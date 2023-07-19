#include "../common.h"

int main()
{
    init();
    vvl tuples(100'000);
    walk(i, tuples)
    {
        vl tuple(5);
        cin >> tuple;
        tuples[i] = tuple;
    }
    uset<vl> a;
    auto start = chrono::high_resolution_clock::now();
    walk(i, tuples)
    {
        a.insert(tuples[i]);
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