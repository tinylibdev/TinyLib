// Deadly zone of death, beware.
#pragma once
#include "../Base/Win/WinAPI.h"


namespace tl {
    // Custom malloc and free can go in namespace.
    void* malloc(size_t size);
    void free(void* ptr);
}


#ifndef FLOAT_SUPPORT_H
#define FLOAT_SUPPORT_H

// Need this to support float numbers throughout the library.
extern "C" int _fltused;

#endif // FLOAT_SUPPORT_H


// The compiler tries to optimize with memset, so we need to overwrite it.
extern "C" void* __cdecl memset(void*, int, size_t);
#pragma intrinsic(memset)

// Also overloading new and delete.
void* operator new(size_t size) noexcept;
void operator delete(void* ptr) noexcept;
void* operator new[](size_t size) noexcept;
void operator delete[](void* ptr) noexcept;
void operator delete(void* ptr, unsigned int size) noexcept;