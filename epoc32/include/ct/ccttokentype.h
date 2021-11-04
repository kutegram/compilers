// Copyright (c) 2001-2004 Symbian Software Ltd.  All rights reserved.
/**
 * @file 
 * CTTokenType Codes
 *
 * @internalTechnology
 */
 
#ifndef __CCTTOKENTYPE_H__
#define __CCTTOKENTYPE_H__

#include <ct/mcttokentype.h>

/**
 * Abstract base class for a handler object to be called when a CCTTokenType is
 * deleted.  The handler is called simply by being deleted.  It is called from
 * CCTTokenType's destructor.
 *
 * This allows for ecom-loaded tokens to be destroyed properly without
 * forcing clients of ctframework.dll to link against ecom.
 *
 * @internalTechnology
 */
class CCTTokenTypeDeleteHandler : public CBase
	{
 public:
	IMPORT_C virtual ~CCTTokenTypeDeleteHandler();
	};

/**
 * A token type.
 *
 * This abstract class is instantiated using the ECom plug-in architecture 
 * for a particular token type. This adds a delayed destruction behaviour 
 * to MCTTokenType, which defines the majority of the interface.
 *
 * This class uses protected inheritance from CBase so that clients cannot
 * inadvertantly call delete on instances of it - they should call the Release()
 * method instead.
 * 
 * @publishedPartner
 * 
 * 
 */
class CCTTokenType : protected CBase, public MCTTokenType
	{
public:
	/** Gets a file server session */
	inline RFs& Fs();

protected:
	/** Increments the reference count. 
	* 
	* Must be called for every token created from this interface */
	IMPORT_C void IncReferenceCount();

	// From this point onwards, everything in this class is essentialy
	// internal and of no interest to dereived classes.
 public:
	
	/** Creates a CCTTokenType given its CCTTokenTypeInfo.
	*	
	* Static constructor function that uses the ECom 
	* plug-in architecture to load the actual implementation.
	*
	* @param aInfo	Information about the token type.
	* @param aFs	An open file server session.
	* @return		The new token type object. */
	IMPORT_C static CCTTokenType* NewL(const CCTTokenTypeInfo& aInfo, RFs aFs);

	/** Creates a CCTTokenType given the UID of the token type.	
	*
	* Static constructor function that uses the ECom 
	* plug-in architecture to load the actual implementation.
	*
	* @param aUID	The UID of the token type.
	* @param aFs	An open file server session.
	* @return		The new token type object. */
	IMPORT_C static CCTTokenType* NewL(TUid aUID, RFs aFs);
	
	/** Releases the token type object.
	*
	* To be called when you have finished with the object.
	*
	* The API does not allow the destructor to be directly called as this object 
	* could remain in existence for longer to hold onto the ECom handle on the DLL; 
	* for instance it may not be deleted until all tokens and interfaces have also 
	* been released. */
	IMPORT_C virtual void Release();

	/** Gets the UID of the token type.	
	*
	* @return	The UID of the token type. */
	IMPORT_C virtual TUid Type() const;
	
	/** Gets the label of the token type.	
	*
	* @return	The label of the token type. */
	IMPORT_C virtual const TDesC& Label() const;

 protected:
	IMPORT_C CCTTokenType();

	/** Destructor */
	IMPORT_C virtual ~CCTTokenType();

	/**
	 * For 2 phase construction. 
	 *
	 * This function must be called by derived NewL() functions if and only if the 
	 * class is being constructed without using ECom.
	 */
	IMPORT_C void ConstructL(TUid aUID, const TDesC& aLabel, RFs aFs);

 private:
	static CCTTokenType* CreateTokenTypeLC(TUid aUid);	

 private:
	/// Delete handler, called on destruction
	CCTTokenTypeDeleteHandler* iDeleteHandler;
	
	/// A refedrence count
	TInt iCount;

	/// The UID of the token type.
	TUid iUID;

	/// The label of the token type
	HBufC* iLabel;

	RFs iFs;
	};

inline RFs& CCTTokenType::Fs()
	/** Gets the file server session.
	*
	* @return	The file server session. */
	{
	return iFs;
	}

// These are defined here as they need to ahve both MCTTokenType and 
// CCTTokenType defined before they can be.
inline MCTTokenType* MCTTokenType::NewL(const CCTTokenTypeInfo& aInfo, RFs aFs)
	/** Creates a MCTTokenType object given it's CCTTokenTypeInfo.
	*
	* @param aInfo	Information about the token type.
	* @param aFs	An open file server session.
	* @return		A new token type object. */
	{
	return CCTTokenType::NewL(aInfo, aFs);
	}

inline MCTTokenType* MCTTokenType::NewL(TUid aUID, RFs aFs)
	/** Creates a MCTTokenType object given the UID of the token type. 
	*
	* @param aUID	The UID of the token type.
	* @param aFs	An open file server session.
	* @return		A new token type object. */
	{
	return CCTTokenType::NewL(aUID, aFs);
	}

//__CCTTOKENTYPE_H__
#endif
