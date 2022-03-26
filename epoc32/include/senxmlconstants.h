/*
* ==============================================================================
*  Name        : SenXmlConstants.h
*  Part of     : Web Services Xml
*  Interface   :
*  Description : This header lists all constants of XML Extensions library
*  Version     :
*
*  Copyright � 2002-2005 Nokia. All rights reserved.
*  This material, including documentation and any related
*  computer programs, is protected by copyright controlled by
*  Nokia. All rights are reserved. Copying, including
*  reproducing, storing, adapting or translating, any
*  or all of this material requires the prior written consent of
*  Nokia. This material also contains confidential
*  information which may not be disclosed to others without the
*  prior written consent of Nokia.
* ==============================================================================
*/


#ifndef SEN_XML_CONSTANTS_H
#define SEN_XML_CONSTANTS_H

//  INCLUDES
#include <e32base.h>

// CONSTANTS
// Leave codes
const TInt KErrSenInvalidCharacters         =   -30300;
const TInt KErrSenZeroLengthDescriptor      =   -30301;
const TInt KErrSenXmlReaderNotSet           =   -30302;
const TInt KErrSenXmlContentHandlerNotSet   =   -30303;

// Panics
_LIT(KSenXmlPanic, "SenXml");



// XML String constants
const TInt KSenMaxXmlEscapedLength = 8;
_LIT8(KSenSlash,                    "/");
_LIT8(KSenColon,                    ":");
_LIT8(KSenLessThan,                 "<");
_LIT8(KSenGreaterThan,              ">");
_LIT8(KSenSpace,                    " ");
_LIT8(KSenQuot,                     "'");
_LIT8(KSenDblQuot,                  "\"");
_LIT8(KSenEquals,                   "=");
_LIT8(KSenEqualsDblQuot,            "=\"");
_LIT8(KSenSlashGreaterThan,         "/>");
_LIT8(KSenLessThanSlash,            "</");
_LIT8(KSenSpaceXmlns,               " xmlns");
_LIT8(KSenXmlns,                    "xmlns");
_LIT8(KSenXmlNsAttNamePlusColon,    "xmlns:");
_LIT8(KSenXmlCommentStart,          "<!--");
_LIT8(KSenXmlCommentEnd,            "-->");
_LIT8(KSenXmlInstructionStart,      "<?");
_LIT8(KSenXmlInstructionEnd,         "?>");
_LIT8(KSenXmlEntityStart,            "<!");

// The predeclared, basic XML entities:
// &apos;    (')
// &quot;    (")
// &gt;      (>)
// &lt;      (<)
// &amp;     (&)

_LIT8(KSenEscapedAmp,     "&amp;");
_LIT8(KSenEscapedApos,    "&apos;");
_LIT8(KSenEscapedDblQuot, "&quot;");
_LIT8(KSenEscapedGt,      "&gt;");
_LIT8(KSenEscapedLt,      "&lt;");

// XML-escaping chars as descriptors
_LIT8(KSenAmpersandDesC8,  "&");
_LIT8(KSenAposDesC8,       "\'");
_LIT8(KSenDblQuotDesC8,    "\"");
_LIT8(KSenGtDesC8,         ">");
_LIT8(KSenLtDesC8,         "<");


/*
_LIT8(KSenQuotedAmp,     "&amp;");
_LIT8(KSenQuotedApos,    "&apos;");
_LIT8(KSenQuotedDblQuot, "&quot;");
_LIT8(KSenQuotedGt,      "&gt;");
_LIT8(KSenQuotedLt,      "&lt;");
*/

/**
* SenXmlPanic Enumeration
*/
enum TSenXmlPanic
    {
    EBadNamespace = 1,
    EBadNamespacePrefix,
    EBufNot16Bit,
    EFragmentElementNotInitialized,
    EDelegatedFragmentAlreadySet,
    EInconsistentTokens,
    EBadInternalState
    };

#endif // SEN_XML_CONSTANTS_H

// End of File

