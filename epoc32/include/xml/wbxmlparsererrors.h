// wbxmlparsererrors.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __WBXMLPARSERERRORS_H__
#define __WBXMLPARSERERRORS_H__

/**
@file

This file contains WBXML Parser panic errors and the Panic function

@internalTechnology
*/

#include <e32base.h>

enum TWbxmlParserError
	{
	/**
	Indicates that a leave code other than that expected was received.
	*/
	EWbxmlParserErrorUnexpectedLeaveCode		= 7000,

	/**
	Indicates that a state other than that expected was reached.
	*/
	EWbxmlParserErrorUnexpectedState			= 7001,

	/**
	Indicates that logic other than that expected was reached.
	*/
	EWbxmlParserErrorUnexpectedLogic			= 7002,

	};


void Panic(TWbxmlParserError aError);


// __WBXMLPARSERERRORS_H__
#endif
