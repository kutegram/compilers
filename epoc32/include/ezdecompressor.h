// EZLib: DECOMPRESSOR.H
// Copyright (C) Symbian LTD 1999-2003
//
// Declaration for Decompression class
//

#ifndef __EZDECOMPRESSOR_H__
#define __EZDECOMPRESSOR_H__

#include <e32base.h>
#include <ezstream.h>
#include <ezbufman.h>

/**
The CEZDecompressor class provides in-memory de-compression functions, including integrity checks of the compressed data.
This version of the library supports only one compression / de-compression method (deflation / inflation).  De-compression
can be done in a single step (using DecompressL()) if the buffers are large enough (for example if an input file is mmap'ed),
or can be done by repeated calls of the InflateL() function.  The source data is de-compressed to the target buffer (both source 
and target contained within the buffer manager argument).

@publishedAll

*/
class CEZDecompressor : public CEZZStream
	{
public:
	/** Decompression panic values */
	enum 
		{
		EInflateInitlialiserError = EUnexpected + 1,
		EInflateVersionError,
		EInflateTerminated,
		EInflateDictionaryError
		};
		
	/** Window Bits - the base two logarithm of the window size (the size of the history buffer) */
	enum
		{
		EMaxWBits = MAX_WBITS
		};

public:
	~CEZDecompressor();

	IMPORT_C static CEZDecompressor* NewLC(MEZBufferManager& aInit, TInt aWindowBits = EMaxWBits);
	IMPORT_C static CEZDecompressor* NewL(MEZBufferManager& aInit, TInt aWindowBits = EMaxWBits);

	IMPORT_C static CEZDecompressor* NewLC(MEZBufferManager& aInit, const TDesC8& aDictionary, TInt aWindowBits = EMaxWBits);
	IMPORT_C static CEZDecompressor* NewL(MEZBufferManager& aInit, const TDesC8& aDictionary, TInt aWindowBits = EMaxWBits);


	IMPORT_C void ResetL(MEZBufferManager& aInit);
	IMPORT_C TBool InflateL();

	IMPORT_C static void DecompressL(TDes8 &aDestination, const TDesC8 &aSource);

	private:
		enum TInflationState
			{
			ENoFlush,
			EFinalize,
			ETerminated
			};

	private:
		void SetDictionaryL();
		CEZDecompressor(MEZBufferManager* aInit);
		CEZDecompressor(MEZBufferManager* aInit, const TUint8 *aDictionary, TInt aLength);
		void ConstructL(TInt aWindowBits);

	private:
		MEZBufferManager* iBufferInit;
		TInflationState iInflationState;
		const TUint8* iDictionary;
		TInt iDictionaryLength;
	};

#endif


