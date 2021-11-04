// httperr.h
//
// Copyright (c) Symbian Software Ltd 2001-2007.  All rights reserved.
 
/** 
	@file httperr.h
	@warning : This file contains Rose Model ID comments - please do not delete
 */ 

#ifndef __HTTPERR_H__
#define __HTTPERR_H__

// System includes
#include <e32std.h>

//##ModelId=3C4C18750141
class HTTPStatus
/** 
The complete set of HTTP Status codes, as defined in RFC2616.
@publishedAll

*/
	{
public:
	enum 
		{
		/** 'Informational' range of codes 1xx 
		*/ 
		/** Continue.
		*/
		EContinue						= 100, 
		/** Switching Protocols.
		*/
		ESwitchingProtocols				= 101,  
		/** 'Successful' range of codes 2xx 
		*/
		/** Ok.
		*/
		EOk								= 200,
		/** Created.
		*/
		ECreated						= 201,  
		/** The entry has been accepted.
		*/
		EAccepted						= 202,
		/** Non-Authoritative Information.
		*/
		ENonAuthoritativeInfo			= 203,
		/** No Content.
		*/
		ENoContent						= 204,
		/** Reset Content.
		*/
		EResetContent					= 205, 
		/** Partial Content.
		*/
		EPartialContent					= 206,
		/** 'Redirection' range of codes 3xx 
		*/
		/** Multiple Choices.
		*/
		EMultipleChoices				= 300, 
		/** Moved Permanently.
		*/
		EMovedPermanently				= 301,
		/** Found.
		Note, this is deprecated in HTTP/1.1 - 307 will be used instead
		*/
		EFound							= 302,  
		/** See Other.
		*/
		ESeeOther						= 303,
		/** Not Modified.
		*/
		ENotModified					= 304,
		/** Use Proxy.
		*/
		EUseProxy						= 305,
		/** Unused.
		*/
		EUnused							= 306,
		/** Temporary Redirect.
		*/
		ETemporaryRedirect				= 307,
		/** 'Client Error' range of codes 4xx 
		*/
		/** Bad Request.
		*/
		EBadRequest						= 400,
		/** Unauthorized.
		*/
		EUnauthorized					= 401,
		/** Payment Required. Note, this is reserved in HTTP/1.1
		*/
		EPaymentRequired				= 402, 
		/** Forbidden.
		*/
		EForbidden						= 403,
		/** Not Found.
		*/
		ENotFound						= 404,
		/** Method Not Allowed.
		*/
		EMethodNotAllowed				= 405,
		/** Not Acceptable.
		*/
		ENotAcceptable					= 406,
		/** Proxy Authentication Required.
		*/
		EProxyAuthenticationRequired	= 407,
		/** Request Timeout.
		*/
		ERequestTimeout					= 408,
		/** Conflict.
		*/
		EConflict						= 409,
		/** Gone.
		*/
		EGone							= 410,
		/** Length Required.
		*/
		ELengthRequired					= 411,
		/** Precondition Failed.
		*/
		EPreconditionFailed				= 412,
		/** Request Entity Too Large. 
		*/
		ERequestEntityTooLarge			= 413,
		/** Request-URI Too Long.
		*/
		ERequestURITooLong				= 414,
		/** Unsupported Media Type.
		*/
		EUnsupportedMediaType			= 415,
		/** Requested Range Not Satisfiable.
		*/
		ERequestedRangeNotSatisfiable	= 416,
		/** Expectation Failed.
		*/
		EExpectationFailed				= 417,
		/** 'Server Error' range of codes 5xx 
		*/
		/** Internal Server Error.
		*/
		EInternalServerError			= 500,
		/** Not Implemented.
		*/
		ENotImplemented					= 501,
		/** Bad Gateway.
		*/
		EBadGateway						= 502,
		/** Service Unavailable.
		*/
		EServiceUnavailable				= 503, 
		/** Gateway Timeout.
		*/
		EGatewayTimeout					= 504,
		/** HTTP Version Not Supported.
		*/
		EHTTPVersionNotSupported		= 505
		};

		/** Is the supplied status code in the 1xx Informational range?
		@param aStatus Is the supplied status code in the 1xx Informational range?
		@return ETrue if the specified status code is in the 1xx Informational range.
		##ModelId=3C4C18750162
		*/
		inline static TBool IsInformational(TInt aStatus);
		
		
		/** Is the supplied status code in the 2xx Successful range?
		@param aStatus Is the supplied status code in the 2xx Successful range?
		@return ETrue if the specified status code is in the 2xx Successful range
		##ModelId=3C4C18750160
		*/
		inline static TBool IsSuccessful(TInt aStatus);

		/** Is the supplied status code in the 3xx Redirection range? 
		@param aStatus Is the supplied status code in the 3xx Redirection range?
		@return	ETrue if the specified status code is in the 3xx Redirection range.
		##ModelId=3C4C18750159
		*/
		inline static TBool IsRedirection(TInt aStatus);

		/** Is the supplied status code in the 4xx Client Error range? 
		@param aStatus Is the supplied status code in the 4xx Client Error range?
		@return ETrue if the specified status code is in the 4xx Client Error range.
		##ModelId=3C4C18750157
		*/
		inline static TBool IsClientError(TInt aStatus);

		/** Is the supplied status code in the 5xx Server Error range? 
		@param aStatus Is the supplied status code in the 5xx Server Error range?
		@return ETrue if the specified status code is in the 5xx Server Error range.
		##ModelId=3C4C18750155
		*/
		inline static TBool IsServerError(TInt aStatus);
	};

//
// HTTP Panic codes
//

#include <e32base.h>

// HTTPPanic::Panic(HTTPPanic:: )

//##ModelId=3C4C18740352
class HTTPPanic
/**
HTTP panic codes
@publishedAll

*/
	{
public:
	enum THTTPPanic
		{
		/** RHTTPSession session is already open. ( Panic HTTP-CORE 0 )
		*/
		ESessionAlreadyOpen,
		/** Specified field is missing. ( Panic HTTP-CORE 1 )
		*/
		EHeaderFieldMissing,
		/** Unused. ( Panic HTTP-CORE 2 )
		*/
		EHeaderParamMissing,
		/** Unused. ( Panic HTTP-CORE 2 )
		*/
		EHeaderInvalidPart,
		/** Mismatch between header's type and its attempted use. ( Panic HTTP-CORE 4 )
		*/
		EHeaderInvalidType,
		/** Unused. ( Panic HTTP-CORE 5 )
		*/
		ETransactionEventOutstanding,
		/** A transaction error occurred, and the MHFRunError() in use didn't handle it. ( Panic HTTP-CORE 6 )
		*/
		ETransactionUnhandledError,
		/** Attempted to add a filter while there is a transaction outstanding. ( Panic HTTP-CORE 6 )
		*/
		EAddingFilterWithOutstandingTransactions,
		/** Attempted to add a filter at a position not between the protocol handler and the client. ( Panic HTTP-CORE 8 )
		*/
		EFilterInvalidPosition,
		/** CHTTPEncoder object destroyed without its data being released. ( Panic HTTP-CORE 9 )
		*/
		EHTTPFormDataUnreleased,
		/** CHTTPEncoder object at the wrong state for adding data. ( Panic HTTP-CORE 10 ) 
		*/
		EHTTPFormSupplyingData,
		/** Unused. ( Panic HTTP-CORE 11 )
		*/
		EValidationFilterFailure,
		/** Invalid request data. ( Panic HTTP-CORE 12 )
		*/
		EInvalidTxData,
		/** Invalid response data. ( Panic HTTP-CORE 13 )
		*/
		EInvalidRxData,
		/** Unused. ( Panic HTTP-CORE 14 )
		*/
		ENoTransportHandlerSet,
		/** Unused. ( Panic HTTP-CORE 15 )
		*/
		EAuthenticationFilterBadState,
		/** An invalid filter handle was specified. ( Panic HTTP-CORE 16 )
		*/
		EInvalidFilterHandle
		};

	//##ModelId=3C4C18740366
	static void Panic(THTTPPanic aPanic);
	};

// HTTP external errors/leave codes. Add new sub-ranges at the end; do not insert between the sub-ranges that
// are already here.  This is to allow a client to reasonably check for errors between two adjacent range
// base values rather than check for individual codes.

/**
Base value for the HTTP error code range (-7200 to -7399)
@publishedAll

*/
const TInt KHttpErrorBase = -7200;

//
// Text mode HTTP protocol handler
//

/**
Codec encoding errors for HTTP headers
@publishedAll

*/
const TInt KHttpHeaderEncodeErrorBase = KHttpErrorBase;

/**
Error making a default encoding of unrecognised headers
@publishedAll

*/
const TInt KErrHttpEncodeDefault			= KHttpHeaderEncodeErrorBase;
/**
Error encoding the Accept field
@publishedAll

*/
const TInt KErrHttpEncodeAccept				= KHttpHeaderEncodeErrorBase - 1; 
/**
Error encoding the Accept-Charset field
@publishedAll

*/
const TInt KErrHttpEncodeAcceptCharset		= KHttpHeaderEncodeErrorBase - 2; 
/**
Error encoding a q-value parameter
@publishedAll

*/
const TInt KErrHttpEncodeQValue				= KHttpHeaderEncodeErrorBase - 3; 
/**
Error encoding the Authorization field
@publishedAll

*/
const TInt KErrHttpEncodeAuthorization		= KHttpHeaderEncodeErrorBase - 4; 
/**
Error encoding Basic credentials
@publishedAll

*/
const TInt KErrHttpEncodeBasicAuth			= KHttpHeaderEncodeErrorBase - 5; 
/**
Error encoding Digest credentials
@publishedAll

*/
const TInt KErrHttpEncodeDigestAuth			= KHttpHeaderEncodeErrorBase - 6; 
/**
Error encoding the Connection field
@publishedAll

*/
const TInt KErrHttpEncodeConnection			= KHttpHeaderEncodeErrorBase - 7; 
/**
Error encoding the Content-Length field
@publishedAll

*/
const TInt KErrHttpEncodeContentLength		= KHttpHeaderEncodeErrorBase - 8; 
/**
Error encoding the Content-Type field
@publishedAll

*/
const TInt KErrHttpEncodeContentType		= KHttpHeaderEncodeErrorBase - 9; 
/**
Error encoding the Host field
@publishedAll

*/
const TInt KErrHttpEncodeHost				= KHttpHeaderEncodeErrorBase - 10;
/**
Error encoding the Host field's port parameter
@publishedAll

*/
const TInt KErrHttpEncodeHostPort			= KHttpHeaderEncodeErrorBase - 11;
/**
Error encoding the Transfer-Encoding field
@publishedAll

*/
const TInt KErrHttpEncodeTransferEncoding	= KHttpHeaderEncodeErrorBase - 12;
/**
Error encoding the User-Agent field
@publishedAll

*/
const TInt KErrHttpEncodeUserAgent			= KHttpHeaderEncodeErrorBase - 13;
/**
Error encoding the Date field
@publishedAll

*/
const TInt KErrHttpEncodeDate				= KHttpHeaderEncodeErrorBase - 14;
/**
Error encoding the Cookie field 
@publishedAll

*/
const TInt KErrHttpEncodeCookie				= KHttpHeaderEncodeErrorBase - 15;
/**
Error encoding the Cache-Control field
@publishedAll

*/
const TInt KErrHttpEncodeCacheControl		= KHttpHeaderEncodeErrorBase - 16; 
/**
Error encoding the Pragma field 
@publishedAll

*/
const TInt KErrHttpEncodePragma				= KHttpHeaderEncodeErrorBase - 17;
/**
Error encoding the if match field
@publishedAll

*/
const TInt KErrHttpEncodeIfMatch			= KHttpHeaderEncodeErrorBase - 18; 
/**
Error encoding the if none match field 
@publishedAll

*/
const TInt KErrHttpEncodeIfNoneMatch		= KHttpHeaderEncodeErrorBase - 19;
/**
Error encoding the if modified since field 
@publishedAll

*/
const TInt KErrHttpEncodeIfModifiedSince	= KHttpHeaderEncodeErrorBase - 20;
/**
Error encoding the if unmodified since field 
@publishedAll

*/
const TInt KErrHttpEncodeIfUnmodifiedSince	= KHttpHeaderEncodeErrorBase - 21;
/**
Error encoding the Cookie2 field 
@publishedAll

*/
const TInt KErrHttpEncodeCookie2			= KHttpHeaderEncodeErrorBase - 22;
/**
Error encoding the Content-Language field
@publishedAll

*/
const TInt KErrHttpEncodeContentLanguage	= KHttpHeaderEncodeErrorBase - 23;
/**
Error encoding the WWWAuthenticate field
@publishedAll

*/
const TInt KErrHttpEncodeDoWWWAuthenticate	= KHttpHeaderEncodeErrorBase - 24;
/**
Error encoding the Age field
@publishedAll

*/
const TInt KErrHttpEncodeDoAge				= KHttpHeaderEncodeErrorBase - 25;
/**
Error encoding the Vary field
@publishedAll

*/
const TInt KErrHttpEncodeDoVary				= KHttpHeaderEncodeErrorBase - 26;
/**
Error encoding the Content-Language field
@publishedAll

*/
const TInt KErrHttpEncodeDoContentLanguage	= KHttpHeaderEncodeErrorBase - 27;
/**
Error encoding the Content-Encoding field
@publishedAll

*/
const TInt KErrHttpEncodeContentEncoding	= KHttpHeaderEncodeErrorBase - 28;
/**
Error encoding the Content-Location field
@publishedAll

*/
const TInt KErrHttpEncodeContentLocation	= KHttpHeaderEncodeErrorBase - 29;
/**
Error encoding the Content-MD5 field
@publishedAll

*/
const TInt KErrHttpEncodeContentMD5			= KHttpHeaderEncodeErrorBase - 30;
/**
Error encoding the Accept-Encoding field
@publishedAll

*/
const TInt KErrHttpEncodeAcceptLanguage		= KHttpHeaderEncodeErrorBase - 31;
/**
Error encoding the Accept-Language field
@publishedAll

*/
const TInt KErrHttpEncodeAcceptEncoding		= KHttpHeaderEncodeErrorBase - 32;
/**
Error encoding the TE field
@publishedAll

*/
const TInt KErrHttpEncodeTE					= KHttpHeaderEncodeErrorBase - 33;
/**
Error encoding the Upgrade field
@publishedAll

*/
const TInt KErrHttpEncodeUpgrade			= KHttpHeaderEncodeErrorBase - 34;

/**
Codec decoding errors for values found in HTTP headers
@publishedAll

*/
const TInt KHttpValueDecodeErrorBase = KHttpErrorBase - 60;

/**
General formatting error for date values
@publishedAll

*/
const TInt KErrHttpDecodeMalformedDate		= KHttpValueDecodeErrorBase;	 
/**
Malformed year
@publishedAll

*/
const TInt KErrHttpDecodeMalformedYear 		= KHttpValueDecodeErrorBase - 1; 
/**
Malformed short month name
@publishedAll

*/
const TInt KErrHttpDecodeMalformedMonth		= KHttpValueDecodeErrorBase - 2; 
/**
Malformed number of day in month
@publishedAll

*/
const TInt KErrHttpDecodeMalformedDay		= KHttpValueDecodeErrorBase - 3; 
/**
Malformed short day name
@publishedAll

*/
const TInt KErrHttpDecodeMalformedWkDay		= KHttpValueDecodeErrorBase - 4; 
/**
Malformed long day name
@publishedAll

*/
const TInt KErrHttpDecodeMalformedWeekDay	= KHttpValueDecodeErrorBase - 5; 
/**
Malformed integer value
@publishedAll

*/
const TInt KErrHttpDecodeMalformedInteger	= KHttpValueDecodeErrorBase - 6; 
/**
Malformed quoted string
@publishedAll

*/
const TInt KErrHttpDecodeMalformedQuotedStr	= KHttpValueDecodeErrorBase - 7; 

/**
Codec decoding errors for HTTP headers
@publishedAll

*/
const TInt KHttpHeaderDecodeErrorBase = KHttpErrorBase - 70;

/**
Error decoding the Accept field
@publishedAll

*/
const TInt KErrHttpDecodeAccept				= KHttpHeaderDecodeErrorBase;
/**
Error decoding the Connection field
@publishedAll

*/
const TInt KErrHttpDecodeConnection			= KHttpHeaderDecodeErrorBase - 1;
/**
Error decoding the Content-Length field
@publishedAll

*/
const TInt KErrHttpDecodeContentLength		= KHttpHeaderDecodeErrorBase - 2;
/**
Error decoding the Content-Type field
@publishedAll

*/
const TInt KErrHttpDecodeContentType		= KHttpHeaderDecodeErrorBase - 3;
/**
Error decoding the Transfer-Encoding field
@publishedAll

*/
const TInt KErrHttpDecodeTransferEncoding	= KHttpHeaderDecodeErrorBase - 4;
/**
Error decoding the WWWAuthenticate field
@publishedAll

*/
const TInt KErrHttpDecodeWWWAuthenticate	= KHttpHeaderDecodeErrorBase - 5;
/**
The WWWAuthenticate field contained an unrecognised authentication scheme
@publishedAll

*/
const TInt KErrHttpDecodeUnknownAuthScheme	= KHttpHeaderDecodeErrorBase - 6;
/**
Error decoding a Basic WWWAuthenticate challenge
@publishedAll

*/
const TInt KErrHttpDecodeBasicAuth			= KHttpHeaderDecodeErrorBase - 7;
/**
Error decoding a Digest WWWAuthenticate challenge
@publishedAll

*/
const TInt KErrHttpDecodeDigestAuth			= KHttpHeaderDecodeErrorBase - 8;
/**
Error decoding a Set-Cookie field
@publishedAll

*/
const TInt KErrHttpDecodeCookie				= KHttpHeaderDecodeErrorBase - 9;
/**
Error decoding the Authorization field
@publishedAll

*/
const TInt KErrHttpDecodeAuthorization		= KHttpHeaderDecodeErrorBase - 10;
/**
Error decoding the Accept-Charset field
@publishedAll

*/
const TInt KErrHttpDecodeAcceptCharset		= KHttpHeaderDecodeErrorBase - 11;
/**
Error decoding the Accept-Language field
@publishedAll

*/
const TInt KErrHttpDecodeAcceptLanguage		= KHttpHeaderDecodeErrorBase - 12;
/**
Error decoding the Accept-Encoding field
@publishedAll

*/
const TInt KErrHttpDecodeAcceptEncoding		= KHttpHeaderDecodeErrorBase - 13;
/**
Error decoding the TE field
@publishedAll

*/
const TInt KErrHttpDecodeTE					= KHttpHeaderEncodeErrorBase - 14;
/**
Error decoding the Expect field
@publishedAll

*/
const TInt KErrHttpDecodeExpect				= KHttpHeaderEncodeErrorBase - 15;
/**
Error decoding the Content-Disposition field
@publishedAll

*/
const TInt KErrHttpDecodeContentDisposition	= KHttpHeaderDecodeErrorBase - 14;
/**
Response errors. These represent specific failure cases
@publishedAll

*/
const TInt KErrHttpResponseFailureBase = KHttpErrorBase - 100;

/**
A uri redirected too many times, possibly indicating a circular redirection
@publishedAll

*/
const TInt KErrHttpRedirectExceededLimit		= KErrHttpResponseFailureBase;	  
/**
A server responded that the uri must be fetched via a proxy
@publishedAll

*/
const TInt KErrHttpRedirectUseProxy				= KErrHttpResponseFailureBase - 1;
/**
A server sent a redirection response that did not include a Location header
@publishedAll

*/
const TInt KErrHttpRedirectNoLocationField		= KErrHttpResponseFailureBase - 2;
/**
An error occured in parsing which left the parser in a unknown state
@publishedAll

*/
const TInt KErrHttpUnknownParseState			= KErrHttpResponseFailureBase - 3;

/**
Request building errors: cause the Validation Filter to make a transaction fail and terminate 
@publishedAll

*/
const TInt KErrHttpReqBuildErrorBase = KHttpErrorBase - 130;

/**
A body is provided with a method that doesn't allow bodys to be transmitted
@publishedAll

*/
const TInt KErrHttpRequestHasBody					= KErrHttpReqBuildErrorBase;	
/**
A body is missing from a method that requires it
@publishedAll

*/
const TInt KErrHttpRequestBodyMissing				= KErrHttpReqBuildErrorBase - 1;			
/**
Should contain The Max-Forward header
@publishedAll

*/
const TInt KErrHttpTraceReqWithoutMaxForwardHeader	= KErrHttpReqBuildErrorBase - 2;
/**
Body must NOT be sent chunked if using HTTP/1.0
@publishedAll

*/
const TInt KErrHttpPostReqBodyWithoutSizeOnHTTP10	= KErrHttpReqBuildErrorBase - 3;
/**
Request contained a response header or a entity header but no body
@publishedAll

*/
const TInt KErrHttpInvalidHeaderInRequest	  		= KErrHttpReqBuildErrorBase - 4;
/**
Missing but required header errors
@publishedAll

*/

const TInt KErrHttpMissingHeaderBase = KHttpErrorBase - 160;
/**
A body was provided in the request but no Content-Type header was set
@publishedAll

*/

const TInt KErrHttpEntityHeaderMissingContentType		= KErrHttpMissingHeaderBase;	
/**
The request URI was relative, but no Host header was set to indicate a server to connect to
@publishedAll

*/
const TInt KErrHttpGeneralHeaderMissingHost				= KErrHttpMissingHeaderBase - 1;
/**
Protocol handler errors
@publishedAll

*/
const TInt KErrHttpProtocolHandlerBase = KHttpErrorBase - 170;
/**
The request body needed to be rewound but the client but it doesn't support 
@publishedAll

*/
const TInt KErrHttpCantResetRequestBody				= KErrHttpProtocolHandlerBase;
/**
The Protocol handler is not initialised
@publishedAll

*/
const TInt KErrHttpProtTransactionNotInitialised	= KErrHttpProtocolHandlerBase -1;
/**
Unable to establish a tunnel.
@publishedAll

*/
const TInt KErrHttpCannotEstablishTunnel			= KErrHttpProtocolHandlerBase -2;
/**
Invalid URI
@publishedAll

*/
const TInt KErrHttpInvalidUri						= KErrHttpProtocolHandlerBase -3;
/**
Protocol handler experienced a non-pipelining error
@publishedAll

*/
const TInt KErrHttpNonPipeliningError				= KErrHttpProtocolHandlerBase -4;
/**
Protocol handler experienced a pipelining error
@publishedAll

*/
const TInt KErrHttpPipeliningError					= KErrHttpProtocolHandlerBase -5;

/**
The request has been not sent for the transaction and connection has been disconnected. 
This error will be propagated to the client only, if the HTTP:ENotifyOnDisconnect property 
is set with a value HTTP::EEnableDisconnectNotification

@publishedAll

*/
const TInt KErrHttpRequestNotSent 					= KErrHttpProtocolHandlerBase -6;

/**
The response has been not received for the transaction and connection has been disconnected. 
This error will be propagated to the client only, if the HTTP:ENotifyOnDisconnect property is 
set with a value HTTP::EEnableDisconnectNotification

@publishedAll

*/
const TInt KErrHttpResponseNotReceived				= KErrHttpProtocolHandlerBase -7;

/**
Partial response has been received and connection has been disconnected. This error will be 
propagated to the client only, if the HTTP:ENotifyOnDisconnect property is set with a value
HTTP::EEnableDisconnectNotification

@publishedAll

*/
const TInt KErrHttpPartialResponseReceived			= KErrHttpProtocolHandlerBase -8;

/**
ClientApplication wants to fail the transaction that was in process by the HTTPMessageParser
@publishedAll

*/
const TInt KErrHttpOptimiserFailsTrans				= KErrHttpProtocolHandlerBase -9;

// end of error codes - maximum error value is -7399 - must not be exceeded!
// Inline methods from HTTPStatus

inline TBool HTTPStatus::IsInformational(TInt aStatus)
	{ 
	return ((aStatus >= HTTPStatus::EContinue) && (aStatus < HTTPStatus::EOk));
	}
inline TBool HTTPStatus::IsSuccessful(TInt aStatus)
	{ 
	return ((aStatus >= HTTPStatus::EOk) && (aStatus < HTTPStatus::EMultipleChoices));
	}
inline TBool HTTPStatus::IsRedirection(TInt aStatus)
	{
	return ((aStatus >= HTTPStatus::EMultipleChoices) && (aStatus < HTTPStatus::EBadRequest));
	}
inline TBool HTTPStatus::IsClientError(TInt aStatus)
	{
	return ((aStatus >= HTTPStatus::EBadRequest) && (aStatus < HTTPStatus::EInternalServerError));
	}
inline TBool HTTPStatus::IsServerError(TInt aStatus)
	{
	return (aStatus >= HTTPStatus::EInternalServerError);
	}



// __HTTPERR_H__
#endif
