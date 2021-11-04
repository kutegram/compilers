// GSMUETEL.H
//
// Copyright (c) Symbian Software Ltd. 2001-2007.  All rights reserved.
//


/**
 *  
 *  @file
 *  This file contains the header file of the etel functions that have to be adapted later
 *  
 */

#ifndef __GSMUETEL_H__
#define __GSMUETEL_H__

#include <e32base.h>
#include <gsmunmspacemobmsg.h>
#include <gsmuelem.h>


/**
 *  Basic SMS class that contains some of the Etel mulit-mode SMS types.
 *  @publishedAll
 *  
 */
class TGsmSms
	{
public:
	inline TGsmSms();
	inline const TDesC8& Pdu() const;
	inline void SetPdu(const TDesC8& aPdu);
	inline const TGsmSmsTelNumber& Sca() const;
	inline void SetSca(const TGsmSmsTelNumber& aSca);

private:
	NMobileSmsMessaging::TMobileSmsGsmTpdu iPdu;	///< Storage for the PDU
	TGsmSmsTelNumber iSca;							///< Storage for the SCA
	};

/** Responsibility for submit/delivery reports. */
	enum TSmsReportResponsibility
		{
	/** ME has report resposibility. */
		ESmsReportME,
	/** Client has report resposibility. */
		ESmsReportClient
		};
	struct TSmsReportSetting
/**
 *  Flags for report responsibility.
 *  @internalComponent
 */
		{
	/** Responsibility for delivery reports. */
		TSmsReportResponsibility iDeliverReports;
	/** Responsibility for submit reports. */
		TSmsReportResponsibility iSubmitReports;
		};

#include <gsmuetel.inl>

// !defined __GSMUETEL_H__
#endif
