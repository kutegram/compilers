// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedPartner

*/

#ifndef REMCONINTERFACEBASE_H
#define REMCONINTERFACEBASE_H

#include <e32base.h>
#include <remcon/clienttype.h>

class CRemConInterfaceSelector;

/**
Base class for outer layer APIs. 
*/
class CRemConInterfaceBase : public CBase
	{
public: 
	/** Destructor */
	IMPORT_C ~CRemConInterfaceBase();

public: // called by the ultimate client
	/** 
	Cancels the currently outstanding asynchronous send request. 
	@return KErrNone.
	*/
	IMPORT_C TInt Cancel();

public: // called by the interface selector
	/**
	Called by the interface selector to get a pointer to an object which 
	implements the interface API with UID aUid. This is a mechanism for 
	allowing future change to the interface API without breaking BC in 
	existing (non-updated) interfaces.
	*/
	virtual TAny* GetInterfaceIf(TUid aUid) = 0;

	/** 
	Accessor for the interface's UID. 
	@return The interface's UID.
	*/
	TUid InterfaceUid() const;

	/** 
	Accessor for the maximum length of operation-specific data in this 
	interface. 
	@return The size in bytes of a buffer needed to hold the largest single 
	payload of operation-associated data in this interface.
	*/
	TUint MaxLength() const;

	/**
	Accessor for the type of the interface- either controller or target.
	@return The interface type.
	*/
	TRemConClientType Type() const;

protected:
	/** 
	Constructor.
	@param aInterfaceUid The UID of the interface.
	@param aMaxLength The maximum length of any operation-specific data in the 
	interface being registered.
	@param aInterfaceSelector The interface selector.
	*/
	IMPORT_C CRemConInterfaceBase(TUid aInterfaceUid, 
		TUint aMaxLength, 
		CRemConInterfaceSelector& aInterfaceSelector,
		TRemConClientType aType);

	/** Must be called by concrete types at construction time. Registers the 
	interface with the interface selector. */
	IMPORT_C void BaseConstructL();

	/** 
	Accessor for the interface selector. 
	@return The interface selector.
	*/
	IMPORT_C CRemConInterfaceSelector& InterfaceSelector();

private: // owned
	/** The UID of the concrete (derived) interface. */
	TUid iInterfaceUid; 

	/** Max length of operation-specific data in this interface. */
	TUint iMaxLength; 

	/** The type of the interface- controller or target. */
	const TRemConClientType iType;

	/** 
	Pad for BC-friendly future change.
	*/
	TAny* iPad;

private: // unowned
	CRemConInterfaceSelector& iInterfaceSelector;
	};

// REMCONINTERFACEBASE_H
#endif
