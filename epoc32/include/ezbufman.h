// EZLib: BUFMAN.H
// Copyright (C) Symbian LTD 1999-2003
//
// Defines Mixin class for a BufferManager
//

#ifndef __EZBUFFERMANAGER_H__
#define __EZBUFFERMANAGER_H__

class CEZZStream;

/**
Interface class to manage input and output buffers for compression and de-compression

@publishedAll

*/
class MEZBufferManager
	{
public:

	/**
	Initialise the stream with input and output buffers and starts reading

	@param aZStream the stream to initialise
	*/
	virtual void InitializeL(CEZZStream &aZStream) = 0;
	
	/**
	Set the stream's input buffer and starts reading
	
	@param aZStream the steam whose input buffer to set
	*/	
	virtual void NeedInputL(CEZZStream &aZStream) = 0;
	
	/**
	Set the stream's output buffer and start writing

	@param aZStream the steam whose output buffer to set
	*/	
	virtual void NeedOutputL(CEZZStream &aZStream) = 0;
	
	/**
	Finish writing to the stream

	@param aZStream the stream to complete writing to
	*/	
	virtual void FinalizeL(CEZZStream &aZStream) = 0;
	};

#endif

