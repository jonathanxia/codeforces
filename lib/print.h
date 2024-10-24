#pragma once
#include <lib/macros.h>

// Printing
void init()
{
    ios_base::sync_with_stdio(false), cin.tie(nullptr);
    cout << setprecision(16) << std::fixed;
}

// Declarations of operator<< to avoid circular dependencies
template <typename T, size_t N> std::ostream &operator<<(std::ostream& os, const array<T, N>& a);
template <typename T1, typename T2> std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p);
template <typename K, typename V> std::ostream &operator<<(std::ostream &os, const unordered_map<K, V, custom_hash> &mp);
template <typename K, typename V> std::ostream &operator<<(std::ostream &os, const map<K, V> &mp);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::vector<T> &v);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::deque<T> &v);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &vv);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::set<T> &s);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::multiset<T> &s);
template <typename T> std::ostream &operator<<(std::ostream &os, const std::unordered_set<T, custom_hash> &s);
template <typename K, typename V> std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &mp);

// Actual definitions
template <typename T1, typename T2>
std::ostream& operator<<(std::ostream& os, const std::pair<T1, T2>& p)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    return os << "(" << p.first << ", " << p.second << ")";
#else
    return os << p.first << " " << p.second;
#endif
#else
    return os << p.first << " " << p.second;
#endif
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const unordered_map<K, V, custom_hash> &mp)
{
    os << "{ ";
    for (const auto &p : mp)
    {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const map<K, V> &mp)
{
    os << "{ ";
    for (const auto &p : mp)
    {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        os << *it;
        if (it != v.end() - 1)
        {
            os << " ";
        }
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &v)
{
    for (auto it = v.begin(); it != v.end(); ++it)
    {
        os << *it;
        if (it != v.end() - 1)
        {
            os << " ";
        }
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<std::vector<T>> &vv)
{
    walk(i, vv)
    {
#ifndef ONLINE_JUDGE
#ifdef DEBUG
        os << i << ": ";
#endif
#endif
        os << vv[i];
        if (i != len(vv) - 1)
        {
            os << '\n';
        }
    }
    return os;
}

template <typename T, size_t N>
std::ostream &operator<<(std::ostream& os, const array<T, N>& a) {
    os << "{";
    FOR(i, 0, (int) N - 1) {
        os << a[i];
        if (i < (int) N - 1) os << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::unordered_set<T, custom_hash> &s)
{
    os << "{ ";
    for (const auto &item : s)
    {
        os << item << " ";
    }
    os << "}";
    return os;
}

template <typename K, typename V>
std::ostream &operator<<(std::ostream &os, const std::unordered_map<K, V> &mp)
{
    os << "{ ";
    for (const auto &p : mp)
    {
        os << p.first << ": " << p.second << ", ";
    }
    os << "}";
    return os;
}

template <typename T>
void print(const T &t)
{
#ifdef INTERACTIVE
    std::cout << t << std::endl;
#else
#ifdef DEBUG
    std::cout << t << std::endl;
#else
    std::cout << t << "\n";
#endif
#endif
}

template <typename T, typename... Args>
void print(const T &t, const Args &...args)
{
    std::cout << t << " ";
    print(args...);
}

template <typename T>
void dprint(const T &t)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cout << t << std::endl;
#endif
#endif
}

template <typename T, typename... Args>
void dprint(const T &t, const Args &...args)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cout << t << " ";
    print(args...);
#endif
#endif
}

template <typename T>
void eprint(const T &t)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cerr << t << std::endl;
#endif
#endif
}

template <typename T, typename... Args>
void eprint(const T &t, const Args &...args)
{
#ifndef ONLINE_JUDGE
#ifdef DEBUG
    std::cerr << t << " ";
    eprint(args...);
#endif
#endif
}

// Fancy variable debugging, stolen from:
// https://codeforces.com/blog/entry/79024
#ifndef ONLINE_JUDGE
#ifdef DEBUG
int recur_depth = 0;
#define dbg(x)                                                                                                 \
    {                                                                                                          \
        ++recur_depth;                                                                                         \
        auto x_ = x;                                                                                           \
        --recur_depth;                                                                                         \
        cout << string(recur_depth, '\t') << #x << " = " << x_ << endl; \
    }
#else
#define dbg(x)
#endif
#else
#define dbg(x)
#endif

#ifndef ONLINE_JUDGE
#ifdef DEBUG
#define edbg(x)                                                                                                 \
    {                                                                                                          \
        ++recur_depth;                                                                                         \
        auto x_ = x;                                                                                           \
        --recur_depth;                                                                                         \
        cerr << string(recur_depth, '\t') << #x << " = " << x_ << endl; \
    }
#else
#define edbg(x)
#endif
#else
#define edbg(x)
#endif

#define SAY_YES { print("YES"); return; }
#define SAY_NO { print("NO"); return; }
#define SAY_Yes { print("Yes"); return; }
#define SAY_No { print("No"); return; }
#define SAY_NEG1 { print(-1); return; }

// Use these for writing an interactive server
#define server_read(x) ({cin >> (x); eprint("Server read:", (x));})
#define server_write(x) ({print((x)); eprint("Server wrote:", (x));})