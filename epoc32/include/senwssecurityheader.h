/*
* ==============================================================================
*  Name        : SenWsSecurityHeader.h
*  Part of     : Web Services Framework / Utils
*  Interface   : 
*  Description : CSenWsSecurityHeader represents security header functionality
*                according to oasis wss spesifications (2004/01)
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


#ifndef SEN_WS_SECURITY_HEADER_H
#define SEN_WS_SECURITY_HEADER_H

//  INCLUDES
#include <SenBaseFragment.h>
#include <SenSoapConstants.h>


// FORWARD DECLARATIONS
class CSenIdentityProvider;

// CLASS DECLARATION

/**
* CSenWsSecurityHeader represents security header functionality according to 
* oasis web services security (WSS) specifications (2004/01) or older (2003/06)
* @lib SenUtils.lib
* @since Series60 3.0
*/
class CSenWsSecurityHeader : public CSenBaseFragment
    {
    public:  // Constructors and destructor

		/**
		* PasswordType Enumeration
		*/
        enum TPasswordType
            {
            EText = 1,        // default, wsse:PasswordText
            EDigest           // wsse:Digest
            };

        
        /**
        * Basic constructor.
        * @return a pointer to new CSenWsSecurityHeader class instance.
        */
        IMPORT_C static CSenWsSecurityHeader* NewL();
        
        /**
        * Basic constructor.
        * @return a new CSenWsSecurityHeader class instance, which pointer
        * is left on cleanup stack.
        */
        IMPORT_C static CSenWsSecurityHeader* NewLC();

        
        /**
        * Basic constructor.
        * @param    aData   Data to be set as header's content.
        * @return a pointer to new CSenWsSecurityHeader class instance.
        */
        IMPORT_C static CSenWsSecurityHeader* NewL(const TDesC8& aData);

        /**
        * Basic constructor.
        * @param    aData   Data to be set as header's content.
        * @return a new CSenWsSecurityHeader class instance, which pointer
        * is left on cleanup stack.
        */
        IMPORT_C static CSenWsSecurityHeader* NewLC(const TDesC8& aData);
        
        /**
        * Basic constructor.
        * @param    aData           Data to be set as header's content.
        * @param    aSecurityNs     A namespace to be set to the header.
        * @return a pointer to new CSenWsSecurityHeader class instance.
        */
        IMPORT_C static CSenWsSecurityHeader* NewL(const TDesC8& aData, const TDesC8& aSecurityNs);

        /**
        * Basic constructor.
        * @param    aData           Data to be set as header's content.
        * @param    aSecurityNs     A namespace to be set to the header.
        * @return a new CSenWsSecurityHeader class instance, which pointer
        * is left on cleanup stack.
        */
        IMPORT_C static CSenWsSecurityHeader* NewLC(const TDesC8& aData, const TDesC8& aSecurityNs);

        /**
        * Destructor.
        */
        IMPORT_C virtual ~CSenWsSecurityHeader();

        // New functions
    
        /**
        * Constructs a username token.
        * @since Series60 3.0
        * @param  aIdentityProvider  Identity provider which is used to get
        * the authorization ID used in username token. Method takes the
        * AuthzID out from aIdentityProvider, and uses it as username for
        * this token.
        * Format of the token is as follows:
        *
        * <wsse:UsernameToken>
        *   <wsse:Username>
        *       username
        *   </wsse:Username>
        * </wsse:UsernameToken>"
        *
        * The above token assumes, that wsse namespace is declared in 
        * top level of the security header.
        * @return a pointer to buffer containing the username token. Does not
        * return NULL. Ownership is transferred to the caller. Method leaves
        * with value KErrNotSupported, if a password type is not supported.
        */
        IMPORT_C HBufC8* UsernameTokenL(CSenIdentityProvider &aIdentityProvider);

        /**
        * Constructs a username token.
        * @since Series60 3.0
        * @param  aIdentityProvider  Identity provider which is used to get
        * the authorization ID used in username token. Method takes the
        * AuthzID out from aIdentityProvider, and uses it as username for
        * this token. Password is also fetched from aIdentityProvider via
        * calling Password() getter, which must return a Base64 [XML-Schema]
        * encoded, SHA-1 hash value, of the UTF8 encoded password.
        * @param  aType Specifies the type of the password, either
        * wsse:PasswordText or wsse:PasswordDigest
        *
        * Format of the token is as follows (if password type is wsse:PasswordText):
        *
        * <wsse:UsernameToken>
        *   <wsse:Username>
        *       username
        *   </wsse:Username>
        *   <wsse:Password>
        *       password
        *   </wsse:Password>
        * </wsse:UsernameToken>"
        *
        * If the password type is wsse:Password:Digest, then the password element
        * will be declared as follows:
        *
        *   <wsse:Password Type="wsse:PasswordDigest">
        *
        * The above token assumes, that wsse namespace is declared in 
        * top level of the security header.
        * @return a pointer to buffer containing the username token. Does not
        * return NULL. Ownership is transferred to the caller. Method leaves
        * with value KErrNotSupported, if a password type is not supported.
        */
        IMPORT_C HBufC8* UsernameTokenL(CSenIdentityProvider &aIdentityProvider,
                                        CSenWsSecurityHeader::TPasswordType aType);

        // Static methods:

        /**
        * Constructs a username token. This method does not add the <Password>
        * element, since it is optional for basic username tokens.
        * @since Series60 3.0
        * @param  aUsername     User name which is used in the username 
        *                       token.
        * @param  aToken        Ref-to-pointer where the token will be
        *                       allocated. Shouldn't contain any data when
        *                       called, or that data will be lost.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt UsernameTokenL(const TDesC8& aUsername,
                                            HBufC8*& aToken);

        /**
        * Constructs a username token using a password, too.
        * @since S60 5.0
        * @param  aUsername     User name which is to be used in new token.
        * @param  aPassword     Password which is to be use in new token.
        *                       The type will be set to default: wsse:PasswordDigest,
        *                       defined in KSecurityAttrTypeText. This is
        *                       a Base64 [XML-Schema] encoded, SHA-1 hash value, 
        *                       of the UTF8 encoded password.
        * @param  aToken        Ref-to-pointer in which the token will be
        *                       allocated. Shouldn't contain any data when
        *                       called, or that data will be lost.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt UsernameTokenL(const TDesC8& aUsername,
                                            const TDesC8& aPassword,
                                            HBufC8*& aToken);

       /**
        * Constructs a username token using a password, too.
        * @since S60 5.0
        * @param  aUsername     User name which is to be used in new token.
        * @param  aPassword     Password which is to be use in new token
        *                       This is a Base64 [XML-Schema] encoded, SHA-1 
        *                       hash value, of the UTF8 encoded password.
        * @param  aType         Specifies the type of the password:
        *                       - EText, being default refers to wsse:PasswordText,
        *                       but this method does not add this, since it can
        *                       be omitted.
        *                       - EDigest: will add wsse:PasswordDigest attribute
        *                       to the <Password> -element, as in here:
        *
        *                        <wsse:UsernameToken>
        *                           <wsse:Username>
        *                               username
        *                           </wsse:Username>
        *                           <wsse:Password Type="wsse:PasswordDigest">
        *                               password
        *                           </wsse:Password>
        *                         </wsse:UsernameToken>"
        *                        
        * @param  aToken        Ref-to-pointer where the token will be
        *                       allocated. Shouldn't contain any data when
        *                       called, or that data will be lost.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt UsernameTokenL(const TDesC8& aUsername,
                                            const TDesC8& aPassword,
                                            CSenWsSecurityHeader::TPasswordType aType,
                                            HBufC8*& aToken);


       /**
        * Constructs a BinarySecurityToken.
        * @since S60 5.0
        *                        
        * @param  aContent      Encoded EncryptedData which is to be used in token.
        * @param  aToken        Ref-to-pointer where the token will be
        *                       allocated. Shouldn't contain any data when
        *                       called, or that data will be lost.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt BinarySecurityTokenL(const TDesC8& aContent,
                                                  HBufC8*& aToken);
        /**
        * Constructs a BinarySecurityToken.
        * @since S60 5.0
        *                        
        * @param  aContent      Encoded EncryptedData which is to be used in token.
        * @param  aValueType  Indicates what the security token is
        * @param  aToken        Ref-to-pointer where the token will be
        *                       allocated. Shouldn't contain any data when
        *                       called, or that data will be lost.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt BinarySecurityTokenL(const TDesC8& aContent,
                                                  const TDesC8& aValueType,
                                                  HBufC8*& aToken);

        /**
        * Constructs a timestamp.
        * @since S60 5.0
        * Format of the timestamp is as follows:
        *   <wsu:Timestamp xmlns:wsu="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd">
        *       <wsu:Created>2001-09-13T08:42:00Z</wsu:Created>
        *       <wsu:Expires>2002-09-13T08:42:00Z</wsu:Expires>
        *   </wsu:Timestamp>
        * The wsu namespace is declared inside this element.
        *   Based on chapter 10 from WS-Security 2004
        * @param aCreated - creation time of token
        * @param aExpires - end of validation time for token
        * @param aTimestamp - a pointer to buffer containing the timestamp. Does not
        *         return NULL. Ownership is transferred to the caller.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt TimestampL(const TDesC8& aCreated, const TDesC8& aExpires, HBufC8*& aTimestamp);
        
        /**
        * Constructs a timestamp.
        * @since S60 5.0
        * Format of the timestamp is as follows:
        *   <wsu:Timestamp xmlns:wsu="http://docs.oasis-open.org/wss/2004/01/oasis-200401-wss-wssecurity-utility-1.0.xsd">
        *       <wsu:Created>2001-09-13T08:42:00Z</wsu:Created>
        *   </wsu:Timestamp>
        * The wsu namespace is declared inside this element.
        *   Based on chapter 10 from WS-Security 2004
        * @param aCreated - creation time of token
        * @param aTimestamp - a pointer to buffer containing the timestamp. Does not
        *         return NULL. Ownership is transferred to the caller.
        * @return KErrNone or some system-wide Symbian error code.
        */
        IMPORT_C static TInt TimestampL(const TDesC8& aCreated, HBufC8*& aTimestamp);

        /**
        * Constructs a security token reference.
        * @since S60 5.0
        * Format of the token reference is as follows:
        *   <wsse:SecurityTokenReference wsu:Id="...">
        *       <wsse:Reference URI="..."/>
        *   </wsse:SecurityTokenReference>
        *
        * The above token assumes, that wsse namespace is declared in 
        * top level of the security header.
        * @param  
        * @param aSTR - a pointer to buffer containing the token reference. Does not
        *         return NULL. Ownership is transferred to the caller.
        * @return KErrNone or some system-wide Symbian error code.
        */
// TODO: implement:
//        IMPORT_C static TInt SecurityTokenReferenceL(const TDesC8& aURI, HBufC8*& aSTR); 

       
        // Virtual methods: 

        /** Basic getter for XML namespace of the WS security header.
        * Subclasses should override this to use different namespace 
        * @since Series60 3.0
        * @return the WS security header namespace as string
        */
        IMPORT_C virtual TPtrC8 XmlNs();
        
        /**
        * Basic getter for XML namespace prefix of the WS security header.
        * Subclasses should override this to use different namespace prefix
        * @since Series60 3.0
        * @return the WS security header namespace prefix as string
        */
        IMPORT_C virtual TPtrC8 XmlNsPrefix();    
        
    protected:  
        
        /**
        * C++ default constructor
        */
        IMPORT_C CSenWsSecurityHeader();
        
        /**
        * Basic BaseConstructL function 
        */
        IMPORT_C void BaseConstructL();
        
        // Functions from base classes
        
        /**
        * From CSenBaseFragment Basic BaseConstructL function 
        * @since Series60 3.0
        * @param aData will be used as current token (content) of this security 
        *        header
        */
        IMPORT_C void BaseConstructL(const TDesC8& aData);
        IMPORT_C void BaseConstructL(const TDesC8& aData, const TDesC8& aSecurityNs);
    };

#endif // SEN_WS_SECURITY_HEADER_H

// End of File
