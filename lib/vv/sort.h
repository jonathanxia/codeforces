#pragma once
#include <lib/common.h>
namespace vv {

template <typename T>
struct Identity {
    constexpr const T& operator()(const T& value) const
    {
        return value;
    }
};


template <typename T, typename KeyFunc = Identity<T>>
void sort(vector<T>& a, int start = 0, int end = -1, KeyFunc keyFunc = Identity<T> {})
{
    if (end < 0) {
        end += len(a);
    }
    if (start >= end || end >= len(a)) {
        return; // Invalid indices or empty range
    }

    std::stable_sort(a.begin() + start, a.begin() + end + 1,
        [&keyFunc](const T& x, const T& y) {
            return keyFunc(x) < keyFunc(y);
        });
}

template <typename T, typename KeyFunc = Identity<T>>
void rsort(vector<T>& a, int start = 0, int end = -1, KeyFunc keyFunc = Identity<T> {})
{
    if (end < 0) {
        end += len(a);
    }
    if (start >= end || end >= len(a)) {
        return; // Invalid indices or empty range
    }

    std::stable_sort(a.begin() + start, a.begin() + end + 1,
        [&keyFunc](const T& x, const T& y) {
            return keyFunc(x) > keyFunc(y);
        });
}
}