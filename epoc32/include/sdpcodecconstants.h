/*
* =============================================================================
*  Name          : SdpCodecConstants.h
*  Part of       : SDPCodec
*  Description   : Constants defination file 
*  Version       : 1.0 
*
*  Copyright (c) 2002 Nokia Corporation. 
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


#ifndef __SDPCODECCONSTANTS_H__
#define __SDPCODECCONSTANTS_H__

/*
* @file
* @publishedAll
* 
*/

// Delimiter constants
const TText8 KDotChar = '.';
const TText8 KColonChar = ':';
const TText8 KSPChar = ' ';  
const TText8 KEqualChar = '=';
const TText8 KSlashChar = '/';
const TText8 KHyphenChar = '-';
const TText8 KLFChar = '\n';
const TText8 KCRChar = '\r';
const TText8 KEofChar = '\0';

_LIT8(KDotStr, ".");
_LIT8(KColonStr, ":");
_LIT8(KSPStr, " ");
_LIT8(KEqualStr, "=");
_LIT8(KSlashStr, "/");
_LIT8(KHyphenStr, "-");
_LIT8(KCRLFStr, "\r\n");
_LIT8(KLFStr, "\n");
_LIT8(KCRStr, "\r");
_LIT8(KEofStr, "\0");
_LIT8(KValidFQDNChars, 
      "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ.-");

#endif
