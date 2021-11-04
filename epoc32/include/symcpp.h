// e32\compsupp\symcpp\symcpp.h
//
// Copyright (c) 2005-2007 Symbian Ltd. All rights reserved.
//
// This is a preinclude file for the symbian cpp specific defintions from RVCT2.2 onwards
// 

#ifdef __ARMCC_VERSION
#if (__ARMCC_VERSION < 220000 || __ARMCC_VERSION >= 230000)
#error This instantiation of the build requires use of RVCT 2.2
#endif
#endif

// Deal with operator new issues here
#ifdef __cplusplus
namespace std {
	struct nothrow_t { };
	extern const nothrow_t nothrow;
}

IMPORT_C void* operator new(unsigned int aSize) __NO_THROW;

IMPORT_C void* operator new(unsigned int aSize,unsigned int aSize1) __NO_THROW;

IMPORT_C void* operator new[](unsigned int aSize) __NO_THROW;

IMPORT_C void* operator new(unsigned int aSize, const std::nothrow_t& aNoThrow) __NO_THROW;

IMPORT_C void* operator new[](unsigned int aSize, const std::nothrow_t& aNoThrow) __NO_THROW;

IMPORT_C void operator delete(void* aPtr) __NO_THROW;

IMPORT_C void operator delete[](void* aPtr) __NO_THROW;

IMPORT_C void operator delete(void* aPtr, const std::nothrow_t& aNoThrow) __NO_THROW;

IMPORT_C void operator delete[](void* aPtr, const std::nothrow_t& aNoThrow) __NO_THROW;

#endif
