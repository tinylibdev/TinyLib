#include "Memory.h"

namespace tl {
    // Allocate memory for amount <size>.
    void* malloc(size_t size)
    {
        return VirtualAlloc(NULL, size, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
    }

    // Free memory from pointer.
    void free(void* ptr)
    {
        VirtualFree(ptr, 0, MEM_RELEASE);
    }
}

// To enable float support
extern "C" int _fltused = 1;


#pragma function(memset)
void* __cdecl memset(void* ptr, int value, size_t size)
{
    unsigned char* p = static_cast<unsigned char*>(ptr);
    while (size--)
        *p++ = static_cast<unsigned char>(value);

    return ptr;
}


// Allocate memory for a new value.
void* operator new(size_t size) noexcept
{
    void* ptr = tl::malloc(size);
    if (!ptr) return nullptr;
    return ptr;
}

// Free memory from this variable.
void operator delete(void* ptr) noexcept
{
    tl::free(ptr);
}

// Allocate memory for a new array.
void* operator new[](size_t size) noexcept
{
    void* ptr = tl::malloc(size);
    if (!ptr) return nullptr;
    return ptr;
}

// Free memory from this array.
void operator delete[](void* ptr) noexcept
{
    tl::free(ptr); // Use custom free for arrays
}

// Unsigned int parameter is needed to overload compiler.
void operator delete(void* ptr, unsigned int size) noexcept
{
    tl::free(ptr);
}