// CharacterSetConverter.inl
//
// Copyright (C) 2004 Symbian Ltd. All rights reserved.
//

#include "CharacterSetConverter.h"

/**
Creates a Charconv Plug-in interface implementation.
@param		aInterfaceImplUid The UID for the required Charconv Plug-in interface implementation.
*/
CCharacterSetConverterPluginInterface* CCharacterSetConverterPluginInterface::NewL(TUid aInterfaceImplUid)
	{
	return reinterpret_cast <CCharacterSetConverterPluginInterface*> (
		REComSession::CreateImplementationL(
			aInterfaceImplUid,
			_FOFF(CCharacterSetConverterPluginInterface, iDtor_ID_Key))); 
	}
/**
Destroys the Charconv Plug-in interface implementation specified by iDtor_ID_Key
*/
CCharacterSetConverterPluginInterface::~CCharacterSetConverterPluginInterface()
	{
	REComSession::DestroyedImplementation(iDtor_ID_Key);
	}
