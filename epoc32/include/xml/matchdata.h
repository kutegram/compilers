// matchdata.h
//
// Copyright (c) Symbian Software Ltd 2003 - 2007. All rights reserved.
//

/** 
@file 

@SYMPurpose Detailed parser information for resolution criteria in XML framework

@publishedAll

*/


#ifndef MATCHDATA_H
#define MATCHDATA_H

#include <e32base.h>
#include <s32strm.h>
#include <s32mem.h>
#include <ecom/implementationinformation.h>

namespace Xml
{

/**
The plugin variant string of the default Symbian-provided XML parser plugins.
@publishedAll

*/
_LIT8(KXmlSymbianPluginVariant, "Symbian");		

/**
CMatchData class provides detailed parser information for XML framework.
Client application should use this class to precisely specify the plugin, 
which should be used as a parsing engine in XML framework.

@publishedAll

*/

NONSHARABLE_CLASS(CMatchData) : public CBase
{

public:
	CMatchData();
	~CMatchData();
	
	IMPORT_C static CMatchData* NewL();
	IMPORT_C static CMatchData* NewL(const TDesC8& aPackage);
	IMPORT_C static CMatchData* NewLC();
	IMPORT_C static CMatchData* NewLC(const TDesC8& aPackage);

	IMPORT_C void SetMimeTypeL(const TDesC8& aData);
	IMPORT_C const TPtrC8 MimeType() const;

	IMPORT_C void SetVariantL(const TDesC8& aVariant);
	IMPORT_C const TPtrC8 Variant() const;
	
	IMPORT_C void SetLeaveOnMany(TBool aSetting);
	IMPORT_C void SetRomOnly(TBool aSetting);
	IMPORT_C void SetCaseSensitivity(TBool aSetting);
	
	IMPORT_C TUid ResolveL(RImplInfoArray& aImplList) const;

public:
	CMatchData& operator=(const CMatchData & aMatchData);
	TBool operator==(const CMatchData & aMatchData) const;
	HBufC8* PackToBufferL() const;

private:
	void ConstructL(const TDesC8& aPackage);
	
	TBool VariantMatch(const TDesC8& aOpaqueField) const;
	TBool MimeTypeMatch(const TDesC8& aDataField) const;
	TBool MatchField(const TDesC8& aField, const TDesC8& aMatchString, const TDesC8& aSeparator) const;
	
	TBool CaseSensitivity() const;
	TBool LeaveOnMany() const;
	TBool RomOnly() const;
	
	void ExternalizeL(RWriteStream& aStream) const;
	void InternalizeL(RReadStream& aStream);		

	TUid SelectSingleParserL(RImplInfoPtrArray& aImplList) const;
	TBool IsInvalidVariant() const;
	
	static TInt SortOrder(const CImplementationInformation &aImpInfo1, 
							const CImplementationInformation &aImpInfo2);
private:
	/** 
	Mime type requested by client
	Is matched against one of entries of data_type field in resoure information file
	*/
	HBufC8* iMimeType; 
	
	/**
	Variant requested by client
	Is matched against first entry in opaque_data field of resource information file
	*/
	HBufC8* iVariant;
	
	/**
	Additional information for resolution constrains. Bitmap.
	*/
	TUint32 iAddInfo;
};

}
// MATCHDATA_H
#endif


