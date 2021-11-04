// TXTETEXT.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//


 
TBool CEditableText::HasChanged()const
/** Tests whether the editable text object has been changed by an operation on 
it, as set by SetHasChanged().

@return ETrue if a change has occurred to the text object. EFalse if there 
has been no change. */
	{return iHasChanged;}


TBool CPlainText::FieldSetPresent()const
	{return (iFieldSet.IsPtr() && iFieldSet.AsPtr()!=NULL);}


 

const MTextFieldFactory* CPlainText::FieldFactory()const
/** Gets a pointer to the field factory used by the text object. The field factory 
may be set up using SetFieldFactory(), or may be specified in the NewL().

@return The field factory. NULL if no field factory has been set up. */
	{return (FieldSetPresent()) ? iFieldSet->FieldFactory() : NULL;}


void CPlainText::ConsumeAdornmentL(RReadStream& aStream)
	{
	TStreamId id;
	aStream>> id;
	}


TUid CPlainText::UidFromStreamL(RReadStream& aStream)
	{
	TUid uid;
	aStream>> uid;
	return uid;
	}
