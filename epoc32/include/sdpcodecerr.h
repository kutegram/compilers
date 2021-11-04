/*
* =============================================================================
*  Name          : SdpCodecErr.h
*  Part of       : SDP Codec
*  Interface     : SDK API, SDP Codec API
*  Description   : 
*  Version       : 1.0
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
#ifndef SDPCODECERR_H
#define SDPCODECERR_H

/*
* @file
* @publishedAll
* 
*/


/**
 * Base value for the SdpCode error code range
 */
const TInt KSdpCodecErrorBase = -17875;
/**
 * Codec encoding errors for SDP fields
 */
const TInt KErrSdpCodecVersionField			= KSdpCodecErrorBase;
const TInt KErrSdpCodecOriginField			= KSdpCodecErrorBase - 1; 
const TInt KErrSdpCodecSessionField			= KSdpCodecErrorBase - 2; 
const TInt KErrSdpCodecInfoField			= KSdpCodecErrorBase - 3; 
const TInt KErrSdpCodecUriField				= KSdpCodecErrorBase - 4; 
const TInt KErrSdpCodecEmailField			= KSdpCodecErrorBase - 5; 
const TInt KErrSdpCodecPhoneField			= KSdpCodecErrorBase - 6; 
const TInt KErrSdpCodecConnectionField		= KSdpCodecErrorBase - 7; 
const TInt KErrSdpCodecBandwidthField		= KSdpCodecErrorBase - 8; 
const TInt KErrSdpCodecTimeField			= KSdpCodecErrorBase - 9; 
const TInt KErrSdpCodecRepeatField			= KSdpCodecErrorBase - 10; 
const TInt KErrSdpCodecZoneField			= KSdpCodecErrorBase - 11; 
const TInt KErrSdpCodecKeyField				= KSdpCodecErrorBase - 12; 
const TInt KErrSdpCodecAttributeField		= KSdpCodecErrorBase - 13; 
const TInt KErrSdpCodecMediaField			= KSdpCodecErrorBase - 14; 
const TInt KErrSdpCodecMediaInfoField		= KSdpCodecErrorBase - 15; 
const TInt KErrSdpCodecMediaConnectionField	= KSdpCodecErrorBase - 16; 
const TInt KErrSdpCodecMediaBandwidthField	= KSdpCodecErrorBase - 17; 
const TInt KErrSdpCodecMediaKeyField	    = KSdpCodecErrorBase - 18; 
const TInt KErrSdpCodecMediaAttributeField	= KSdpCodecErrorBase - 19; 
const TInt KErrSdpCodecTypedTime            = KSdpCodecErrorBase - 20;

const TInt KErrSdpCodecStringPool           = KSdpCodecErrorBase - 21;
const TInt KErrSdpCodecDecode				= KSdpCodecErrorBase - 22;

//SDPCODECERR_H
#endif
