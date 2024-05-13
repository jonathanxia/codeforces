#pragma once
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;

template<typename T>
using ordered_set = tree<
    T,
    null_type,
    less<T>,
    rb_tree_tag,
    tree_order_statistics_node_update>;
// find_by_order, order_of_key
// Detailed doc:
//    order_of_key(param): returns number of elements < param
//    find_by_order(idx): returns iterator to the idx-th element of the tree, 0-indexed
//        e.g., find_by_order(0) is the smallest element

template <typename T>
std::ostream &operator<<(std::ostream &os, const ordered_set<T> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}
