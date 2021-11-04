// Copyright (c) Symbian Ltd 2003-2004

#include <e32base.h>

#include "ct.h"


/**
	void MCTWritableCertStore::Add(.., TBool aDeletable, ..)
	

	This is a default (dummy) implementation of the new Add(.., TBool aDeletable, ..) method
	to ensure backward compatibility with old implementations.

 	The MCTWritableCertStore is an abstract parent class for other implementation specific 
 	writable cert store classes such as  CFileCertStore, CFSCertStoreClient, CCheckedCertStore,  
 	and other partner defined classes.
 	
 	Every such child class derived from MCTWritableCertStore, provided it is written properly,
 	MUST have its own implementation for the  Add(.., TBool aDeletable, ..) method.
 	
 	Therefore, this dummy implementation in the parent class (MCTWritableCertStore) should NEVER
 	be engaged, since the child's class implementation is supposed to work. 
 	
 	Once, the method is called here, in the parent class, this simply means that child class
 	didn't manage to provide its implementation, which could in turn mean that either the child
 	class is older version, or the child class is poorly written.
 	
 	Thus, the current Add() returns with TRequestStatus& aStatus set to error 
 	value KErrNotSupported.
 */ 

inline void MCTWritableCertStore::Add( const TDesC&,
							TCertificateFormat,
							TCertificateOwnerType, 
					 		const TKeyIdentifier*,
					 		const TKeyIdentifier*,
					 		const TDesC8&, 
					 		const TBool,
					 		TRequestStatus&	aStatus	)
	{
		TRequestStatus* status = &aStatus;	
		User::RequestComplete( status, KErrNotSupported );
	}

