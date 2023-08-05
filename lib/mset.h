#include "common.h"

typedef multiset<ll> msetl;
namespace mset {
template <typename S, typename T>
void mset_del(S& ss, T x)
{
    auto it = ss.find(x);
    if (it == ss.end()) {
        throw std::out_of_range("element not found");
    }
    ss.erase(it);
}

template <typename S, typename T>
void mset_move(S& ss1, S& ss2, T x)
{
    auto ptr = ss1.find(x);
    if (ptr != ss1.end()) {
        ss1.erase(ptr);
        ss2.insert(x);
    } else {
        throw std::out_of_range("element not found");
    }
}

template <typename T>
T min(multiset<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set min");
    }
    return *(ss.begin());
}

template <typename T>
T max(multiset<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set max");
    }
    return *(ss.rbegin());
}

template <typename T>
T min(set<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set min");
    }
    return *(ss.begin());
}

template <typename T>
T max(set<T>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set max");
    }
    return *(ss.rbegin());
}

template <typename T, typename V>
T min(map<T, V>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set min");
    }
    return (ss.begin())->first;
}

template <typename T, typename V>
T max(map<T, V>& ss)
{
    if (ss.empty()) {
        throw out_of_range("Empty set max");
    }
    return (ss.rbegin())->first;
}
}