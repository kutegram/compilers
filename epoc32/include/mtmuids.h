// MTMUIDS.H
//
// Copyright (c) 1998-2007 Symbian Ltd.  All rights reserved.
//
/**
* @file
* @publishedAll
* 
*/
#if !defined(__MTMUIDS_H__)
#define __MTMUIDS_H__
#if !defined(__E32STD_H__)
#include <e32std.h>
#endif
#if !defined(__MTMDEF_HRH__)
#include <mtmdef.hrh>
#endif

// capabilities (TUid)
/**
* Maximum message body size.
* @Return type: TInt. 
* @publishedAll
* 
*/
const TUid KUidMtmQueryMaxBodySize={KUidMtmQueryMaxBodySizeValue};
/**
* Maximum total size of message.
* @publishedAll
* 
* @Return type: TInt.
*/
const TUid KUidMtmQueryMaxTotalMsgSize={KUidMtmQueryMaxTotalMsgSizeValue};
/** Character widths supported by message type (returned TInt is the sum of the 
appropriate values KMtm7BitBody, KMtm8BitBody, KMtm16BitBody, and KMtmBinaryBody). */

/**
* @publishedAll
* 
*/
const TUid KUidMtmQuerySupportedBody={KUidMtmQuerySupportedBodyValue};
/**
* Are attachments supported.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMtmQuerySupportAttachments={KUidMtmQuerySupportAttachmentsValue};
/**
* Does the MTM message type have a subject field.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMtmQuerySupportSubject={KUidMtmQuerySupportSubjectValue};
/**
* Does the MTM support folders.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMtmQuerySupportsFolder={KUidMtmQuerySupportsFolderValue};
/**
* Off-line operation allowed.
* @No return value.
* @publishedAll
* 
*/
const TUid KUidMtmQueryOffLineAllowed={KUidMtmQueryOffLineAllowedValue};
/**
* Send message.
* @No return value.
* @publishedAll
* 
*/ 
const TUid KUidMtmQueryCanSendMsg={KUidMtmQueryCanSendMsgValue};
/**
* Receive message.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMtmQueryCanReceiveMsg={KUidMtmQueryCanReceiveMsgValue};
/**
* Maximum number of recipients (-1 indicates unlimited numbers).
* @Return type: TInt
* @publishedAll
* 
*/
const TUid KUidMtmQueryMaxRecipientCount={KUidMtmQueryMaxRecipientCountValue};
/**
* When using the MTM in Send-As, does a rendered image have to be prepared (i.e.fax).
* @Return type: TBool. 
* @publishedAll
* 
*/
const TUid KUidMtmQuerySendAsRequiresRenderedImage={KUidMtmQuerySendAsRequiresRenderedImageValue};
/**
* Printer driver UID for rendering the fax image.
* @Return type: TUid
* @publishedAll
* 
*/
const TUid KUidMtmQuerySendAsRenderingUid={KUidMtmQuerySendAsRenderingUidValue};
/**
* UID of default message editor.
* @Return type: TUid. 
* @publishedAll
* 
*/
const TUid KUidMsvMtmQueryEditorUid={KUidMsvMtmQueryEditorUidValue};
/**
* Does the MTM support BIO messages.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMsvQuerySupportsBioMsg={KUidMtmQuerySupportsBioMsgValue};
/**
* Does the MTM support scheduled sending.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMsvQuerySupportsScheduling={KUidMtmQuerySupportsSchedulingValue};
/**
* Does the MTM support the use of recipient type.
* @No return value. 
* @publishedAll
* 
*/
const TUid KUidMtmQuerySupportsRecipientType={KUidMtmQuerySupportsRecipientTypeValue};
/**
* Support for Sending messages using SendAs.  
* If this is supported, then the MTM supports sending messages created through the SendAs API.
* @Return type: TBool. 
* @publishedAll
* 
*/
const TUid KUidMtmQuerySendAsMessageSendSupport={KUidMtmQuerySendAsMessageSendSupportValue};

#endif
