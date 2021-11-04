// EIKPANIC.H
//
// Copyright (c) 1997-2006 Symbian Ltd.  All rights reserved.
//

#ifndef __EIKPANIC_H__
#define __EIKPANIC_H__

/**
@publishedPartner

*/
enum TEikPanic
	{
	EEikPanicInvalidPreviewPageNumber,
	EEikPanicStartupHeapTooSmall,
	EEikPanicNoLibraryOnCommandLine,
	EEikPanicNoDocumentOnCommandLine,
	EEikPanicAlertTextTooLong,
	EEikPanicCursorControlNotFocused,
	EEikPanicControlNotCursorOwner,
	EEikPanicNoHotKeyToRemove,
	EEikPanicNoSuchMenuItem,
	EEikPanicInvalidMenuPane,
	EEikPanicMenuBarTitleUpdateNotSupported,
	EEikPanicInvalidBounds,
	EEikPanicUnknownPlaybackCommand,
	EEikPanicSecretEditorTooLong,
	EEikPanicInvalidClockSize,
	EEikPanicInvalidClockType,
	EEikPanicInvalidClockSettings,
	EEikPanicScrollBarDoesNotExist,
	EEikPanicScrollBarManagerDoesNotExist,
	EEikPanicButtonArrayHigherThanScreen,
	EEikPanicButtonArrayWiderThanScreen,
	EEikPanicBArrayLengthExceeded,
	EEikPanicWorldManager,
	EEikPanicWorldSelector,
	EEikPanicWorldControllerDuplicateSelector,
	EEikPanicOutOfRange,
	EEikPanicNullPointer,
	EEikPanicWrongDisplayMode,
	EEikPanicCalendarInvalidResourceValue,
	EEikPanicPrintPreviewInvalidResourceValue,
	EEikPanicFieldDoesNotExist,
	EEikPanicEditComboInsufficientSize,
	EEikPanicInvalidNumberOfRowsOrColumns,
	EEikPanicButtonHasNoComponent,
    EEikPanicFSelNoSuchFolder,
	EEikPanicToolBarHasNoObserver,
	EEikPanicToolBarNullControl,
	EEikPanicNoSuchDialogPage,
	EEikPanicOverlongEikonServerMessage,
	EEikPanicCtGroupInvalidDimension,
	EEikPanicCtGroupInvalidNumberOfLines,
	EEikPanicCtGroupInsufficientInitialisation,
	EEikPanicColumnListInvalidBitmapIndex,
	EEikPanicHeaderFooterNullFileName,
	EEikPanicProcessNoStore,
	EEikPanicProcessWrongStoreType,
	EEikPanicDialogToolBarNoObserver,
	EEikPanicLabeledButtonInvalidHotKey,
	EEikPanicLabeledButtonInvalidButtonType,
	EEikPanicIllegalCrop,
	EEikPanicTimeNoDataForDialog,
	EEikPanicDtmfPlayerActive,
	EEikPanicNothingToDial,
	EEikPanicLogicalColorNotFound,
	EEikPanicLogicalColorAlreadyExists,
	EEikPanicInvalidColorRange,
	EEikPanicAppColorArrayNotFound,
	EEikPanicLabelNullText,
	EEikPanicNoLibraryEntryPoint,
	EEikPanicResourceFileNotRemoved,
	EEikPanicControlFactoryNotRemoved,
	EEikPanicButtonGroupDuplicateCleanupPos,
	EEikPanicButtonGroupCleanupCorrupt,
	EEikPanicButtonGroupDuplicateObserver,
	EEikPanicBadInlineEditingState1,
	EEikPanicBadInlineEditingState2,
	EEikPanicBadInlineEditingState3,
	EEikPanicBadInlineEditingState4,
	EEikPanicBadInlineEditingState5,
	EEikPanicBadInlineEditingState6,
	EEikPanicBadInlineEditingState7,
	EEikPanicBadInlineEditingState8,
	EEikPanicBadInlineEditingState9,
	EEikPanicBadInlineEditingState10,
	EEikPanicBadInlineEditingState11,
	EEikPanicBadInlineEditingState12,
	EEikPanicNoSuchMenuTitle,
	EEikPanicLibraryNotLoaded,
	EEikPanicScrollBarFrameNullScrollBar,
	EEikPanicAppUiNotConstructed,
	EEikPanicVirtualCursorLeaveNotExpected,
	EEikPanicCommandStackIsNull,
	EEikPanicVirtualCursorUndefinedError,
	EEikPanicCbaButtonInvalidId,
	EEikPanicNoButtonGroupFactory,
	EEikPanicButtonGroupNotFoundInFactory,
	EEikPanicListItemDrawerGraphicsContextIsNull,
	EEikPanicInvalidNumberOfLines,
	EEikPanicArrayLengthExceeded,
	EEikPanicInvalidIndex,
	EEikPanicInvalidLength,
	EEikPanicDebugKeysAlreadySet,
	};

/**
@internalComponent

*/
GLREF_C void Panic(TEikPanic aPanic);

// __EIKPANIC_H__
#endif
