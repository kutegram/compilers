// TXTFMLYR.INL
//
// Copyright (c) 1997-1999 Symbian Ltd.  All rights reserved.
//




inline CParaFormatLayer* CParaFormatLayer::CloneL()const
/** Constructs and returns a new CParaFormatLayer with identical formatting to 
the current layer. Note that the function does not copy the original layer's 
based-on link - the new layer's based-on link is set to NULL, so that the 
two layers may not have the same effective formatting.

@return A new paragraph format layer cloned from the current layer. */
	{return STATIC_CAST(CParaFormatLayer*,DoCloneL());}




inline CCharFormatLayer* CCharFormatLayer::CloneL()const
/** Constructs and returns a new CCharFormatLayer with identical formatting to 
the current layer. Note that the function does not copy the original layer's 
based-on link - the new layer's based-on link is set to NULL, so that the 
two layers may not have the same effective formatting.

@return A new character format layer cloned from the current layer. */
	{return STATIC_CAST(CCharFormatLayer*,DoCloneL());}
