// attribute.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

#ifndef __ATTRIBUTE_H__
#define __ATTRIBUTE_H__

#include <xml/taginfo.h>

namespace Xml
{

enum TAttributeType
/**
Specifies the type of this attribute object.
These values are defined in the xml specification.
For other specifications they may also be used or 'none'.
@see http://www.w3.org/TR/REC-xml#sec-attribute-types

@publishedAll

*/
	{
/**
Specifies a string type.
*/
	EAttributeType_CDATA,

/**
Specifies a tokenized type.
*/
	EAttributeType_ID,

/**
Specifies a tokenized type.
*/		
	EAttributeType_IDREF,

/**
Specifies a tokenized type.
*/	
	EAttributeType_IDREFS,

/**
Specifies a tokenized type.
*/	
	EAttributeType_NMTOKEN,

/**
Specifies a tokenized type.
*/	
	EAttributeType_NMTOKENS,

/**
Specifies a tokenized type.
*/	
	EAttributeType_ENTITY,

/**
Specifies a tokenized type.
*/	
	EAttributeType_ENTITIES,

/**
Specifies a tokenized type.
*/	
	EAttributeType_NOTATION,

/**
Specifies no type, or unsupported.
*/	
	EAttributeType_NONE,

	};




class RAttribute
/**
The RAttribute class holds an attribute's description belonging to an element.
@see RAttributeArray

@publishedAll

*/
	{
public:

/**
@publishedPartner

*/
	IMPORT_C RAttribute();

/**
@publishedPartner

*/
	IMPORT_C RAttribute Copy();

/**
@publishedPartner

*/
	IMPORT_C void Close();

/**
@publishedPartner

*/
	IMPORT_C void Open(const RString& aUri, const RString& aPrefix, const RString& aLocalName,
					   const TAttributeType aType = EAttributeType_NONE);
					   
/**
@publishedPartner

*/
	IMPORT_C void Open(const RString& aUri, const RString& aPrefix, const RString& aLocalName,
					   const RString& aValue, const TAttributeType aType = EAttributeType_NONE);

	IMPORT_C const RTagInfo& Attribute() const;
	IMPORT_C const RString& Value() const;
	IMPORT_C TAttributeType Type() const;

/**
@publishedPartner

*/
	IMPORT_C void SetValue(const RString& aValue);

private:

/**
Holds information about the attribute.
*/
	RTagInfo iAttribute;

/**
Holds the attribute's value.
*/
	RString iValue;

/**
Holds the attribute's type.
*/
	TAttributeType iType;

	};


/**
Defines a list of attributes for an element.
@see MContentHandler

@publishedAll

*/
typedef RArray<RAttribute> RAttributeArray; 

}

//__ATTRIBUTE_H__
#endif
