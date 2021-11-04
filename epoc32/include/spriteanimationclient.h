// SpriteAnimationClient.h
//
// Copyright (c) 2004 Symbian Software Ltd.  All rights reserved.
//

#ifndef __SPRITEANIMATIONCLIENT_H__
#define __SPRITEANIMATIONCLIENT_H__

#include <w32std.h>

class TAnimationConfig;

/** @internalComponent */
NONSHARABLE_CLASS(RSpriteAnimationClient) : public RAnim
	{
public:
	RSpriteAnimationClient(RAnimDll& aAnimDll);
	~RSpriteAnimationClient();
	void ConstructL(const RWsSprite& aDevice, const TDesC8& aDataType);
	void ConstructL(const RWsSprite& aDevice, const TDesC8& aDataType, TInt aHostHandle);
	void Start(const TAnimationConfig& aConfig);
	void Stop();
	void Pause();
	void Resume();
	void Hold();
	void Unhold();
	void Freeze();
	void Unfreeze();
	void SendEventL(TInt aEvent, const TAny* aData, TInt aDataLength);
	TSize Size();
protected:
	void SetMinBufferSizeL(TInt aSize);
private:
	TPtr8 iBuf;
	};
	
// __SPRITEANIMATIONCLIENT_H__
#endif
