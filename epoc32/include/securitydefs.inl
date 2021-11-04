// securitydefs.inl
//
// Copyright (c) 2003 Symbian Software Ltd. All rights reserved.
//
/**
 * @file
 * 
 * @publishedAll
 * 
 */


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline TKeyUsagePKCS15 operator|(TKeyUsagePKCS15 aLeft, TKeyUsagePKCS15 aRight)
	{
	return static_cast<TKeyUsagePKCS15>(static_cast<TUint>(aLeft) | static_cast<TUint>(aRight));
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline TKeyUsagePKCS15 operator&(TKeyUsagePKCS15 aLeft, TKeyUsagePKCS15 aRight)
	{
	return static_cast<TKeyUsagePKCS15>(static_cast<TUint>(aLeft) & static_cast<TUint>(aRight));
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline const TKeyUsagePKCS15& operator|=(TKeyUsagePKCS15& aLeft, TKeyUsagePKCS15 aRight)
	{
	aLeft = aLeft | aRight;
	return aLeft;
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline const TKeyUsagePKCS15& operator&=(TKeyUsagePKCS15& aLeft, TKeyUsagePKCS15 aRight)
	{
	aLeft = aLeft & aRight;
	return aLeft;
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline TKeyUsageX509 operator|(TKeyUsageX509 aLeft, TKeyUsageX509 aRight)
	{
	return static_cast<TKeyUsageX509>(static_cast<TUint>(aLeft) | static_cast<TUint>(aRight));
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline TKeyUsageX509 operator&(TKeyUsageX509 aLeft, TKeyUsageX509 aRight)
	{
	return static_cast<TKeyUsageX509>(static_cast<TUint>(aLeft) & static_cast<TUint>(aRight));
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline const TKeyUsageX509& operator|=(TKeyUsageX509& aLeft, TKeyUsageX509 aRight)
	{
	aLeft = aLeft | aRight;
	return aLeft;
	}


/** 
 *
 *
 * @param aLeft
 * @param aRight
 * @return
 */
inline const TKeyUsageX509& operator&=(TKeyUsageX509& aLeft, TKeyUsageX509 aRight)
	{
	aLeft = aLeft & aRight;
	return aLeft;
	}
