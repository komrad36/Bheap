/*******************************************************************
*
*    Author: Kareem Omar
*    kareem.h.omar@gmail.com
*    https://github.com/komrad36
*
*    Last updated Dec 8, 2021
*******************************************************************/

#pragma once

#include <cstdint>

#if defined(__clang__) || defined(__GNUC__)
#define LIKELY(x) __builtin_expect(static_cast<bool>(x), 1)
#define UNLIKELY(x) __builtin_expect(static_cast<bool>(x), 0)
#else
#define LIKELY(x) static_cast<bool>(x)
#define UNLIKELY(x) static_cast<bool>(x)
#endif

template <class T>
static inline void Heappush(T* __restrict const pHeap, const uint64_t n, const T x)
{
    uint64_t i = n;
    while (LIKELY(i))
    {
        const uint64_t iNext = (i - 1) >> 1;
        if (UNLIKELY(x < pHeap[iNext]))
            break;
        pHeap[i] = pHeap[iNext];
        i = iNext;
    }
    pHeap[i] = x;
}

template <class T>
static inline void Heappop(T* __restrict const pHeap, const uint64_t n)
{
    const T x = pHeap[n - 1];
    uint64_t i = 0;
    while (LIKELY(i < (n - 1) >> 1))
    {
        const uint64_t j = (i << 1) + 1;
        const uint64_t iNext = j + static_cast<bool>(*(pHeap + j) < *(pHeap + j + 1));
        if (UNLIKELY(pHeap[iNext] < x))
            break;
        pHeap[i] = pHeap[iNext];
        i = iNext;
    }
    pHeap[i] = x;
}
