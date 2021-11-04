//
// TRbuf.h
// Copyright (c) 2005 Symbian Software Ltd. All rights reserved.
//

/**
 * @file
 * @internalTechnology
 */

#if (!defined TRBUF_H)
#define TRBUF_H

#include <e32base.h>
#include <e32std.h>

namespace Elements
{

class TRBuf8 : public RBuf8
/**
	class to provide a RBuf8 destructor
*/
	{
	public:
		static TRBuf8* New(TInt aMaxLength)
			{
			TRBuf8* self = new TRBuf8;
			if (self!=NULL)
				{
				if (self->Create(aMaxLength)!=KErrNone)
					{
					delete self;
					self = NULL;
					}
				}
			return self;
			}

		static TRBuf8* NewL(TInt aMaxLength)
			{
			TRBuf8* self = new (ELeave) TRBuf8;
			CleanupStack::PushL(self);
			self->CreateL(aMaxLength);
			CleanupStack::Pop(self);
			return self;
			}

		~TRBuf8()
			{
			Close();
			}
	};

class TRBuf16 : public RBuf16
/**
	class to provide a RBuf16 destructor
*/
	{
	public:
		static TRBuf16* New(TInt aMaxLength)
			{
			TRBuf16* self = new TRBuf16;
			if (self!=NULL)
				{
				if (self->Create(aMaxLength)!=KErrNone)
					{
					delete self;
					self = NULL;
					}
				}
			return self;
			}

		static TRBuf16* NewL(TInt aMaxLength)
			{
			TRBuf16* self = new (ELeave) TRBuf16;
			CleanupStack::PushL(self);
			self->CreateL(aMaxLength);
			CleanupStack::Pop(self);
			return self;
			}

		~TRBuf16()
			{
			Close();
			}
	};

#if defined(_UNICODE)
typedef TRBuf16 TRBuf;
#else
typedef TRBuf8 TRBuf;
#endif

} //namespace Elements


//TRBUF_H
#endif

