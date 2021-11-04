// EIKCOCTLPANIC.H
//
#if !defined(__EIKCOCTL_PAN__)
#define __EIKCOCTL_PAN__
enum TEikCoCtlPanic
	{
	EEikPanicColumnListLayoutError,
	EEikPanicInvalidUseOfListBoxShortcuts,
	EEikPanicUnexpectedSpaces,
	EEikPanicScrollBarExtensionNotCreated,
	EEikPanicListBoxItemDrawerNotCreated,
	EEikPanicObjectNotFullyConstructed,
	};
#endif

GLREF_C void Panic(TEikCoCtlPanic aPanic);