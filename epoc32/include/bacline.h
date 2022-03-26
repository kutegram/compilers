// BACLINE.H
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//

#ifndef __BACLINE_H
#define __BACLINE_H

#ifndef __E32BASE_H
#include <e32base.h>
#endif

/**
Not available until Platform 003
@internalComponent
*/
typedef TBuf<0x100> TBaCommand;

class CCommandLineArguments : public CBase
/** Parses command line arguments.

The class provides functions to access the arguments that are supplied when 
a program is launched as a new process. 

The program name is returned as argument 0. Other arguments are returned as 
arguments 1, 2 etc. 

The Count() function indicates how many arguments there are, including the 
program name. Arguments may be quoted to contain blanks and quotes.

The command line arguments and process name occupy 256 characters each. In 
order to minimise the space used throughout the lifetime of a program, it 
is recommended that the program parse the arguments shortly after initialisation, 
save the argument values appropriately, and then destroy the CCommandLineArguments 
object.

The main use of this class is in parsing the arguments of WINC command-line 
utilities.

This class is not intended for user derivation 
@publishedAll

*/
	{
public:
	// construct/destruct
	IMPORT_C static CCommandLineArguments* NewLC();
	IMPORT_C static CCommandLineArguments* NewL();
	IMPORT_C ~CCommandLineArguments();
	// extract
	IMPORT_C TPtrC Arg(TInt aArg) const;
	IMPORT_C TInt Count() const;
private:
	CCommandLineArguments();
	void ConstructL();
private:
	CArrayFixFlat<TPtrC>* iArgs;
	HBufC* iCommandLine;
	TFileName iFileName;
	};

#endif
