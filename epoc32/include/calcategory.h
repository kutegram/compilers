// calcategory.h
//
// Copyright (c) Symbian Software Ltd 2005.  All rights reserved.
//

#ifndef __CALCATEGORY_H__
#define __CALCATEGORY_H__

#include <e32std.h>
#include <e32base.h>

class CCalCategoryImpl;

/** Calendar categories can be associated with a calendar entry.

There are 12 built in category types defined by TCalCategoryType. Additionally,
it is possible to define extended category types which are held as a descriptor
of any length.

Any number of categories can be specified for an entry. CCalEntry provides member 
functions for adding, deleting and fetching categories for an entry. 

CCalCategoryManager functions enable the client to add\\delete\\fetch categories 
from a Calendar session and to get a list of entries filtered by their category. 
@publishedAll

*/
NONSHARABLE_CLASS(CCalCategory) : public CBase
    {
public:
	/** Calendar category type.
	@publishedAll
	
	*/
	enum TCalCategoryType 
		{
		/** Appointment */
		ECalAppointment,
		/** Business */
		ECalBusiness,
		/** Education */
		ECalEducation,	
		/** Holiday */
		ECalHoliday,
		/** Meeting */
		ECalMeeting,
		/** All other types */
		ECalMiscellaneous, 
		/** Personal */
		ECalPersonal,
		/** Phone call */
		ECalPhoneCall,
		/** Sick day */
		ECalSickDay,
		/** Special occasion */
		ECalSpecialOccasion,
		/** Travel */
		ECalTravel,
		/** Vacation */
		ECalVacation,
		/** Extended */
		ECalExtended
		};

public:
	IMPORT_C static CCalCategory* NewL(TCalCategoryType aCategory);
	IMPORT_C static CCalCategory* NewL(const TDesC& aExtendedName);
	IMPORT_C ~CCalCategory();

	IMPORT_C TCalCategoryType Category() const;
	IMPORT_C const TDesC& ExtendedCategoryName() const;
	
public:	
	CCalCategoryImpl* Impl() const;
	static CCalCategory* NewL(CCalCategoryImpl* aImpl);

private:
	CCalCategory();
	CCalCategory(CCalCategoryImpl* aImpl);
	void ConstructL(TCalCategoryType aCategory);
	void ConstructL(const TDesC& aExtendedName);

private: // member data
	CCalCategoryImpl* iCalCategoryImpl;
	};
	
// __CALCATEGORY_H__
#endif
