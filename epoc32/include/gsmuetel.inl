// GSMUETEL.INL
//
// Copyright (c) Symbian Software Ltd. 2001-2006.  All rights reserved.
//

/**
 *  @file
 *  @publishedAll
 *      
 */

/**
 *  Constructor.
 */
inline TGsmSms::TGsmSms()
	{
	}


/**
 *  Gets a descriptor containing the PDU.
 *  
 *  @return Descriptor containing the PDU 
 */
inline const TDesC8& TGsmSms::Pdu() const
	{
	return iPdu;
	}


/**
 *  Sets the PDU.
 *  
 *  @param aPdu Descriptor containing the PDU 
 */
inline void TGsmSms::SetPdu(const TDesC8& aPdu)
	{
	iPdu = aPdu;
	}


/**
 *  Gets the Service Centre Address.
 *  
 *  @return Service Centre Address 
 */
inline const TGsmSmsTelNumber& TGsmSms::Sca() const
	{
	return iSca;
	}


/**
 *  Sets the Service Centre Address.
 *  
 *  @param aSca Service Centre Address 
 */
inline void TGsmSms::SetSca(const TGsmSmsTelNumber& aSca)
	{
	iSca = aSca;
	}
