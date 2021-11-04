// cmsvtechnologytypedefaultmtmsettings.h
//
// Copyright (c) 2005 Symbian Software Ltd.  All rights reserved.
//

#ifndef __CMSVTECHNOLOGYTYPEDEFAULTMTMSETTINGS_H__
#define __CMSVTECHNOLOGYTYPEDEFAULTMTMSETTINGS_H__

#include <e32base.h>
#include <e32cmn.h>

class RFs;
class CRepository;


/**
Stores default MTM settings for a technology type to the Central Repository.

@publishedAll

*/
class CMsvTechnologyTypeDefaultMtmSettings : public CBase
	{
private:
	struct TMsvTechnologyTypeDefaultMtmInfo
		{
		TUid iTechnologyTypeUid;
		TUid iMtmUid;
		};

public:
	IMPORT_C static CMsvTechnologyTypeDefaultMtmSettings* NewL( RFs& aFs );
	IMPORT_C ~CMsvTechnologyTypeDefaultMtmSettings( );
	
	IMPORT_C TInt DefaultMtm( TUid aTechnologyTypeUid, TUid& aMtmUid ) const;
	IMPORT_C void SetDefaultMtmL( TUid aTechnologyTypeUid, TUid aMtmUid );
	IMPORT_C TInt RemoveDefaultMtm( TUid aTechnologyTypeUid );
	
	// Stores and Restores data in the central repository
	IMPORT_C void LoadSettingsL( );
	IMPORT_C void SaveSettingsL( );

private:
	CMsvTechnologyTypeDefaultMtmSettings( RFs& aFs );
	void ConstructL();
	void CheckIfMtmIsPartOfTechnologyTypeGroupL( const TUid aTechnologyTypeUid,
												 const TUid aMtmUid, const TUid aMtmTypeUid ) const;
	TInt FindDefaultMtm( const TUid aTechnologyTypeUid, 
						 TMsvTechnologyTypeDefaultMtmInfo& aTechnologyTypeDefaultMtmInfo ) const;

private:
	CRepository* iRepository;
	RArray<TMsvTechnologyTypeDefaultMtmInfo> iTechnologyTypeDefaultMtmArray;
	RArray<TUid> iRemovedTechnologyTypes;
	RFs& iFs;
	};
//__CMSVTECHNOLOGYTYPEDEFAULTMTMSETTINGS_H__
#endif
