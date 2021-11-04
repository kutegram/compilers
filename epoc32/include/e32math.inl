// e32\include\e32math.inl
//
// Copyright (c) 1997-2001 Symbian Ltd. All rights reserved.
//

#if !defined(__E32MATH_INL__)
#define __E32MATH_INL__




// class TRealX

TBool TRealX::operator==(const TRealX &aVal) const
/**
@publishedAll


Compares this extended precision number for equality with another.

@param aVal A reference to the extended precision value to be compared.

@return True, if this extended precision number is equal to aVal;
        false, otherwise.
*/
	{
	return(Compare(aVal)&EEqual);
	}




TBool TRealX::operator!=(const TRealX &aVal) const
/**
@publishedAll


Compares this extended precision number for in-equality with another.

@param aVal A reference to the extended precision value to be compared.

@return True, if this extended precision number is not equal to aVal;
        false, otherwise.
*/
	{
	return!(Compare(aVal)&EEqual);
	}




TBool TRealX::operator>=(const TRealX &aVal) const
/**
@publishedAll


Compares this extended precision number for being greater than
or equal to another.

@param aVal A reference to the extended precision value to be compared.

@return True, if this extended precision number is greater than or equal
        to aVal, false, otherwise.
*/
	{
	return(Compare(aVal)&(EEqual|EGreaterThan));
	}




TBool TRealX::operator<=(const TRealX &aVal) const
/**
@publishedAll


Compares this extended precision number for being less than
or equal to another.

@param aVal A reference to the extended precision value to be compared.

@return True, if this extended precision number is less than or equal
        to aVal, false, otherwise.
*/
	{
	return(Compare(aVal)&(ELessThan|EEqual));
	}




TBool TRealX::operator>(const TRealX &aVal) const
/**
@publishedAll


Compares this extended precision number for being greater than
another.

@param aVal A reference to the extended precision value to be compared.

@return True, if this extended precision number is greater than aVal,
        false, otherwise.
*/
	{
	return(Compare(aVal)&EGreaterThan);
	}




TBool TRealX::operator<(const TRealX &aVal) const
/**
@publishedAll


Compares this extended precision number for being less than
another.

@param aVal A reference to the extended precision value to be compared.

@return True, if this extended precision number is less than aVal,
        false, otherwise.
*/
	{
	return(Compare(aVal)&ELessThan);
	}

#endif
