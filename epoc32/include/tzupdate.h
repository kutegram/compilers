// TZUPDATE.H
//
// Copyright (c) Symbian Software Ltd 2004-2005. All rights reserved.
//

#ifndef __TZUPDATE_H__
#define __TZUPDATE_H__

#include <e32cmn.h> // TUid.

/** UTC Offset update notification constants. When the UTC offset is automatically
adjusted for Daylight Saving then it is possible to receive
notification using the Publish and Subscribe API with the
values defined here. Note that this property is updated by the Time Zone Server
as this is the only component that can modify the UTC Offset.

@see RProperty in e32property.h
@publishedAll


*/
namespace NTzUpdate
    {
    const TUid KPropertyCategory = { 0x1020383E };

    enum TPropertyKeys
        {
        EUtcOffsetChangeNotification,
        ECurrentTimeZoneId,
        EHomeTimeZoneId,
        };

	struct TTimeZoneChange
		{
		TInt iNewTimeZoneId;
		TInt iOldTimeZoneId;
		};
    }

// __TZUPDATE_H__
#endif
