/*
* =============================================================================
*  Name        : _sipcodecdefs.h
*  Part of     : SIP Codec
*  Interface   : SDK API, SIP Codec API
*  Description : 
*  Version     : SIP/4.0 
*
*  Copyright (c) 2004 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing, adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation. 
* =============================================================================
*/

#ifndef SIPCODECDEFS_H
#define SIPCODECDEFS_H

#ifdef CPPUNIT_TEST

#define UNIT_TEST(ClassName) friend class ClassName;

#else 

#define UNIT_TEST(ClassName)

#endif

// SIPCODECDEFS_H
#endif
