/*
* ============================================================================
*  Name        : eikcal.h
*  Part of     : S60 UI Framework / EikCtl
*  Description : Interface class for EIKON calendar observer.
*  Version     : %version: 1 %
*
*  Copyright © 2002-2006 Nokia.  All rights reserved.
*  This material, including documentation and any related computer
*  programs, is protected by copyright controlled by Nokia.  All
*  rights are reserved.  Copying, including reproducing, storing,
*  adapting or translating, any or all of this material requires the
*  prior written consent of Nokia.  This material also contains
*  confidential information which may not be disclosed to others
*  without the prior written consent of Nokia.
* ============================================================================
*/

#ifndef __EIKCAL_H__
#define __EIKCAL_H__

#include <eikbctrl.h>
#include <eikscbut.h>
#include <eikcmbut.h>

/**
 * Calendar observer interface.
 *
 * <b> Not used in S60. </b>
 *
 * @lib eikctl.lib
 * @since S60 0.9
 */
class MEikCalendarObserver
	{
public:

    /**
     * <b> Not used in S60. </b>
     */
	virtual void GetMinimumAndMaximumAndInitialDatesForCalendarL(
	                                            TTime& aMinimumDate,
	                                            TTime& aMaximumDate,
	                                            TTime& aInitialDate) const=0;
	
	/**
	 * <b> Not used in S60. </b>
     */
	virtual void SetDateFromCalendarAndDrawNow(const TTime& aDate)=0;
	};

#endif // __EIKCAL_H__
