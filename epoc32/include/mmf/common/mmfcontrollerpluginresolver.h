// mmf\common\mmfcontrollerpluginresolver.h
//
// Copyright (c) Symbian Software Ltd 2002-2006.  All rights reserved.
//
#ifndef MMF_COMMON_MMFCONTROLLERPLUGINRESOLVER_H
#define MMF_COMMON_MMFCONTROLLERPLUGINRESOLVER_H

#include <ecom/ecom.h>
#include <e32base.h>
#include <apmstd.h>

/**
@publishedAll


Default heap size for the controller thread
*/
const TUint KMMFDefaultControllerThreadHeapSize = 0x100000; //1MB


class CMMFFormatImplementationInformation;

/**
@publishedAll


Array of CMMFFormatImplementationInformation 
*/
typedef RPointerArray<CMMFFormatImplementationInformation> RMMFFormatImplInfoArray;

class CMMFControllerImplementationInformation;

/**
@publishedAll


Array of CMMFControllerImplementationInformation 
*/
typedef RPointerArray<CMMFControllerImplementationInformation> RMMFControllerImplInfoArray;

/**
@internalComponent

Interface to be implemented by customers of the class TaggedDataParser.
*/
class MTaggedDataParserClient
	{
public:
	virtual void ProcessTaggedDataL(const TDesC8& aTag, const TDesC8& aData) = 0;
	};

/**
@internalComponent

Utility class used to parse data separated by xml-style tags.
*/
class TaggedDataParser
	{
public:

	/**
	Splits aData into xml-style tags and values, and gets aClient to process each tag/value pair.
	*/
	static void ParseTaggedDataL(const TDesC8& aData, MTaggedDataParserClient& aClient);

	/**
	Converts a string to a uid. If the string begin with "0x" it will be parsed as Hex, else Decimal.
	*/
	static void ConvertTextToUidL(const TDesC8& aData, TUid& aUid);

	/**
	Converts a string to a TUint. The string must begin with "0x" and be 10 characters long,
	otherwise it is considered corrupt.
	*/
	static void ConvertTextToTUintL(const TDesC8& aData, TUint& aUid);

	};

class CMatchData;

class CDesC8Array;

/**
@publishedAll

Abstract class that contains basic information about ECom Multimedia plugins.



*/
class CMMFPluginImplementationInformation : public CBase
	{
public:

	/**
	Returns the uid of this particular plugin implementation.
	This is the UID used to instantiate this multimedia plugin.

	@return The implementation uid.

	
	*/
	IMPORT_C TUid Uid() const;

	/**
	Returns the display name of this plugin implementation.

	@return The display name.

	
	*/
	IMPORT_C const TDesC& DisplayName() const;

	/**
	Returns the name of the supplier of this plugin implementation, e.g. "Symbian".

	@return The plugin supplier.

	
	*/
	IMPORT_C const TDesC& Supplier() const;

	/**
	Returns the version number of this plugin.

	@return The version number.

	
	*/
	IMPORT_C TInt Version() const;

	/**
	Returns the array of media IDs supported by this plugin.
	
	The media ID can be used by clients to determine whether the plugin supports audio or
	video data (or both). A UID is used for the media ID to provide future extensibility.

	@return The array of media IDs.

	
	*/
	IMPORT_C const RArray<TUid>& SupportedMediaIds() const;

	/**
	Tests whether this plugin was supplied by aSupplier.

	@param  aSupplier
	        The required supplier.

	@return A boolean indicating if this plugin was supplied by aSupplier. ETrue if this plugin was supplied 
	        by aSupplier, EFalse if not.

	
	*/
	IMPORT_C TBool SupportsSupplier(const TDesC& aSupplier) const;

	/**
	Tests whether this plugin supports aMediaId.

	@param  aMediaId
	        The required media id.

	@return A boolean indicating if the plugin supports aMediaId. ETrue if this plugin supports aMediaId, EFalse if not.

	
	*/
	IMPORT_C TBool SupportsMediaId(TUid aMediaId) const;

	/**
	Destructor.
	*/
	virtual ~CMMFPluginImplementationInformation();

protected:

	/**
	Constructor.
	*/
	CMMFPluginImplementationInformation();

	/** 
	Sets the supplier. Takes a copy of aData.
	*/
	void SetSupplierL(const TDesC8& aData);

	/**
	Adds a media id. aData is parsed to find the uid of the media id to be added.
	*/
	void AddMediaIdL(const TDesC8& aData);
	
protected:

	/** 
	The UID of this plugin. 
	*/
	TUid iUid;

	/** 
	The display name of this plugin. 
	*/
	HBufC* iDisplayName;

	/** 
	The supplier of this plugin. 
	*/
	HBufC* iSupplier;

	/** 
	The version number of this plugin. 
	*/
	TInt iVersion;

	/**
	The media ids supported by this plugin.
	*/
	RArray<TUid> iMediaIds;
	};

/**
@publishedAll


Contains format support information retrieved from the ECom registry.

An object of this type may describe either a concrete format plugin (ie a CMMFFormatEncode or a
CMMFFormatDecode implementation) or a format supported by a controller plugin.

The object is created using a CImplementationInformation object retrieved from the ECom registry.
All relevant data is copied out of the CImplementationInformation object, and its opaque data is
parsed to provide the supplier, supported media ids, supported mime types, supported file extensions,
and supported header data matches.

Notes for Format Plugin developers:
@code
The opaque data section of the ECom plugin resource file must be in the format:

opaque_data = "<?>Data 1<?>Data 2<?>Data 3<?>Data 4[...]<?>Data N";

The <?> preceding the data determines the meaning of the data.  The following are the possible tags:

	<s> - Supplier
	<i> - Media Id
	<m> - Mime Type
	<e> - File Extension
	<h> - Header Data
	<c> - Custom Interfaces

UIDs must always be in hex in the format '0x12345678', must include the '0x' and be 10 characters long
@endcode


*/
class CMMFFormatImplementationInformation : public CMMFPluginImplementationInformation, MTaggedDataParserClient
	{
public:
	/**
	Constructs a new format implementation information object.

	@param  aImplInfo
	        The ECOM implementation information

	@return The new object created.

	
	*/
	static CMMFFormatImplementationInformation* NewL(const CImplementationInformation& aImplInfo);

	/**
	Constructs a new format implementation information object.

	@param  aImplInfo
	        The ECOM implementation information

	@return The new object created. Note that this will be on the cleanup stack.

	
	*/
	static CMMFFormatImplementationInformation* NewLC(const CImplementationInformation& aImplInfo);

	/** 
	Destructor 
	*/
	virtual ~CMMFFormatImplementationInformation();

	/**
	Returns the array of supported file extensions.

	@return The array of file extensions.
	
	*/
	IMPORT_C const CDesC8Array& SupportedFileExtensions() const;

	/**
	Returns the array of supported mime types.

	@return The array of mime types.

	
	*/
	IMPORT_C const CDesC8Array& SupportedMimeTypes() const;

	/**
	Returns the array of supported header data matches.

	@return The array of header data.
	
	*/
	IMPORT_C const CDesC8Array& SupportedHeaderData() const;

	/**
	Tests whether this format provides support for the specified file extension, aFileExtension.

	@param  aFileExtension
	        The requested file extension. Must be the extension only, and contain the dot '.'

	@return A boolean indicating if the specified file extension is supported. ETrue if this format provides 
	        the required support, EFalse if it does not.

	
	*/
	IMPORT_C TBool SupportsFileExtension(const TDesC8& aFileExtension) const;

	/**
	Tests whether this format provides support for aMimeType.

	@param  aMimeType
	        The requested mime type.

	@return A boolean indicating if the format is supported. ETrue if this format provides the required support, EFalse if not.

	
	*/
	IMPORT_C TBool SupportsMimeType(const TDesC8& aMimeType) const;

	/**
	Tests whether this format provides support for aHeaderData.
	aHeaderData is searched for each chunk supported by this format.

	@param	aHeaderData
	        The requested header data.
	        
	@return A boolean indicating if aHeaderData is supported. ETrue if this format provides the required support, EFalse if not.

	
	*/
	IMPORT_C TBool SupportsHeaderDataL(const TDesC8& aHeaderData) const;

	/**
	Tests whether this format provides support for Custom Interfaces.
        
	@return A boolean indicating if Custom Interfaces are supported. ETrue if this format provides the required support, EFalse if not.
	*/
	IMPORT_C TBool SupportsCustomInterfaces() const;

protected:

	/** 
	Constructor 
	*/
	CMMFFormatImplementationInformation();

	/** 
	2nd phase constructor 
	*/
	void ConstructL(const CImplementationInformation& aImplInfo);

	/** 
	Adds a file extension to the array of extensions supported by this format. 
	*/
	void AddFileExtensionL(const TDesC8& aData);

	/**
	Adds a mime type to the array of types supported by this format.
	*/
	void AddMimeTypeL(const TDesC8& aData);

	/** 
	Adds a chunk of header data to the array of chunks supported by this format.
	*/
	void AddHeaderDataL(const TDesC8& aData);

	/** 
	from MTaggedDataParserClient 
	*/
	void ProcessTaggedDataL(const TDesC8& aTag, const TDesC8& aData);

private:
	class CBody;
	/** 
	CMMFFormatImplementationInformation body
	*/
	CBody* iBody;
	};


/**
@publishedAll


Contains controller plugin information retrieved from the ECom registry.

The object is created using a CImplementationInformation object retrieved from the ECom registry.
All relevant data is copied out of the CImplementationInformation object, and its opaque data is
parsed to provide the supplier, supported media IDs.

Notes for Format Plugin developers:
The exact formats supported by the controller plugin are calculated by:

1. The formats supported by the controller plugin itself must be declared in separate entries in the
controller plugin resource file.  Two interface UIDs should be defined by the plugin writer - one
for the play formats supported, the other for the record formats supported.  The play formats are
then listed as implementations of the play format interface uid, and likewise the record formats.

2. Format plugins (CMMFFormatEncode and CMMFFormatDecode) declare which controller plugin they
extend.  ECom is search for the format plugins that extend the controller plugin, and they
are added to the list.

The opaque data section of the ECom plugin resource file must be in the format:
@code

opaque_data = "<?>Data 1<?>Data 2<?>Data 3<?>Data 4[...]<?>Data N";

The <?> preceding the data determines the meaning of the data.  The following are the possible tags:

	<s> - Supplier - must be only one
	<i> - Media Id
	<p> - UID of play format 'interface' - must be only one
	<r> - UID of record format 'interface' - must be only one

UIDs must always be in hex in the format '0x12345678', must include the '0x' and be 10 characters long.
@endcode


*/
class CMMFControllerImplementationInformation : public CMMFPluginImplementationInformation, MTaggedDataParserClient
	{
public:

	/**
	Constructs a new controller implementation information object.

	@param  aImplInfo
	        The ECOM implementation information.

	@return The new object created.
	
	@internalTechnology

	
	*/
	static CMMFControllerImplementationInformation* NewL(const CImplementationInformation& aImplInfo);

	/**
	Constructs a new controller implementation information object.

	Note: 
	The new object will be on the cleanup stack.

	@param  aImplInfo
	        The ECOM implementation information

	@return The new object created.
	
	@internalTechnology

	
	*/
	static CMMFControllerImplementationInformation* NewLC(const CImplementationInformation& aImplInfo);

	/**
	Constructs a new controller implementation information object.

	@param  aUid
	        The Uid of the controller to obtain controller implementation information

	@return The new object created.

	
	*/
	IMPORT_C static CMMFControllerImplementationInformation* NewL(TUid aUid);

	/**
	Destructor.
	
	@internalTechnology
	*/
	~CMMFControllerImplementationInformation();

	/**
	Returns the array of play formats supported by this controller.

	@return The play formats supported.

	
	*/
	IMPORT_C const RMMFFormatImplInfoArray& PlayFormats() const;

	/**
	Returns the array of record formats supported by this controller.

	@return The record formats supported.

	
	*/
	IMPORT_C const RMMFFormatImplInfoArray& RecordFormats() const;

	/**
	Returns the heap space required by this controller.

	@return The heap space required.

	
	*/
	IMPORT_C TUint HeapSpaceRequired() const;
	
	/**
	Queries the ECom registry for the play formats supported. 
	
	@internalTechnology
	*/
	void GetPlayFormatsL();

	/** 
	Queries the ECom registry for the record formats supported.
	
	@internalTechnology
	*/
	void GetRecordFormatsL();
	
	/**
	Returns the uri schemes of this plugin.

	@return The array of uri schemes.

	@internalTechnology
	*/
	IMPORT_C const CDesC8Array& SupportedUriSchemes() const;
	
	/**
	Tests whether the plugin supports aUriScheme.
	
	@param  aUriScheme
	        The required Uri Scheme.

	@return A boolean indicating if the plugin supports aUriScheme. ETrue if this plugin supports aUriScheme, EFalse if not.

	@internalTechnology
	*/
	IMPORT_C TBool SupportsUriScheme(const TDesC8& aUriScheme) const;
	
	/**
	Tests whether the controller plugin supports url
		
	@return A boolean indicating if the plugin supports url. ETrue for uri supporting controller, EFalse if not.
	
	@internalTechnology
	*/
	IMPORT_C TBool SupportsNetworkCapability() const;
	
	/**
	Sets the uri priority of this controller
	
	@param  aUriPriority
	        The Uri priority to be assigned.
	        
	@internalTechnology
	*/
	IMPORT_C void SetUriPriority(TInt aUriPriority);
	
	/**
	Retrieves the uri priority of this controller. 
	Higher priority implies greater number. ie UriPriority() returning 3 
	has higher prioirty than UriPriority() returning 1.
	
	@return  The assigned Uri priority.
	
	@internalTechnology
	*/
	IMPORT_C TInt UriPriority() const;
	
protected:

	/**
	Constructor.
	
	@internalTechnology
	*/
	CMMFControllerImplementationInformation();

	/**
	2nd phase constructor.
	
	@internalTechnology
	*/
	void ConstructL(const CImplementationInformation& aImplInfo);

	/**
	Parses aData to get the collection UID of the play formats supported by this controller.
	
	@internalTechnology
	*/
	void SetPlayFormatCollectionUidL(const TDesC8& aData);

	/**
	Parses aData to get the collection UID of the record formats supported by this controller.
	
	@internalTechnology
	*/
	void SetRecordFormatCollectionUidL(const TDesC8& aData);

	/**
	Parses aData to get the size of the stack the controller requires.
	
	@internalTechnology
	*/
	void SetHeapSizeL(const TDesC8& aData);

	/**
	From MTaggedDataParserClient.
	*/
	void ProcessTaggedDataL(const TDesC8& aTag, const TDesC8& aData);

	/**
	Queries the ECom registry for:
		- all registry entries with an interface UID of aFormatCollectionUid
		- all format plugins with an interface UID of aFormatPluginCollectionUid (ie CMMFFormatEncode
		  or CMMFFormatDecode) that have the UID of this controller plugin in the default_data field
		  of their ECom resource file.

	CMMFFormatImplementationInformation objects are created for each entry returned, and appended to
	aFormatArray.

	@param  aFormatCollectionUid
	        See above.
	@param  aFormatPluginCollectionUid
	        See above.
	@param  aFormatArray
	        See above.
	        
	@internalTechnology

	
	*/
	void GetFormatsL(TUid aFormatCollectionUid, TUid aFormatPluginCollectionUid, RMMFFormatImplInfoArray& aFormatArray);

	/**
	Creates CMMFFormatImplementationInformation objects for all CImplementationInformation objects
	in aEcomArray.  Any corrupt objects are ignored.  The objects created are added to aFormatArray.

	@param  aEcomArray
	        See above.
	@param  aFormatArray
	        See above.
	        
	@internalTechnology

	
	*/
	void AddFormatsSwallowCorruptL(RImplInfoPtrArray& aEcomArray, RMMFFormatImplInfoArray& aFormatArray);
	
	/**
	Sets the Uri Scheme found in opaque data
	
	@param  aUriScheme
			Gives the uri scheme supported by the controller
	
	@internalTechnology
	*/
	void SetUriSchemeL(const TDesC8& aUriScheme);
	
	/**
	Sets the Network capability found in opaque data
	
	@param  aNetworkCapable
			Declares the incapability to support uri if matches to 'yes'. 
			If this is the case, iIsNetworkCtrl is set to EFalse
	
	@internalTechnology
	*/
	void SetNetworkCapabilityL(const TDesC8& aNetworkCapable);

private:

	/**
	The play formats supported by this controller.
	*/
	RMMFFormatImplInfoArray iPlayFormats;

	/**
	The record formats supported by this controller.
	*/
	RMMFFormatImplInfoArray iRecordFormats;

	/**
	The interface uid of the resource file definitions of the play formats supported directly by this controller.
	*/
	TUid iPlayFormatCollectionUid;

	/**
	The interface uid of the resource file definitions of the record formats supported directly by this controller.
	*/
	TUid iRecordFormatCollectionUid;
	
	/**
	The heap space required by this controller
	*/
	TUint iHeapSpaceRequired;
	
	/**
	The Uri scheme supported by this plugin
	*/
	CDesC8Array* iUriSchemes;
	
	/**
	The uri priority acquired by this controller
	*/
	TInt iUriPriority;  
	
	/**
	The uri support provided by this controller
	*/
	TBool iIsNetworkCtrl;
	};


/**
@publishedAll

Contains the parameters used to select mmf plugins from the ECOM registry.



*/
class CMMFPluginSelectionParameters : public CBase
	{
public:

/**
Describes the type of preferred supplier match to be performed on the plugins return from
the ECOM registry.
*/
enum TPreferredSupplierMatchType
	{

	/**	No preferred supplier match will be performed.
	*/
	ENoPreferredSupplierMatch,

	/** Plugins from all suppliers will be returned, but those from the preferred supplier will be first in the list.
	*/
	EPreferredSupplierPluginsFirstInList,

	/** Only plugins from the preferred supplier will be returned.
	*/
	EOnlyPreferredSupplierPluginsReturned
	};
/**
Describes the type of media ID match to be performed on the plugins return from
the ECOM registry.
*/
enum TMediaIdMatchType
	{

	/** No media ID match will be performed.
	*/
	ENoMediaIdMatch,

	/** All plugins that support the media ID supplied will be returned, even those that support
	other media IDs.  For example, if an audio plugin is requested, plugins that support
	audio and video will also be returned.
	*/
	EAllowOtherMediaIds,

	/** Only plugins that support the exact media IDs supplied will be returned.  For example, if an
	audio plugin is requested, plugins that only support audio will be returned
	(ie. no audio/video plugins).
	*/
	EAllowOnlySuppliedMediaIds
	};

public:

	/**
	Destructor.  Resets and destroys all member data.

	
	*/
	virtual ~CMMFPluginSelectionParameters();


	/**
	Sets the preferred supplier of the plugin.

	@param  aPreferredSupplier
	        The preferred supplier of the plugin.
	@param  aMatchType
	        The type of match to be made.

	
	*/
	IMPORT_C void SetPreferredSupplierL(const TDesC& aPreferredSupplier, TPreferredSupplierMatchType aMatchType);

	/**
	Sets the media IDs that must be supported by the plugin, for example audio, video etc.

	@param  aMediaIds
	        An array of the media IDs that the selected plugins must support.
	@param  aMatchType
	        The type of match to be made.

	
	*/
	IMPORT_C void SetMediaIdsL(const RArray<TUid>& aMediaIds, TMediaIdMatchType aMatchType);

	/**
	Returns the preferred supplier.  If no preferred supplier has been set, a blank 
	string will be returned.
	
	@return The preferred supplier
	
	*/
	IMPORT_C const TDesC& PreferredSupplier() const;

	/**
	Returns the type of preferred supplier match to perform.

	@return The preferred supplier match type.
	
	*/
	IMPORT_C TPreferredSupplierMatchType PreferredSupplierMatchType() const;

	/**
	Returns the list of media IDs that must be supported by the plugin.

	@return The list of media IDs.

	
	*/
	IMPORT_C const RArray<TUid>& MediaIds() const;

	/**
	Returns the type of preferred supplier match to perform.
	
	@return The preferred supplier match type.

	
	*/
	IMPORT_C TMediaIdMatchType MediaIdMatchType() const;

	/**
	Returns the uid of the interface to be searched for plugin matches.

	@return The interface uid.

	
	*/
	IMPORT_C TUid InterfaceUid() const;

protected:

	/**
	Protected constructor.

	Defaults to setting the TPreferredSupplierMatchType enum to ENoPreferredSupplierMatch and TMediaIdMatchType
	to ENoMediaIdMatch.

	@param  aPluginInterfaceUid
	        The plugin's interface UID.
	*/
	CMMFPluginSelectionParameters(TUid aPluginInterfaceUid);

	/**
	Tests whether the specified media is supported by the plugin.

	@param  aPlugin
	        The media to test.

	@return A boolean indicating if the specified media is supported by the plugin. ETrue if the specified 
	        media is supported by the plugin. EFalse if the specified media is not supported by the plugin.
	*/
	TBool CheckMediaIdSupportL(const CMMFPluginImplementationInformation& aPlugin) const;
private:
	TUid iPluginInterfaceUid;
	HBufC* iPreferredSupplier;
	TPreferredSupplierMatchType iPreferredSupplierMatchType;
	RArray<TUid> iMediaIds;
	TMediaIdMatchType iMediaIdMatchType;
	};

/**
@publishedAll

Defines the format support required.

On construction, the selection parameters are blank, causing all plugins to be returned.



*/
class CMMFFormatSelectionParameters : public CBase
	{
public:
/**
Describes the type of match to be performed.
The match types are mutually exclusive.
*/
enum TMatchDataType
	{

	/** All plugins will be selected. This is the default option.
	*/
	EMatchAny,

	/** The match will be based on a file extension.
	*/
	EMatchFileExtension,

	/** The match will be based on a mime type.
	*/
	EMatchMimeType,

	/** The match will be based on a header data.
	*/
	EMatchHeaderData,
	
	/** 
	@publishedPartner
	@prototype
	
	The match will be based on Uri details.
	*/
	EMatchUri
	};

public:
	
	/**
	Allocates and constructs a new format selection parameter object with blank parameters.

	Calls NewLC().

	@return A new format selection parameter object.
	*/
	IMPORT_C static CMMFFormatSelectionParameters* NewL();

	/**
    Allocates and constructs a new format selection parameter object with blank parameters, placing it on the 
	cleanup stack.

	@return A new format selection parameter object.
	*/
	IMPORT_C static CMMFFormatSelectionParameters* NewLC();

	/**
	Allocates and constructs a new format selection parameter object with the specified parameters.

	@param  aParams
	        The required parameters.
	@return A new format selection parameter object.
	*/
	static CMMFFormatSelectionParameters* NewL(const CMMFFormatSelectionParameters& aParams);

	/**
	Sets this object to match to a file extension.

	aFileName can be a full filename or just an extension.  If there is no dot in the filename
	and it is 5 characters or less in length then it is assumed to be an extension.  If the first
	character of the filename is a dot, it assumed to be an extension.  Otherwise, the filename
	is parsed using TParse to reveal the extension.

	Once the extension has been extracted, it is converted from unicode to utf8 and copied into
	iMatchData.

	@param  aFileName
	        The file name to be matched.  Must include the extension.

	
	*/
	IMPORT_C void SetMatchToFileNameL(const TDesC& aFileName);

	/**
	Sets this object to match to a file extension specified by a URI

	Once the extension has been extracted, it is copied into iMatchData.

   	@param  aUri
	        The URI containing the file name to be matched.  Must include the extension.

	
	*/
	IMPORT_C void SetMatchToUriL(const TDesC& aUri);
	
	/**
	@publishedPartner
	@prototype
	
	Sets this object to match to uri scheme and file extension specified by a URI.
	
	The Uri scheme and extension are saved in iMatchReqData. Further,iMatchData contains uri extension, 
	iMatchUriScheme contains uri scheme.

	@param  aUri
	        The URI containing the scheme and uri extension to be matched. 

	*/
	IMPORT_C void SetMatchToUriSupportL(const TDesC& aUri);
	
	/**
	Sets this object to match to a MIME type.
	
	@param  aMimeType
	        The mime type to match.

	
	*/
	IMPORT_C void SetMatchToMimeTypeL(const TDesC8& aMimeType);

	/**
	Sets this object to match to a pattern in header data.
	
	@param  aHeaderData
	        The header of the file in question.  This header data will be matched
	        against the match patterns provided by the plugins.

	
	*/
	IMPORT_C void SetMatchToHeaderDataL(const TDesC8& aHeaderData);

	/**
	Returns the data used to perform the plugin match.
	
	@return The match data.

	
	*/
	IMPORT_C const TDesC8& MatchData() const;
	
	/**
	@publishedPartner
	@prototype
	
	Returns the uri scheme used to perform the plugin match.
	
	@return The uri scheme.

	*/
	IMPORT_C const TDesC8& MatchUriScheme() const;

	/**
	Returns the type of the data used to perform the plugin match.

	@return The match data type.

	
	*/
	IMPORT_C TMatchDataType MatchDataType() const;
	
	/**
	Destructor.
	*/
	virtual ~CMMFFormatSelectionParameters();
protected:

	/**
	Protected constructor.
	*/
	CMMFFormatSelectionParameters();
	void ConstructL(const CMMFFormatSelectionParameters& aParams);

private:
	CMatchData* iMatchReqData;
	TMatchDataType iMatchDataType;
	};



/**
@publishedAll


Contains the parameters used to select controller plugins from the ECOM registry.


*/
class CMMFControllerPluginSelectionParameters : public CMMFPluginSelectionParameters
	{
public:

	/**
	Constructs a new controller selection parameters object.

	@return The new object created.

	
	*/
	IMPORT_C static CMMFControllerPluginSelectionParameters* NewL();

	/**
	Construct a new controller selection parameters object.
	
	@return The new object created.  Note that the new object will be left on the cleanup stack.

	
	*/
	IMPORT_C static CMMFControllerPluginSelectionParameters* NewLC();

	/**
	Sets the play format support required.

	Note:
	The play formats supported by the controller plugins will only be retrieved if
	this method is called.  To get all the play formats supported by the system, call this
	with a 'blank' CMMFFormatSelectionParameters object.

	@param  aRequiredSupport
	        The play format support required.

	
	*/
	IMPORT_C void SetRequiredPlayFormatSupportL(const CMMFFormatSelectionParameters& aRequiredSupport);

	/**
	Sets the record format support required.

	Note:
	The record formats supported by the controller plugins will only be retrieved if
	this method is called.  To get all the record formats supported by the system, call this
	with a 'blank' CMMFFormatSelectionParameters object.

	@param  aRequiredSupport
	        The record format support required.

	@return The new object created.

	
	*/
	IMPORT_C void SetRequiredRecordFormatSupportL(const CMMFFormatSelectionParameters& aRequiredSupport);

	/**
	Retrieves all controller plugins that support the requirements of the caller.

	@param  aImplementations	
	        After this method returns, this array will contain all the
	        controller plugins that support the caller's requirements.
	        Note: The array will be emptied by this method.

	
	*/
	IMPORT_C virtual void ListImplementationsL(RMMFControllerImplInfoArray& aImplementations) const;

	/** 
	Destructor
	*/
	virtual ~CMMFControllerPluginSelectionParameters();
protected:
	CMMFControllerPluginSelectionParameters();
	void MatchImplementationToSelectParamsL(RMMFControllerImplInfoArray& aImplementations, const CMMFControllerImplementationInformation& aPlugin, TInt& aArrayPos) const;
	TInt CheckPreferredSupplierL(RMMFControllerImplInfoArray& aImplementations, const CMMFControllerImplementationInformation& aPlugin) const;
	TBool CheckFormatSupportL(CMMFFormatSelectionParameters* aSelectParams, const RMMFFormatImplInfoArray& aFormats) const;
	/**
	Checks the given Controller for uri support. Uri support may be there 
	if either requiredscheme or extension matches with that given controller
	
	@param  aSelectParams 
			Describes the selection parameter which a controller needs to 
			support in order to be selected
			
	@param	aPlugin
			The controller plugin which is checked for uri support 
			
	@param	aFormats
			The play or record formats looked for extension match
	*/
	TBool CheckUriSupport(CMMFFormatSelectionParameters* aSelectParams, CMMFControllerImplementationInformation* aPlugin, const RMMFFormatImplInfoArray& aFormats) const;

protected:
	/**
	The required play format support
	*/
	CMMFFormatSelectionParameters* iRequiredPlayFormatSupport;
	
	/**
	The required record format support
	*/
	CMMFFormatSelectionParameters* iRequiredRecordFormatSupport;
	};

class CMmfRecognizerUtil; // declared here.
/**
@internalAll

MMF utility class used by MMF recognizer
Maintains an array of CMMFControllerImplementationInformation objects
so that data headers can be speedily matched against.
Updates the array when notified by ECOM of a change to the global
interface implementation registration data.
*/
NONSHARABLE_CLASS( CMmfRecognizerUtil ): public CBase
	{
public:
	enum TMatchLevel
		{
		EMatchNone, //no match
		EMatchData, //data match only
		EMatchName  //suffix and data match
		};
public:
	IMPORT_C static void GetMimeTypesL(CDesC8Array* aMimeTypes);

	IMPORT_C static CMmfRecognizerUtil* NewL();

	~CMmfRecognizerUtil();
	IMPORT_C TMatchLevel GetMimeTypeL(const TDesC& aFileName, const TDesC8& aImageData, TDes8& aMimeType);

private:
	CMmfRecognizerUtil();
	void ConstructL();

private:
	class CBody;
	CBody* iBody;
	};


/**
@publishedAll


Abstract class used to contain the parameters used to select format plugins from the ECOM registry.

Note: 
The classes CMMFFormatEncodePluginSelectionParamters and CMMFFormatDecodePluginSelectionParameters
should be used to list and select format plugin implementations.


*/
class CMMFFormatPluginSelectionParameters : public CMMFPluginSelectionParameters
	{
public:

	/**
	Retrieves all format plugins that support the requirements of the caller.

	@param  aImplementations
	        After this function returns, this array will contain all the
	        format plugins that support the caller's requirements.
	        Note: The array will be emptied by this method.

	
	*/
	IMPORT_C void ListImplementationsL(RMMFFormatImplInfoArray& aImplementations) const;

	/**
	Sets the format support required.

	@param  aRequiredSupport
	        The format support required.

	
	*/
	IMPORT_C void SetRequiredFormatSupportL(const CMMFFormatSelectionParameters& aRequiredSupport);

	/**
	Destructor.
	*/
	virtual ~CMMFFormatPluginSelectionParameters();
protected:
	/**
	Protected constructor.
	*/
	CMMFFormatPluginSelectionParameters(TUid aInterfaceUid);

	void MatchImplementationToSelectParamsL(RMMFFormatImplInfoArray& aImplementations, const CMMFFormatImplementationInformation& aPlugin, TInt& aArrayPos) const;
	TInt CheckPreferredSupplierL(RMMFFormatImplInfoArray& aImplementations, const CMMFFormatImplementationInformation& aPlugin) const;
	TBool CheckFormatSupportL(const CMMFFormatImplementationInformation& aPlugin) const;
protected:
	/**
	The format support required
	*/
	CMMFFormatSelectionParameters* iRequiredFormatSupport;
	};

/**
@publishedAll


Class used to list and select plugins implementing the CMMFFormatEncode interface.


*/
class CMMFFormatEncodePluginSelectionParameters : public CMMFFormatPluginSelectionParameters
	{
public:

	/**
	Construct a new format encode selection parameters object.
	
	@return The new object created.

	
	*/
	IMPORT_C static CMMFFormatEncodePluginSelectionParameters* NewL();

	/**
	Constructs a new format encode selection parameters object.

	@return The new object created.  Note that the new object will be left on the cleanup stack.

	
	*/
	IMPORT_C static CMMFFormatEncodePluginSelectionParameters* NewLC();
protected:
	/**
	Protected constructor.
	*/
	CMMFFormatEncodePluginSelectionParameters();
	};


/**
@publishedAll


Class used to list and select plugins implementing the CMMFFormatDecode interface.


*/
class CMMFFormatDecodePluginSelectionParameters : public CMMFFormatPluginSelectionParameters
	{
public:

	/**
	Constructs a new format decode selection parameters object.

	@return The new object created.
	
	
	*/
	IMPORT_C static CMMFFormatDecodePluginSelectionParameters* NewL();

	/**
	Constructs a new format decode selection parameters object.

	@return The new object created. Note that the new object will be left on the cleanup stack.

	
	*/
	IMPORT_C static CMMFFormatDecodePluginSelectionParameters* NewLC();
protected:
	/**
	Protected constructor.
	*/
	CMMFFormatDecodePluginSelectionParameters();
	};



/** 
@publishedAll


Template class CleanupResetAndDestroy to clean up the array
of implementation information from the cleanup stack.
*/

template <class T>
class CleanupResetAndDestroy
	{
public:
	/**
	Puts an item on the cleanup stack.

	@param  aRef 
	        The implementation information to be put on the cleanup stack.
	*/
	inline static void PushL(T& aRef);
private:
	static void ResetAndDestroy(TAny *aPtr);
	};
template <class T>
inline void CleanupResetAndDestroyPushL(T& aRef);
template <class T>
inline void CleanupResetAndDestroy<T>::PushL(T& aRef)
	{CleanupStack::PushL(TCleanupItem(&ResetAndDestroy,&aRef));}
template <class T>
void CleanupResetAndDestroy<T>::ResetAndDestroy(TAny *aPtr)
	{(STATIC_CAST(T*,aPtr))->ResetAndDestroy();}
template <class T>
inline void CleanupResetAndDestroyPushL(T& aRef)
	{CleanupResetAndDestroy<T>::PushL(aRef);}


#endif
