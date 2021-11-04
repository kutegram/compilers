// Uri8.h
//
// Copyright (c) Symbian Software Ltd 2001-2007. All rights reserved.
//

/**
	@file Uri8.h
	Comments :	This file contains the API definition for the classes TUriC8 and 
				CUri8. These classes provide non-modifying (TUriC8) and modifying
				(CUri8) functionality for the components of a Uri as described in 
				RFC2396.
	@publishedAll
	
 */

#ifndef __URI8_H__
#define __URI8_H__

// System includes
//
#include <e32base.h>
#include <f32fsys.h>
#include <uricommon.h>


/**
Dependencies : TUriComponent.
Comments : Provides non-modifying functionality on the components of a uri object as
defined in RFC2396. There are 5 components; scheme, authority, path, query and fragment.

The	object holds descriptor pointers to the parsed uri components and a descriptor pointer 
to the uri. It is non-owning. It uses 8-bit descriptors.

The functionality provided by this API allows the uri components to be extracted from the 
parsed uri, checked for their presence in the uri and be compared with those in another 
TUriC8 object.
@publishedAll


*/
class TUriC8
	{
public:	// Methods

	IMPORT_C HBufC* GetFileNameL() const;
	IMPORT_C HBufC* GetFileNameL(TUriFileName aType) const;

	IMPORT_C const TDesC8& Extract(TUriComponent aComponent) const;
	IMPORT_C void UriWithoutFragment(TPtrC8& aUriNoFrag) const;

	IMPORT_C TBool IsPresent(TUriComponent aComponent) const;
	IMPORT_C TBool IsSchemeValid() const;
	IMPORT_C TInt Compare(const TUriC8& aUri, TUriComponent aComponent) const;

	IMPORT_C const TDesC8& UriDes() const;

	IMPORT_C TInt Validate() const;
	IMPORT_C TInt Equivalent(const TUriC8& aUri) const;
	IMPORT_C HBufC* DisplayFormL(TUriComponent aComponent = EUriComplete) const;

protected:	// Methods

	IMPORT_C TUriC8();
	void Reset();

protected:	// Attributes

	/** The array of descriptor pointers to the uri components.
	*/
	TPtrC8		iComponent[EUriMaxComponents];

	/** The descriptor pointer to the uri.
	*/
	TPtrC8		iUriDes;

/**
	A friend class.
	@see		CUri8 
	
 */
	friend class CUri8;

/**
	A friend class used for testing.
	@see		TUriC8StateAccessor
	
	@internalComponent
 */
	friend class TUriC8StateAccessor;

	};

/**
Dependencies : TUriC8
Comments : Provides functionality to parse a descriptor into the components of a uri as 
defined in RFC2396. There are 5 components; scheme, authority, path, query and fragment.

It uses 8-bit descriptors.

Format of a uri is; scheme://authority path?query\#fragment

@warning The descriptor that is parsed by an object of this class will be referenced 
by that object. If the original descriptor is no longer in scope there will be undefined 
behaviour.
@publishedAll


*/
class TUriParser8 : public TUriC8
	{
public:	// Methods

	IMPORT_C TUriParser8();

	IMPORT_C TInt Parse(const TDesC8& aUri);

private:	// Methods	
	void RetrieveScheme(const TPtrC8& aUri, TPtrC8& aScheme);
	};

class CUri8 : public CBase
/**
Dependencies : CBase, TUriC8.
Comments : Provides modifying functionality on the components of a uri object, as
defined in RFC2396. There are 5 components; scheme. authority, path, query and fragment.

The	object holds parsed uri information. It is owning. It uses 8-bit descriptors.

The functionality provided by this API allows the uri components to be set or removed 
from this parsed uri. Also, it provides a reference to TUriC8 object so that the non-modifying 
functionality can be used.
@publishedAll


*/
	{
public: // Methods

	IMPORT_C static CUri8* CreateFileUriL(const TDesC& aFullFileName, TUint aFlags = 0); 
	IMPORT_C static CUri8* CreatePrivateFileUriL(const TDesC& aRelativeFileName, TDriveNumber aDrive, TInt aFlags = 0);
	
	IMPORT_C static CUri8* NewL(const TUriC8& aUri);
	IMPORT_C static CUri8* NewLC(const TUriC8& aUri);
	IMPORT_C static CUri8* NewL();
	IMPORT_C static CUri8* NewLC();

	IMPORT_C static CUri8* ResolveL(const TUriC8& aBaseUri, const TUriC8& aRefUri);

	IMPORT_C ~CUri8();

	IMPORT_C const TUriC8& Uri() const;
	IMPORT_C void SetComponentL(const TDesC8& aData, TUriComponent aComponent);
	IMPORT_C void RemoveComponentL(TUriComponent aComponent);

private:	// Methods

	CUri8(const TUriC8& aNewUri);
	void ConstructL();
	void FormUriL();
	void InitializeFileUriComponentsL(const TDesC& aFileName, TDriveNumber aDrive, TUint aFlags);

private:	// Attributes

	/** The descriptor buffer that contains the uri.
	 */
	HBufC8*	iUriBuf;

	/** The parsed uri object.
	 */
	TUriC8	iUri;

/**
	A friend class used for testing.
	@see		TUri8StateAccessor
	
	@internalComponent
 */
	friend class TUri8StateAccessor;

	};

// __URI8_H__
#endif
