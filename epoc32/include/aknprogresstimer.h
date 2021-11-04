/*
* ============================================================================
*  Name     : AknProgressTimer.h
*  Part of  : Avkon
*
*  Description:
*  Version:
*
*  Copyright © 2002 Nokia Corporation.
*  This material, including documentation and any related 
*  computer programs, is protected by copyright controlled by 
*  Nokia Corporation. All rights are reserved. Copying, 
*  including reproducing, storing,  adapting or translating, any 
*  or all of this material requires the prior written consent of 
*  Nokia Corporation. This material also contains confidential 
*  information which may not be disclosed to others without the 
*  prior written consent of Nokia Corporation.
* ============================================================================
*/
// AknProgressTimer.h: interface for the CAknProgressTimer class.
//
//////////////////////////////////////////////////////////////////////

#ifndef __AKNPROGRESSTIMER__
#define __AKNPROGRESSTIMER__

#include <e32base.h>

struct TTimerModel
  {
  TInt iFinalValue;
  TInt iHundreths;
  TInt iIncrement;
  TBool iRunning;
  };
class CAknNoteControl;

NONSHARABLE_CLASS(CAknProgressTimer) : public CTimer  
  {
 public:
	CAknProgressTimer();
	virtual ~CAknProgressTimer();
  void ConstructL(TTimerModel* aModel,CAknNoteControl* aContainer,TCallBack aCallBack);
  void AdjustRunningState();
private:
  void Queue();
  void RunL();
private:
  TTimerModel* iModel;
  CAknNoteControl* iContainer;
  TCallBack iCallBack;
  };

#endif 
