// S32MEM.INL
//
// Copyright (c) 1998-2007 Symbian Ltd.  All rights reserved.
//

// Class RMemWriteStream
inline RMemWriteStream::RMemWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
/** 
Constructs a write stream with an externalizer.  For example, CStoreMap implements 
MExternalizer<TStreamRef>. 

@param anExter Specifies an externalizer. 
@see MExternalizer
@see CStoreMap  
*/
	{}

// Class RDesWriteStream
inline RDesWriteStream::RDesWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
/** 
Constructs a write stream with an externalizer.  For example, CStoreMap implements 
MExternalizer<TStreamRef>. 

@param anExter Specifies an externalizer. 
@see MExternalizer
@see CStoreMap  
*/
	{}

// Class RBufWriteStream
inline RBufWriteStream::RBufWriteStream(const MExternalizer<TStreamRef>& anExter)
	: RWriteStream(anExter)
/** 
Constructs a write stream with an externalizer.  For example, CStoreMap implements 
MExternalizer<TStreamRef>. 

@param anExter Specifies an externalizer. 
@see MExternalizer
@see CStoreMap  
*/
	{}
	
inline void RBufWriteStream::Append(CBufBase& aBuf)
/** 
Open a stream that writes to a dynamic buffer using insert mode.

@param aBuf The dynamic buffer that will be the sink of this stream.
@see RBufWriteStream::Insert
*/
	{Insert(aBuf,aBuf.Size());}

