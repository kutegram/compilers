// Autogenerated from epoc32\BUILD\src\common\generic\application-protocols\http\framework\group\HTTP\ARMV5\HttpStringConstants.st by the stringtable tool - Do not edit

#ifndef STRINGTABLE_HTTP
#define STRINGTABLE_HTTP

#include <stringpool.h>

struct TStringTable;

/** A String table */
class HTTP 
	{
public:
	enum TStrings
		{
		/** CONNECT */
		ECONNECT,
		/** DELETE */
		EDELETE,
		/** GET */
		EGET,
		/** HEAD */
		EHEAD,
		/** OPTIONS */
		EOPTIONS,
		/** POST */
		EPOST,
		/** PUT */
		EPUT,
		/** TRACE */
		ETRACE,
		/** HTTP/1.0 */
		EHttp10,
		/** HTTP/1.1 */
		EHttp11,
		/** Cache-Control */
		ECacheControl,
		/** Connection */
		EConnection,
		/** Date */
		EDate,
		/** Pragma */
		EPragma,
		/** Transfer-Encoding */
		ETransferEncoding,
		/** Upgrade */
		EUpgrade,
		/** Via */
		EVia,
		/** Warning */
		EWarning,
		/** Host */
		EHost,
		/** Accept */
		EAccept,
		/** Accept-Charset */
		EAcceptCharset,
		/** Accept-Encoding */
		EAcceptEncoding,
		/** Accept-Language */
		EAcceptLanguage,
		/** Authorization */
		EAuthorization,
		/** Cookie */
		ECookie,
		/** Cookie2 */
		ECookie2,
		/** Expect */
		EExpect,
		/** From */
		EFrom,
		/** If-Modified-Since */
		EIfModifiedSince,
		/** If-Match */
		EIfMatch,
		/** If-None-Match */
		EIfNoneMatch,
		/** If-Range */
		EIfRange,
		/** If-Unmodified-Since */
		EIfUnmodifiedSince,
		/** Keep-Alive */
		EKeepAlive,
		/** Max-Forwards */
		EMaxForwards,
		/** Proxy-Authorization */
		EProxyAuthorization,
		/** Range */
		ERange,
		/** Referer */
		EReferer,
		/** User-Agent */
		EUserAgent,
		/** Accept-Ranges */
		EAcceptRanges,
		/** Age */
		EAge,
		/** ETag */
		EETag,
		/** Location */
		ELocation,
		/** Proxy-Authenticate */
		EProxyAuthenticate,
		/** Retry-After */
		ERetryAfter,
		/** Server */
		EServer,
		/** Set-Cookie */
		ESetCookie,
		/** Set-Cookie2 */
		ESetCookie2,
		/** Vary */
		EVary,
		/** WWW-Authenticate */
		EWWWAuthenticate,
		/** Allow */
		EAllow,
		/** Content-Base */
		EContentBase,
		/** Content-Disposition */
		EContentDisposition,
		/** Content-Encoding */
		EContentEncoding,
		/** Content-Language */
		EContentLanguage,
		/** Content-Length */
		EContentLength,
		/** Content-Location */
		EContentLocation,
		/** Content-MD5 */
		EContentMD5,
		/** Content-Range */
		EContentRange,
		/** Content-Type */
		EContentType,
		/** Expires */
		EExpires,
		/** Last-Modified */
		ELastModified,
		/** q */
		EQ,
		/** gzip */
		EGzip,
		/** compress */
		ECompress,
		/** deflate */
		EDeflate,
		/** bytes */
		EBytes,
		/** none */
		ENone,
		/** no-cache */
		ENoCache,
		/** no-store */
		ENoStore,
		/** max-age */
		EMaxAge,
		/** max-stale */
		EMaxStale,
		/** min-fresh */
		EMinFresh,
		/** no-transform */
		ENoTransform,
		/** only-if-cached */
		EOnlyIfCached,
		/** public */
		EPublic,
		/** private */
		EPrivate,
		/** must-revalidate */
		EMustRevalidate,
		/** proxy-revalidate */
		EProxyRevalidate,
		/** s-maxage */
		ESMaxAge,
		/** close */
		EClose,
		/** charset */
		ECharset,
		/** 100-continue */
		E100Continue,
		/** TE */
		ETE,
		/** Trailer */
		ETrailer,
		/** chunked */
		EChunked,
		/** Basic */
		EBasic,
		/** Digest */
		EDigest,
		/** realm */
		ERealm,
		/** domain */
		EDomain,
		/** nonce */
		ENonce,
		/** opaque */
		EOpaque,
		/** stale */
		EStale,
		/** algorithm */
		EAlgorithm,
		/** qop */
		EQop,
		/** auth */
		EAuth,
		/** response */
		EResponse,
		/** uri */
		EUri,
		/** cnonce */
		ECnonce,
		/** nc */
		ENc,
		/** 00000001 */
		E00000001,
		/** _000 */
		EPort,
		/** _Auth */
		EAuthentication,
		/** _Red */
		ERedirect,
		/** _Val */
		EValidation,
		/** _ProtH */
		EProtocolHandler,
		/** Client */
		EClient,
		/** _clf */
		EHttpClientFilter,
		/** _shf */
		ESessionHeaderFilter,
		/** _ckf */
		ECookieFilter,
		/** _cnf */
		EHttpConnectFilter,
		/** _001 */
		EProxyUsage,
		/** _002 */
		EProxyAddress,
		/** _003 */
		EUseProxy,
		/** _004 */
		EDoNotUseProxy,
		/** _005 */
		EMaxNumTransportHandlers,
		/** _006 */
		EMaxNumTransPerTranspHndlr,
		/** _007 */
		EHTTPVersion,
		/** _008 */
		EMaxRedirect,
		/** Protocol */
		EProtocol,
		/** HTTP */
		EHTTP,
		/** HTTPS */
		EHTTPS,
		/** WSP */
		EWSP,
		/** _009 */
		EWspCapClientMessageSize,
		/** _00A */
		EWspCapServerMessageSize,
		/** _00B */
		EWspCapUseAcknowledgements,
		/** _00C */
		EWspCapSupportSuspendResume,
		/** _00D */
		EWspCapMaxOutstandingRequests,
		/** _00E */
		EWspProxyAddress,
		/** _00F */
		EWspBearer,
		/** _010 */
		EWspIp,
		/** _011 */
		EWspSMS,
		/** _012 */
		EWspLocalPort,
		/** _013 */
		EWspRemotePort,
		/** _014 */
		EWspServiceNumber,
		/** _015 */
		EWspSessionType,
		/** _016 */
		EWspConnectionOriented,
		/** _017 */
		EWspConnectionLess,
		/** _018 */
		EWspSecurity,
		/** _019 */
		EWspUseWtls,
		/** _01A */
		EWspDoNotUseWtls,
		/** _01B */
		EWspProxyConnectionTimeout,
		/** _01C */
		EWspProxyExceptionInfo,
		/** _01D */
		EWspRemainingSDUSize,
		/** _01E */
		EWspRemainingMessageSize,
		/** _01F */
		EAuthenticatedOK,
		/** _020 */
		EAuthenticationFailure,
		/** username */
		EUsername,
		/** Password */
		EPassword,
		/** Authentication:Status */
		EAuthenticationStatus,
		/** _021 */
		ERedirectCount,
		/** _022 */
		EProtTrans,
		/** * / * */
		EAnyAny,
		/** text/ * */
		ETextAny,
		/** text/html */
		ETextHtml,
		/** text/plain */
		ETextPlain,
		/** text/vnd.wap.wml */
		ETextVndWapWml,
		/** application/octet-stream */
		EApplicationOctetStream,
		/** application/x-www-form-urlencoded */
		EApplicationXWwwFormUrlEncoded,
		/** _023 */
		ECookieName,
		/** _024 */
		ECookieValue,
		/** Path */
		EPath,
		/** Comment */
		EComment,
		/** CommentURL */
		ECommentURL,
		/** Discard */
		EDiscard,
		/** Port */
		ECookiePort,
		/** Secure */
		ESecure,
		/** Version */
		EVersion,
		/** _025 */
		EHttpSocketServ,
		/** _026 */
		EHttpSocketConnection,
		/** _027 */
		ESecureDialog,
		/** _028 */
		EDialogPrompt,
		/** _029 */
		EDialogNoPrompt,
		/** _02A */
		ETunnel,
		/** _02B */
		EHttpPipelining,
		/** _02C */
		EEnablePipelining,
		/** _02D */
		EDisablePipelining,
		/** _02E */
		ECipherSuiteValue,
		/** _2F */
		EHttpBatching,
		/** _030 */
		EDoNotEnableBatching,
		/** _031 */
		EEnableBatching,
		/** _32 */
		EBatchingBufferSize,
		/** _033 */
		ESocketShutdownMode,
		/** _034 */
		ESocketShutdownNormal,
		/** _035 */
		ESocketShutdownImmediate,
		/** _036 */
		ESessionClosing,
		/** Profile */
		EProfile,
		/** Profile-Diff */
		EProfileDiff,
		/** _UaProf */
		EUAProfFilter,
		/** _037 */
		EMaxNumTransactionsToPipeline,
		/** _038 */
		ESessionId,
		/** _03A */
		ENotifyOnDisconnect,
		/** _03B */
		EEnableDisconnectNotification,
		/** _03C */
		EDisableDisconnectNotification,
		/** _03D */
		ERecvBufferSize,
		/** _03E */
		EHTTPTransOptimiser,
		/** _03F */
		EEnableHTTPTransOptimiser,
		/** _040 */
		EDisableHTTPTransOptimiser,
		/** NTLM */
		ENTLM,
		/** _041 */
		ENotify100Continue,
		/** _042 */
		EEnableNotification,
		/** _043 */
		EDisableNotification,
		/** _051 */
		ESendTimeOutValue,
		/** _052 */
		EReceiveTimeOutValue
		};
	static const TStringTable Table;	
	};

// STRINGTABLE_HTTP
#endif

