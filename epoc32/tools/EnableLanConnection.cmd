:: ============================================================================
::  Name        : EnableLanConnection.cmd
::  Part of     : nettools / emulatorlan       *** Info from the SWAD
::  Description : Command file for project emulatorlan
::  Version     : %version: 1.1.1 % << Don't touch! Updated by Synergy at check-out.
::
::  Copyright © 2007 Nokia.  All rights reserved.
::  This material, including documentation and any related computer
::  programs, is protected by copyright controlled by Nokia.  All
::  rights are reserved.  Copying, including reproducing, storing,
::  adapting or translating, any or all of this material requires the
::  prior written consent of Nokia.  This material also contains
::  confidential information which may not be disclosed to others
::  without the prior written consent of Nokia.
:: ============================================================================
:: Template version: 4.1.1

call configchange.pl --config ethernetWithCommDB --kernel EKA2 --target winscw --variant UDEB
call \epoc32\RELEASE\winscw\udeb\dbcreator.exe -dtextshell -- f:c:\S60_32_default_snaps.xml
