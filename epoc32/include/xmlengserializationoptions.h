/*
* ==============================================================================
*  Name        : xmlengserializationoptions.h
*  Part of     : XmlEngine / DOM XPath C++ Wrapper
*  Interface   : Domain, XML Engine DOM API
*  Description : Serialization options functions
*  Version     : %version: 2 % 
*
*  Copyright � 2004-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/


#ifndef XMLENGINE_SERIALIZATIONOPTIONS_H_INCLUDED
#define XMLENGINE_SERIALIZATIONOPTIONS_H_INCLUDED

#include <e32base.h>

// FORWARD DECLARATION
class MXmlEngOutputStream;
class MXmlEngDataSerializer;
class MXmlEngNodeFilter;

/**
 * Class allow to set serialization option during document save.
 * 
 * @lib XmlEngineDOM.lib
 * @since S60 v3.1
 */
class TXmlEngSerializationOptions 
	{
public:
    /** Use indent in output */
    static const TUint KOptionIndent                 = 0x01;
    /** Skip xml declaration */
	static const TUint KOptionOmitXMLDeclaration     = 0x02;
	/** Add standalone in xml declaration. KOptionOmitXMLDeclaration must not be set */
	static const TUint KOptionStandalone             = 0x04;
	/** Add encoding in xml declaration. KOptionOmitXMLDeclaration must not be set */
	static const TUint KOptionEncoding               = 0x08;
	/** Not supported currently */
	static const TUint KOptionIncludeNsPrefixes      = 0x10;
	/** Not supported currently */
	static const TUint KOptionCDATASectionElements   = 0x20;
	/** Decode base64 encoded binary containers content upon XOP serialization*/
	static const TUint KOptionDecodeBinaryContainers		 = 0x40;	
    
	/**
     * Constructor
     *
     * @since S60 v3.1
	 * @param aOptionFlags Serialization options
     * @param aEncoding Serialization encoding
     */
    IMPORT_C TXmlEngSerializationOptions( TUint aOptionFlags = 
    								   (TXmlEngSerializationOptions::KOptionIndent | 
    									TXmlEngSerializationOptions::KOptionStandalone |
    									TXmlEngSerializationOptions::KOptionEncoding), 
                                    const TDesC8& aEncoding = KNullDesC8);

	/**
     * Set node filter
     *
     * @since S60 v3.1
	 * @param aFilter New node filter
     */
    IMPORT_C void SetNodeFilter(MXmlEngNodeFilter* aFilter);  

public:
	/** Options flag */
    TUint iOptions;
	/** Encoding */
    TPtrC8 iEncoding;
	/** Node filter */
    MXmlEngNodeFilter* iNodeFilter;
    /** Object whose serialization callback is invoked **/
    MXmlEngDataSerializer* iDataSerializer;
	};



#endif /* XMLENGINE_SERIALIZATIONOPTIONS_H_INCLUDED */
