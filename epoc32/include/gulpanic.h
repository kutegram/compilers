// GULPANIC.H
//
// Copyright (c) 1997-2003 Symbian Ltd.  All rights reserved.
//

#if !defined(__GULPANIC_H__)
#define __GULPANIC_H__

/**
@internalComponent
*/
enum TEgulPanic
	{
	EEgulPanicResourceNullPointer,
	EEgulPanicResourceInvalidNumberType,
	EEgulPanicNullPointer,
	EEgulPanicLogicalColorNotFound,
	EEgulPanicLogicalColorAlreadyExists,
	EEgulPanicInvalidColorRange,
	EEgulPanicAppColorArrayNotFound,
	EEgulPanicNullTls,
	EEgulPanicInvalidSpriteResizeMode,
	EEgulPanicInvalidInternalSpriteResizeMode,
	EEgulPanicAttemptToAppendNullMember,
	EEgulPanicAttemptToAppendIncompleteMember,
	EEgulPanicInvalidSpriteIndex,
	EEgulPanicNegativeSpriteSize,
	EEgulPanicInvalidDigitType,
	EEgulPanicImplementationMoved,
	EEgulPanicCParaFormatAlignementValueNotSupported
	};

#endif
