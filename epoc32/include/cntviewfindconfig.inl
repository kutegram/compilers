// CNTVIEWFINDCONFIG.INL
//
// Copyright (c) 2002 Symbian Ltd.  All rights reserved.
//


// -----------------------CContactViewFindConfigInterface --------------------------------
inline CContactViewFindConfigInterface* CContactViewFindConfigInterface::NewL(TUid aImplementationUid)
/** Allocates and constructs an instance of the plug-in interface.

@param aImplementationUid The UID of the find configuration implementation 
to instantiate.
@return Pointer to the newly created implementation object. */
	{
		TAny* ptr = REComSession::CreateImplementationL(aImplementationUid,
					_FOFF(CContactViewFindConfigInterface,iDtor_ID_Key));
		return reinterpret_cast<CContactViewFindConfigInterface*>(ptr);
	}
inline CContactViewFindConfigInterface::~CContactViewFindConfigInterface()
/** Virtual destructor. */
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}

