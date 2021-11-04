package Msg;
use strict;
use IO::Select;
use IO::Socket;
use Carp;

use vars qw (%rd_callbacks %wt_callbacks $rd_handles $wt_handles);

%rd_callbacks = ();
%wt_callbacks = ();
$rd_handles   = IO::Select->new();
$wt_handles   = IO::Select->new();
my $blocking_supported = 0;

my $TotalConnections = 0;


BEGIN {
    # Checks if blocking is supported
    eval {
        require POSIX; POSIX->import(qw (F_SETFL O_NONBLOCK EAGAIN));
    };
    $blocking_supported = 1 unless $@;
}

use Socket qw(SO_KEEPALIVE SOL_SOCKET);
use constant TCP_KEEPIDLE  => 4; # Start keeplives after this period
use constant TCP_KEEPINTVL => 5; # Interval between keepalives
use constant TCP_KEEPCNT   => 6; # Number of keepalives before death

# TotalConnections
#
# Inputs
#
# Outputs
#
# Description
# This function returns the total number of connections
sub TotalConnections
{
  return $TotalConnections;
}

# Connect
#
# Inputs
# $pkg
# $to_host (Host connect to)
# $to_port (Port number to connect to)
# $rcvd_notification_proc (Function to call on recieving data)
#
# Outputs
#
# Description
# This function connects the client to the server
sub connect {
    my ($pkg, $to_host, $to_port,$rcvd_notification_proc) = @_;
    
    # Create a new internet socket
    
    my $sock = IO::Socket::INET->new (
                                      PeerAddr => $to_host,
                                      PeerPort => $to_port,
                                      Proto    => 'tcp',
                                      TimeOut => 10,
                                      Reuse    => 1);

    return undef unless $sock;

    # Set KeepAlive
    setsockopt($sock, SOL_SOCKET, SO_KEEPALIVE,  pack("l", 1));
    setsockopt($sock, &Socket::IPPROTO_TCP, TCP_KEEPIDLE,  pack("l", 30));
    setsockopt($sock, &Socket::IPPROTO_TCP, TCP_KEEPCNT,   pack("l", 2));
    setsockopt($sock, &Socket::IPPROTO_TCP, TCP_KEEPINTVL, pack("l", 30));
  
    # Increse the total connection count
    $TotalConnections++;

    # Create a connection end-point object
    my $conn = bless {
        sock                   => $sock,
        rcvd_notification_proc => $rcvd_notification_proc,
    }, $pkg;
    
      # Set up the callback to the rcv function
    if ($rcvd_notification_proc) {
        my $callback = sub {_rcv($conn, 0)};
        set_event_handler ($sock, "read" => $callback);
    }
    $conn;
}

# disconnect
#
# Inputs
# $conn (Connection object)
#
# Outputs
#
# Description
# This function disconnects a connection and cleans up
sub disconnect {
    my $conn = shift;
    
    # Decrease the number of total connections
    $TotalConnections--;
    
    # Delete the socket
    my $sock = delete $conn->{sock};
    return unless defined($sock);
    # Set to not try and check for reads and writes of this socket
    set_event_handler ($sock, "read" => undef, "write" => undef);
    close($sock);
}

# send_now
#
# Inputs
# $conn (Connection object)
# $msg (Message to send)
#
# Outputs
#
# Description
# This function does a immediate send, this will block if the socket is not writeable
sub send_now {
    my ($conn, $msg) = @_;
    
    # Puts the message in the queue
    _enqueue ($conn, $msg);
    # Flushes the queue
    $conn->_send (1); # 1 ==> flush
}

# send_later
#
# Inputs
# $conn (Connection object)
# $msg (Message to send)
#
# Outputs
#
# Description
# This function does a sends at a later time, does not block if the socket is not writeable.
# It sets a callback to send the data in the queue when the socket is writeable
sub send_later {
    my ($conn, $msg) = @_;
    
    # Puts the message in the queue
    _enqueue($conn, $msg);
    # Get the current socket
    my $sock = $conn->{sock};
    return unless defined($sock);
    # Sets the callback to send the data when the socket is writeable
    set_event_handler ($sock, "write" => sub {$conn->_send(0)});
}

# _enqueue
#
# Inputs
# $conn (Connection object)
# $msg (Message to send)
#
# Outputs
#
# Description
# This is a private function to place the message on the queue for this socket
sub _enqueue {
    my ($conn, $msg) = @_;
    # prepend length (encoded as network long)
    my $len = length($msg);
    # Stores the length as a network long in the first 4 bytes of the message
    $msg = pack ('N', $len) . $msg; 
    push (@{$conn->{queue}}, $msg);
}

# _send
#
# Inputs
# $conn (Connection object)
# $flush (Deferred Mode)
#
# Outputs
#
# Description
# This is a private function sends the data
sub _send {
    my ($conn, $flush) = @_;
    my $sock = $conn->{sock};
    return unless defined($sock);
    my ($rq) = $conn->{queue};

    # If $flush is set, set the socket to blocking, and send all
    # messages in the queue - return only if there's an error
    # If $flush is 0 (deferred mode) make the socket non-blocking, and
    # return to the event loop only after every message, or if it
    # is likely to block in the middle of a message.

    $flush ? $conn->set_blocking() : $conn->set_non_blocking();
    my $offset = (exists $conn->{send_offset}) ? $conn->{send_offset} : 0;

    # Loop through the messages in the queue
    while (@$rq) {
        my $msg            = $rq->[0];
        my $bytes_to_write = length($msg) - $offset;
        my $bytes_written  = 0;
        while ($bytes_to_write) {
            $bytes_written = syswrite ($sock, $msg,
                                       $bytes_to_write, $offset);
            if (!defined($bytes_written)) {
                if (_err_will_block($!)) {
                    # Should happen only in deferred mode. Record how
                    # much we have already sent.
                    $conn->{send_offset} = $offset;
                    # Event handler should already be set, so we will
                    # be called back eventually, and will resume sending
                    return 1;
                } else {    # Uh, oh
                    $conn->handle_send_err($!);
                    return 0; # fail. Message remains in queue ..
                }
            }
            $offset         += $bytes_written;
            $bytes_to_write -= $bytes_written;
        }
        delete $conn->{send_offset};
        $offset = 0;
        shift @$rq;
        last unless $flush; # Go back to select and wait
                            # for it to fire again.
    }
    # Call me back if queue has not been drained.
    if (@$rq) {
        set_event_handler ($sock, "write" => sub {$conn->_send(0)});
    } else {
        set_event_handler ($sock, "write" => undef);
    }
    1;  # Success
}

# _err_will_block
#
# Inputs
# $conn (Connection object)
#
# Outputs
#
# Description
# This is a private function processes the blocking error message
sub _err_will_block {
    if ($blocking_supported) {
        return ($_[0] == EAGAIN());
    }
    return 0;
}

# set_non_blocking
#
# Inputs
# $_[0] (Connection socket)
#
# Outputs
#
# Description
# This is a function set non-blocking on a socket
sub set_non_blocking {                        # $conn->set_blocking
    if ($blocking_supported) {
        # preserve other fcntl flags
        my $flags = fcntl ($_[0], F_GETFL(), 0);
        fcntl ($_[0], F_SETFL(), $flags | O_NONBLOCK());
    }
}

# set_blocking
#
# Inputs
# $_[0] (Connection socket)
#
# Outputs
#
# Description
# This is a function set blocking on a socket
sub set_blocking {
    if ($blocking_supported) {
        my $flags = fcntl ($_[0], F_GETFL(), 0);
        $flags  &= ~O_NONBLOCK(); # Clear blocking, but preserve other flags
        fcntl ($_[0], F_SETFL(), $flags);
    }
}

# handle_send_err
#
# Inputs
# $conn (Connection object)
# $err_msg (Error message)
#
# Outputs
#
# Description
# This is a function warns on send errors and removes the socket from list of writable sockets
sub handle_send_err {
   # For more meaningful handling of send errors, subclass Msg and
   # rebless $conn.  
   my ($conn, $err_msg) = @_;
   warn "Error while sending: $err_msg \n";
   set_event_handler ($conn->{sock}, "write" => undef);
}

#-----------------------------------------------------------------
# Receive side routines

# new_server
#
# Inputs
# $pkg (Package)
# $my_host (Hostname of the interface to use)
# $my_port (Port number to listen on)
# $login_proc (Reference to function to call when accepting a connection)
#
# Outputs
#
# Description
# This is a function create a listening socket
my ($g_login_proc,$g_pkg);
my $main_socket = 0;
sub new_server {
    @_ >= 4 || die "Msg->new_server (myhost, myport, login_proc)\n";
    my ($RetryCount);
    my ($pkg, $my_host, $ports, $login_proc, $iConnectionTimeout, $iSocketConnections) = @_;
    # Set a default Socket timeout value
    $iConnectionTimeout = 0 if (!defined $iConnectionTimeout);
    # Set a default Socket retry to be forever
    $iSocketConnections = -1 if (!defined $iSocketConnections);
    
    while(!$main_socket)
    {
        #Check to see if there is a retry limit and if the limit has been reached
        if ($iSocketConnections != -1)
        {
            if (($RetryCount / scalar(@$ports)) >= $iSocketConnections)
            {
                die "ERROR: could not create socket after ".$RetryCount / scalar(@$ports)." attempts";            
            } else {
                # Increment the number of retries
                $RetryCount++;
            }
        }
        
        #Try the first port on the list
        my $my_port = shift(@$ports);
        #Place the port on the back of the queue
        push @$ports,$my_port;
        
        print "Using port number $my_port\n";
        $main_socket = IO::Socket::INET->new (
                                              LocalAddr => $my_host,
                                              LocalPort => $my_port,
                                              Listen    => 5,
                                              Proto     => 'tcp',
                                              TimeOut =>    10,
                                              Reuse     => 1);
        sleep $iConnectionTimeout if (!$main_socket);
    }
    
    # Set KeepAlive
    setsockopt($main_socket, SOL_SOCKET, SO_KEEPALIVE,  pack("l", 1));
    setsockopt($main_socket, &Socket::IPPROTO_TCP, TCP_KEEPIDLE,  pack("l", 30));
    setsockopt($main_socket, &Socket::IPPROTO_TCP, TCP_KEEPCNT,   pack("l", 2));
    setsockopt($main_socket, &Socket::IPPROTO_TCP, TCP_KEEPINTVL, pack("l", 30));
    
    # Add the socket to the list on filehandles to read from.
    set_event_handler ($main_socket, "read" => \&_new_client);
    # Store the package name and login proc for later use
    $g_login_proc = $login_proc; $g_pkg = $pkg;
}

sub rcv_now {
    my ($conn) = @_;
    my ($msg, $err) = _rcv ($conn, 1); # 1 ==> rcv now
    return wantarray ? ($msg, $err) : $msg;
}

sub _rcv {                     # Complement to _send
    my ($conn, $rcv_now) = @_; # $rcv_now complement of $flush
    # Find out how much has already been received, if at all
    my ($msg, $offset, $bytes_to_read, $bytes_read);
    my $sock = $conn->{sock};
    return unless defined($sock);
    if (exists $conn->{msg}) {
        $msg           = $conn->{msg};
        $offset        = length($msg) - 1;  # sysread appends to it.
        $bytes_to_read = $conn->{bytes_to_read};
        delete $conn->{'msg'};              # have made a copy
    } else {
        # The typical case ...
        $msg           = "";                # Otherwise -w complains 
        $offset        = 0 ;  
        $bytes_to_read = 0 ;                # Will get set soon
    }
    # We want to read the message length in blocking mode. Quite
    # unlikely that we'll get blocked too long reading 4 bytes
    if (!$bytes_to_read)  {                 # Get new length 
        my $buf;
        $conn->set_blocking();
        $bytes_read = sysread($sock, $buf, 4);
        if ($! || ($bytes_read != 4)) {
            goto FINISH;
        }
        $bytes_to_read = unpack ('N', $buf);
    }
    $conn->set_non_blocking() unless $rcv_now;
    while ($bytes_to_read) {
        $bytes_read = sysread ($sock, $msg, $bytes_to_read, $offset);
        if (defined ($bytes_read)) {
            if ($bytes_read == 0) {
                last;
            }
            $bytes_to_read -= $bytes_read;
            $offset        += $bytes_read;
        } else {
            if (_err_will_block($!)) {
                # Should come here only in non-blocking mode
                $conn->{msg}           = $msg;
                $conn->{bytes_to_read} = $bytes_to_read;
                return ;   # .. _rcv will be called later
                           # when socket is readable again
            } else {
                last;
            }
        }
    }

  FINISH:
    if (length($msg) == 0) {
        $conn->disconnect();
    }
    if ($rcv_now) {
        return ($msg, $!);
    } else {
        &{$conn->{rcvd_notification_proc}}($conn, $msg, $!);
    }
}

sub _new_client {
    my $sock = $main_socket->accept();
    $TotalConnections++;
    my $conn = bless {
        'sock' =>  $sock,
        'state' => 'connected'
    }, $g_pkg;
    my $rcvd_notification_proc =
        &$g_login_proc ($conn, $sock->peerhost(), $sock->peerport());
    if ($rcvd_notification_proc) {
        $conn->{rcvd_notification_proc} = $rcvd_notification_proc;
        my $callback = sub {_rcv($conn,0)};
        set_event_handler ($sock, "read" => $callback);
    } else {  # Login failed
        $conn->disconnect();
    }
}

#----------------------------------------------------
# Event loop routines used by both client and server

sub set_event_handler {
    shift unless ref($_[0]); # shift if first arg is package name
    my ($handle, %args) = @_;
    my $callback;
    if (exists $args{'write'}) {
        $callback = $args{'write'};
        if ($callback) {
            $wt_callbacks{$handle} = $callback;
            $wt_handles->add($handle);
        } else {
            delete $wt_callbacks{$handle};
            $wt_handles->remove($handle);
        }
    }
    if (exists $args{'read'}) {
        $callback = $args{'read'};
        if ($callback) {
            $rd_callbacks{$handle} = $callback;
            $rd_handles->add($handle);
        } else {
            delete $rd_callbacks{$handle};
            $rd_handles->remove($handle);
       }
    }
}

sub event_loop {
    my ($pkg, $initial_read_timeout, $loop_count) = @_; # event_loop(1) to process events once
    my ($conn, $r, $w, $rset, $wset);
    while (1) {
        # Quit the loop if no handles left to process
        last unless ($rd_handles->count() || $wt_handles->count());
        if (defined $initial_read_timeout)
        {
            ($rset, $wset) = IO::Select->select ($rd_handles, $wt_handles, undef, $initial_read_timeout);
            # On initial timeout a read expect a read within timeout if not disconnect
            if (!defined $rset)
            {
              print "WARNING: no response from server within $initial_read_timeout seconds\n";
              last;
            }
            # Unset intial timeout
            $initial_read_timeout = undef;
        } else {
            ($rset, $wset) = IO::Select->select ($rd_handles, $wt_handles, undef, undef);
        }
        foreach $r (@$rset) {
            &{$rd_callbacks{$r}} ($r) if exists $rd_callbacks{$r};
        }
        foreach $w (@$wset) {
            &{$wt_callbacks{$w}}($w) if exists $wt_callbacks{$w};
        }
        if (defined($loop_count)) {
            last unless --$loop_count;
        }
    }
}

1;

__END__

