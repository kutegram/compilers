// GSMUPDU.INL
//
// Copyright (c) Symbian Software Ltd. 1999-2006.  All rights reserved.
//

/**
 *  @file
 *
 *  Contains inline method implementations from classes defined in gsmupdu.h
 */


/**
 *  Gets the PDU type.
 *  
 *  Once a PDU has been constructed it cannot change its type as the SMS
 *  elements present differ. Hence there is no function to set the type.
 *  
 *  @return PDU type 
 */
inline CSmsPDU::TSmsPDUType CSmsPDU::Type() const
	{
	return iSmsPDUType;
	}


/**
 *  Gets the Reply Path Error flag.
 *  
 *  @return True for Reply Path Error 
 */
inline TBool CSmsDeliverReport::IsRPError() const
	{
	return iIsRPError;
	}


/**
 *  Sets the Reply Path Error flag.
 *  
 *  @param aIsRPError Set to True for Reply Path Error 
 */
inline void CSmsDeliverReport::SetIsRPError(TBool aIsRPError)
	{
	iIsRPError=(TUint8) aIsRPError;
	}


/**
 *  Gets the Reply Path Error flag.
 *  
 *  @return True for Reply Path Error 
 */
inline TBool CSmsSubmitReport::IsRPError() const
	{
	return iIsRPError;
	}


/**
 *  Sets the Reply Path Error flag.
 *  
 *  @param aIsRPError Set to True for Reply Path Error 
 */
inline void CSmsSubmitReport::SetIsRPError(TBool aIsRPError)
	{
	iIsRPError=(TUint8) aIsRPError;
	}


/**
 *  Gets Paramater Indicator.
 *  
 *  @return True if Paramater Indicator is present 
 */
inline TBool CSmsStatusReport::ParameterIndicatorPresent() const
	{
	return iParameterIndicatorPresent;
	}


/**
 *  Sets Paramater Indicator.
 *  
 *  @param aPresent Set to True to set Parameter Indicator Present 
 */
inline void CSmsStatusReport::SetParameterIndicatorPresent(TBool aPresent)
	{
	iParameterIndicatorPresent=(TUint8) aPresent;
	}
