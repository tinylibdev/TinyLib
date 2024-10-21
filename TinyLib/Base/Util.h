#pragma once
#include "../Base/Win/WinAPI.h"
#include "Types.h"


namespace tl
{
    /// @brief Generate a random number, cryptographically strong.
    /// @return A random number which has the range of u32.
    static size_t random()
    {
        u32 number = 0;
        HCRYPTPROV hProv;

        if (CryptAcquireContextA(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT))
            CryptGenRandom(hProv, sizeof(number), reinterpret_cast<BYTE*>(&number));

        CryptReleaseContext(hProv, 0);

        return number;
    }


    /// @brief Get length of C-string.
    /// @param str C-string to get length of.
    /// @return Length of C-string.
    static size_t strlen(const ascii* str)
    {
        if (str == nullptr)
            return 0;

        size_t length = 0;
        while (str[length] != '\0')
            length++;

        return length;
    }
}