// EIKBUSYMSGWIN.H
//
// Copyright (c) Symbian Software Ltd 2004-2006.  All rights reserved.
//

#ifndef __EIKBUSYMSGWIN_H__
#define __EIKBUSYMSGWIN_H__

/** An interface class for creating customized busy message windows 

@publishedPartner 
*/
class MEikBusyMsgWin
	{
public:
	/** Displays a busy message window after a specified duration.
	@param aText The text for the busy message.
	@param aCorner The alignment for the busy message.
	@param aInitialDelay The time period after which the busy message is displayed. */
	virtual void StartDisplaySpecifyingInitialDelay(const TDesC& aText, TGulAlignment aCorner, TTimeIntervalMicroSeconds32 aInitialDelay) =0;

	/** Displays the message window with the specified text and alignment.

	@param aText The text to display in the message. 
	@param aCorner The position in which the message window will appear. There 
	are 9 options for this, each square of a 3 by 3 matrix on the screen. */
	virtual void StartDisplay(const TDesC& aText, TGulAlignment aCorner) =0;
	
	/** Deletes the object, calling it's private destructor.
	*/
	virtual void Release() = 0;
	};
	
// __EIKBUSYMSGWIN_H__
#endif
