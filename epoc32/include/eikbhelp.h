// EIKBHELP.H
//
// Copyright (c) 2000-2006 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKBHELP_H__
#define __EIKBHELP_H__

#include <coemain.h>

const TUid KEikBubbleHelpUid={0x10008E48};

class CCoeControl;

/**
@publishedPartner
@deprecated
*/
class MEikTriggeredHelp	
	{
// The MEikTriggeredHelp class defines an interface for UI classes 
// to implement triggered, transient help message display.
public:
	virtual void TriggerHelp(const TDesC& aDes,const TRect& aRect,TInt aHandle)=0;
	virtual void CancelHelp()=0;
	virtual void CancelHelpTrigger()=0;
	virtual TBool IsDisplayingHelp(TInt aHandle)=0;
	virtual void Release()=0;
protected:
	IMPORT_C virtual void MEikTriggeredHelp_Reserved_1();
	IMPORT_C virtual void MEikTriggeredHelp_Reserved_2();
	};


/** Provides the static functions that control bubble help.

Bubble help is a feature that enables short help messages to be displayed 
for controls in transient windows which pop up close to the control bodies. 

@publishedAll 
*/
class EikBubbleHelp
	{
public:
	IMPORT_C static void Trigger(const TDesC& aDes,const TRect& aRect,TInt aHandle=-1);
	IMPORT_C static void Cancel();
	IMPORT_C static void CancelTrigger();
	IMPORT_C static TBool IsDisplaying(TInt aHandle);
	};


/**
@publishedPartner
@deprecated
*/
class CEikBubbleHelp : public CCoeStatic
// The CEikBubbleHelp class implements global static storage and access to the object providing bubble help
// for the application.  
	{
	~CEikBubbleHelp();
public: 
	IMPORT_C static void SetTriggeredHelpL(MEikTriggeredHelp* aTriggeredHelp);
public:
	static void Trigger(const TDesC& aDes,const TRect& aRect,TInt aHandle=-1);
	static void Cancel();
	static void CancelTrigger();
	static TBool IsDisplaying(TInt aHandle);
private:
	inline CEikBubbleHelp();
	inline static CEikBubbleHelp* Self();
private:
	MEikTriggeredHelp* iHelp;
	};

inline CEikBubbleHelp::CEikBubbleHelp()
	: CCoeStatic(KEikBubbleHelpUid)
	{}

inline CEikBubbleHelp* CEikBubbleHelp::Self()
	{return STATIC_CAST(CEikBubbleHelp*,CCoeEnv::Static(KEikBubbleHelpUid));}

#endif
