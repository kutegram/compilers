// calprogresscallback.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//
#ifndef __CALPROGRESSCALLBACK_H__
#define __CALPROGRESSCALLBACK_H__

class MCalProgressCallBack
/** A call back class to show the progress of long-running operations. 

When a long-running operation is carried out on the instance view or the entry 
view, this class is used to signal its progress, and when the function is complete.

@publishedAll

*/
	{
public:

	/** Progress callback.
	
	This calls the observing class with the percentage complete of the current operation.
	
	@param aPercentageCompleted The percentage complete. */
	virtual void Progress(TInt aPercentageCompleted) = 0;
	
	/** Progress callback.
	
	This calls the observing class when the current operation is finished.
	
	@param aError The error if the operation failed, or KErrNone if successful. */
	virtual void Completed(TInt aError) = 0;
	
	/** 
    Asks the observing class whether progress callbacks are required. This
    is called once only to check if callbacks are enabled.
	
	@return If the observing class returns EFalse, then the Progress() function will not be called. 
    */
	virtual TBool NotifyProgress() = 0;
	};
	
// __CALPROGRESSCALLBACK_H__
#endif
