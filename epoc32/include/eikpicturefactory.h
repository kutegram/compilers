// EIKPICTUREFACTORY.H
//
// Copyright (c) Symbian Software Ltd 1997 - 2006.  All rights reserved.
//


#ifndef __EIKPICTUREFACTORY_H__
#define __EIKPICTUREFACTORY_H__

#include <e32std.h>		// class TUid
#include <gdi.h>		// class TPictureHeader;


/** Provides the support for embedding something other than a CApaDoor. 

@publishedAll 
*/
class MEikPictureFactory
	{
public:
	IMPORT_C virtual TUid Id() const;
	/** Tests if the factory supports the specified picture type.
	
	@param aPictureType The picture type.
	@return ETrue if the factory supports the specified picture type, otherwise 
	EFalse. */
	virtual TBool SupportsPictureType(TUid aPictureType) const=0;
	/** Gets a pointer to the picture factory.
	
	Use of this function does not transfer ownership of the picture factory to 
	the caller.
	
	@param aPictureType The picture type.
	@return Pointer to the picture factory. */
	virtual const MPictureFactory* PictureFactory(TUid aPictureType) const=0;
	/** Inserts a new picture object. 
	
	Ownership of aData transfers immediately the function is called.
	
	@param aPictureType The picture type.
	@param aData The base address of the data.
	@return The picture header. */
	virtual TPictureHeader InsertL(TUid aPictureType, CBase* aData)=0;
	/** Enables editing/viewing of an object
	
	@param aPictureHeader The picture header.
	@param aReadOnly ETrue if object is read only, otherwise EFalse. */
	virtual void EditL(const TPictureHeader& aPictureHeader, TBool aReadOnly)=0;
private:
	IMPORT_C virtual void MEikPictureFactory_Reserved_1();
	IMPORT_C virtual void MEikPictureFactory_Reserved_2();
	};


// __EIKPICTUREFACTORY_H__
#endif
