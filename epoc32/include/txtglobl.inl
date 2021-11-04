// TXTGLOBL.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//




const CParaFormatLayer* CGlobalText::GlobalParaFormatLayer()const
/** Gets the paragraph format layer referenced by the global text object.

@return Pointer to the paragraph format layer referenced by the global text 
object. */
	{return iGlobalParaFormatLayer;}
	


	
const CCharFormatLayer* CGlobalText::GlobalCharFormatLayer()const
/** Gets the character format layer referenced by the global text object.

@return Pointer to the character format layer referenced by the global text 
object. */
	{return iGlobalCharFormatLayer;}

