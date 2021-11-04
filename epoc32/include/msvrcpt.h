// MSVRCPT.H
//
// Copyright (c) 1998 Symbian Ltd.  All rights reserved.
//

#if !defined(__MSVRCPT_H__)
#define __MSVRCPT_H__

class RWriteStream;

//**********************************
// CMsvRecipient
//**********************************
//
// Base class for  multiple recipients
//

class CMsvRecipient : public CBase
/** Base class for information relating to a message recipient. 
@publishedAll

*/
	{
public:
	/** Message sending status for a recipient. 
@publishedAll

*/
	enum TRecipientStatus 
							{	
	/** Message is not sent. */
							ENotYetSent=0,
	/** Message has been sent. */
							ESentSuccessfully=1,
	/** Message sending failed. */
				 			EFailedToSend=2};
	IMPORT_C virtual void InternalizeL(RReadStream& aStream);
	IMPORT_C virtual void ExternalizeL(RWriteStream& aStream) const;
	inline TRecipientStatus Status() const;
	inline void SetStatus(TRecipientStatus aStatus);
	inline TInt Error() const;
	inline void SetError(TInt aError);
	inline const TTime& Time() const;
	inline TTime& Time();
	inline TInt Retries() const;
	inline void IncreaseRetries();
	inline void ResetRetries();
protected:
	IMPORT_C CMsvRecipient();
private:
	TRecipientStatus iStatus;
	TInt   iError;
	TInt   iRetries;
	TTime	 iTime;
	};

#include <msvrcpt.inl>

#endif
