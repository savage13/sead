#pragma once

#include <string>
#include <sead/seadMemUtilCafe.hpp>
#include <sead/seadSafeString.h>

namespace sead {

template <typename T>
inline s32
SafeStringBase<T>::calcLength() const
{
    assureTerminationImpl_();
    s32 length = 0;
    for (;;)
    {
        if (length > cMaximumLength || mStringTop[length] == cNullChar)
            break;

        length++;
    }

    if ( length > cMaximumLength )
        return 0;

    return length;
}

template <typename T>
inline s32
BufferedSafeStringBase<T>::copy(const SafeStringBase<T>& src, s32 copyLength)
{
    T* dst = getMutableStringTop_();
    if (copyLength < 0)
        copyLength = src.calcLength();

    if (copyLength >= mBufferSize)
        copyLength = mBufferSize - 1;

    std::char_traits<T>::copy(dst, src.c_str(), copyLength);
    dst[copyLength] = SafeStringBase<T>::cNullChar;

    return copyLength;
}

} // namespace sead
