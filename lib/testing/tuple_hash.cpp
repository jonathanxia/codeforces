#include "../common.h"
#include <tuple>
namespace std {
namespace {

    // Code from boost
    // Reciprocal of the golden ratio helps spread entropy
    //     and handles duplicates.
    // See Mike Seymour in magic-numbers-in-boosthash-combine:
    //     http://stackoverflow.com/questions/4948780

    template <class T>
    inline void hash_combine(std::size_t& seed, T const& v)
    {
        seed ^= std::hash<T>()(v) + 0x9e3779b9 + (seed << 6) + (seed >> 2);
    }

    // Recursive template code derived from Matthieu M.
    template <class Tuple, size_t Index = std::tuple_size<Tuple>::value - 1>
    struct HashValueImpl {
        static void apply(size_t& seed, Tuple const& tuple)
        {
            HashValueImpl<Tuple, Index - 1>::apply(seed, tuple);
            hash_combine(seed, std::get<Index>(tuple));
        }
    };

    template <class Tuple>
    struct HashValueImpl<Tuple, 0> {
        static void apply(size_t& seed, Tuple const& tuple)
        {
            hash_combine(seed, std::get<0>(tuple));
        }
    };
}

template <typename... TT>
struct hash<std::tuple<TT...>> {
    size_t
    operator()(std::tuple<TT...> const& tt) const
    {
        size_t seed = 0;
        HashValueImpl<std::tuple<TT...>>::apply(seed, tt);
        return seed;
    }
};
}
int main()
{
    vector<tuple<ll, ll, ll, ll, ll>> lol(100'000);
    walk(i, lol)
    {
        ll f1, f2, f3, f4, f5;
        cin >> f1 >> f2 >> f3 >> f4 >> f5;
        lol[i] = make_tuple(f1, f2, f3, f4, f5);
    }
    unordered_set<tuple<ll, ll, ll, ll, ll>> a;
    auto start = chrono::high_resolution_clock::now();
    walk(i, lol)
    {
        a.insert(lol[i]);
    }
    auto stop = chrono::high_resolution_clock::now();
    auto duration = chrono::duration_cast<chrono::milliseconds>(stop - start);
    print("Time to load:", duration.count(), "milliseconds");
    size_t collisions = 0, empty = 0;
    for (auto bucket = a.bucket_count(); bucket--;) {
        if (a.bucket_size(bucket) == 0)
            empty++;
        else
            collisions += a.bucket_size(bucket) - 1;
    }
    std::cout << "a = " << a.max_load_factor() << ' ' << a.load_factor() << ' '
              << ' ' << a.bucket_count() << ' ' << collisions << ' ' << empty << '\n';
    print("Max Load Factor:", a.max_load_factor());
    print("Number of buckets:", a.bucket_count());
    print("Number of collisions:", collisions);
    ll n = 100'000;
    print("Expected number of collisions:", (n * (n - 1)) / (2 * a.bucket_count()));
}