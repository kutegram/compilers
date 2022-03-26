// Copyright (c) Symbian Software Ltd 2004. All rights reserved.

/** @file
@publishedAll

*/

#ifndef REMCONABSVOLCONTROLLER_H
#define REMCONABSVOLCONTROLLER_H

#include <e32base.h>
#include <remcon/remconinterfacebase.h>
#include <remcon/remconinterfaceif.h>

class MRemConAbsVolControllerObserver;
class CRemConInterfaceSelector;

/**
Client-instantiable type supporting sending AbsVol API responses.
*/
NONSHARABLE_CLASS(CRemConAbsVolController) : public CRemConInterfaceBase, 
								             public MRemConInterfaceIf
	{
public:
	/**
	Factory function.
	@param aInterfaceSelector The interface selector. The client must have 
	created one of these first.
	@param aObserver The observer of this interface.
	@return A new CRemConAbsVolController, owned by the interface selector.
	*/
	IMPORT_C static CRemConAbsVolController* NewL(CRemConInterfaceSelector& aInterfaceSelector, 
		MRemConAbsVolControllerObserver& aObserver);
	
	/** Destructor. */
	IMPORT_C ~CRemConAbsVolController();

public:
	/**
	Sends a 'get absolute volume' command. The absolute volume will be 
	returned in response(s) via the observer interface.
	Only one command per controller session can be outstanding at any one time.
	@param aStatus Used by RemCon to indicate completion of the send request. 
	@param aNumRemotes The number of remotes to which the command was sent.
	*/
	IMPORT_C void GetAbsoluteVolume(TRequestStatus& aStatus, TUint& aNumRemotes);

	/**
	Sends a 'set absolute volume' command. The volume is set to aAbsVol, on a 
	range of zero to aMaxVol. Any responses will be returned via the observer 
	interface.
	Only one command per controller session can be outstanding at any one time.
	@param aStatus Used by RemCon to indicate completion of the send request.
	@param aAbsVol The relative volume.
	@param aMaxVol The maximum against which aAbsVol is relative.
	@param aNumRemotes The number of remotes to which the command was sent.
	*/
	IMPORT_C void SetAbsoluteVolume(TRequestStatus& aStatus, TUint aAbsVol, TUint aMaxVol, TUint& aNumRemotes);

private:
	/** 
	Constructor.
	@param aInterfaceSelector The interface selector.
	@param aObserver The observer of this interface.
	*/
	CRemConAbsVolController(CRemConInterfaceSelector& aInterfaceSelector, 
		MRemConAbsVolControllerObserver& aObserver);

private: // from CRemConInterfaceBase
	TAny* GetInterfaceIf(TUid aUid);

private: // from MRemConInterfaceIf
	void MrcibNewMessage(TUint aOperationId, const TDesC8& aData);

private: // unowned
	MRemConAbsVolControllerObserver& iObserver;

private: // owned
	static const TUint KMaxOperationDataSize = 0x20;
	TBuf8<KMaxOperationDataSize> iOutData;
	};

// REMCONABSVOLCONTROLLER_H
#endif
