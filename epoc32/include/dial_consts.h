// dial_consts.h
//
// Copyright (c) Symbian Software Ltd. 2007.  All rights reserved.
//

/**
@file 
@publishedAll
@deprecated 9.1
*/

#ifndef __DIAL_CONSTS_H__
/**
@internalComponent
@deprecated 9.1
*/
#define __DIAL_CONSTS_H__

/** Maximum length for TDialString. 
@internalComponent

*/
const TInt KMaxDialString=50;

/** Maximum length for TAreaCode. 
@internalComponent

*/
const TInt KMaxAreaCode=10;

/** Maximum length for TNatCode. 
@internalComponent

*/
const TInt KMaxNatCode=10;

/** Maximum length for TNatPrefCode.
@internalComponent

*/
const TInt KMaxNatPrefCode=10;

/** Maximum length for TIntlPrefCode. 
@internalComponent

*/
const TInt KMaxIntlPrefCode=10;

/** A buffer to contain a telephone number to dial. 
@publishedAll

*/
typedef TBuf<KMaxDialString> TDialString;

/** A buffer for a telephony area code. 
@publishedAll

*/
typedef TBuf<KMaxAreaCode> TAreaCode;

/** A buffer for a telephony national code. 
@publishedAll

*/
typedef TBuf<KMaxNatCode> TNatCode;

/** A buffer for a telephony national prefix code. 
@publishedAll

*/
typedef TBuf<KMaxNatPrefCode> TNatPrefCode;

/** A buffer for a telephony international prefix code. 
@publishedAll

*/
typedef TBuf<KMaxIntlPrefCode> TIntlPrefCode;



#endif
