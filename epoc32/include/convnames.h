// CONVNAMES.H
//
// Copyright (c) 2000 Symbian Ltd.  All rights reserved.
//

#if !defined(__CONVNAMES_H__)
#define __CONVNAMES_H__

#if !defined(__E32STD_H__)
#include <E32STD.H>
#endif

#if !defined(__E32BASE_H__)
#include <E32BASE.H>
#endif

#if !defined(__BAMDESCA_H__)
#include <BAMDESCA.H>
#endif 

#if !defined(__CHARCONV_H__)
#include <CHARCONV.H>
#endif

class RFs;
class CBaNamedPlugins;

 
class CCnvCharacterSetNames : public CBase, public MDesCArray
/** 
A localised list of the names of non-Unicode character set encodings supported 
on the phone.

For each character conversion plug-in DLL, there are one or more resource 
files which contain the name of the encoding translated into a different language.

This class populates a list of the names of all encodings supported on the 
phone by reading the appropriate resource file for each one. The list is sorted 
according to the collation rules for the device's current locale.

The virtual functions MdcaCount() (returns the number of items in the list) 
and MdcaPoint() (returns a TPtrC for the item at the given index) are implemented 
privately in this class. Users of this class can call them through the MDesCArray 
interface. 
@publishedAll

*/
	{
public:
	IMPORT_C static CCnvCharacterSetNames* NewL(RFs& aFileServerSession, const TArray<CCnvCharacterSetConverter::SCharacterSet>& aArrayOfCharacterSetsAvailable);
	IMPORT_C static CCnvCharacterSetNames* NewLC(RFs& aFileServerSession, const TArray<CCnvCharacterSetConverter::SCharacterSet>& aArrayOfCharacterSetsAvailable);
	IMPORT_C virtual ~CCnvCharacterSetNames();
	IMPORT_C TInt IndexOfIdentifier(TUint aIdentifier) const;
	IMPORT_C TUint IdentifierAtIndex(TInt aIndex) const;

private:
	CCnvCharacterSetNames();
	void ConstructL(RFs& aFileServerSession, const TArray<CCnvCharacterSetConverter::SCharacterSet>& aArrayOfCharacterSetsAvailable);
	// from MDesCArray
	virtual TInt MdcaCount() const;
	virtual TPtrC MdcaPoint(TInt aIndex) const;
	static void DestroyResourceFileArray(TAny* aArrayOfCharconvResourceFiles);

private:
	CBaNamedPlugins* iNamedPlugins;
	};

#endif

