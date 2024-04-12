/*******************************************************************
*
*    Author: Kareem Omar
*    kareem.h.omar@gmail.com
*    https://github.com/komrad36
*
*    Last updated Apr 12, 2024
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
        if (UNLIKELY(!(pHeap[iNext] < x)))
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
        if (UNLIKELY(!(x < pHeap[iNext])))
            break;
        pHeap[i] = pHeap[iNext];
        i = iNext;
    }
    pHeap[i] = x;
}

template <class T>
static inline void Heapify(T* __restrict const pHeap, const uint64_t n)
{
    if (n < 2)
        return;
    uint64_t i = (n - 2) >> 1;
    if (!(n & 1))
    {
        const uint64_t iLeft = (i << 1) + 1;
        const T a = pHeap[i];
        const T b = pHeap[iLeft];
        const bool cond = static_cast<bool>(a < b);
        pHeap[i] = cond ? b : a;
        pHeap[iLeft] = cond ? a : b;
        if (i-- == 0)
            return;
    }
    if (i)
    {
        do
        {
            const uint64_t iLeft = (i << 1) + 1;
            const uint64_t iRight = (i << 1) + 2;
            const T left = pHeap[iLeft];
            const T right = pHeap[iRight];
            const T parent = pHeap[i];
            const bool cond = static_cast<bool>(left < right);
            const T larger = cond ? right : left;
            const uint64_t iLarger = cond ? iRight : iLeft;
            const bool cond2 = static_cast<bool>(parent < larger);
            pHeap[i] = cond2 ? larger : parent;
            pHeap[iLarger] = cond2 ? parent : larger;
        } while (LIKELY(i-- != n >> 2));
    }
    const uint64_t n1 = n - 1;
    do
    {
        const T x = pHeap[i];
        uint64_t j = i;
        for (;;)
        {
            const uint64_t iLeft = (j << 1) + 1;
            if (UNLIKELY(iLeft >= n1))
            {
                if (LIKELY(iLeft == n1 && static_cast<bool>(x < pHeap[iLeft])))
                {
                    pHeap[j] = pHeap[iLeft];
                    j = iLeft;
                }
                break;
            }
            const T left = pHeap[iLeft];
            const T right = pHeap[iLeft + 1];
            const bool cond = static_cast<bool>(left < right);
            const uint64_t iLarger = iLeft + cond;
            const T larger = cond ? right : left;
            if (UNLIKELY(!(x < larger)))
                break;
            pHeap[j] = larger;
            j = iLarger;
        }
        pHeap[j] = x;
    } while (UNLIKELY(i--));
}
