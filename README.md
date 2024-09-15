# Competitive Programming Library

The cp library whose primary users are jonathanxia, kxia1729, and WyattWismer.

Project list:
* Tree shaker to reduce submission sizes
* Build out more of the lib/geo subpackage

# Constant Factors

Here are some notes about the CF server's constant factors. Everything is quoted
as `ms/1 mil ops`. These are slight upper bounds, as in I take the worst performance I
see on the codeforces servers.

* vec.push_back(vl(2)): 100ms
* vec.push_back(ll): 10ms
* DfsTree(1mil node tree): 200ms
* 1mil recursive func calls: 60ms
* Constructing vector(1mil): 2.3ms
* a[i] += a[i - 1] + a[i - 2]: 1.4ms
* a[i] *= a[i - 1] * a[i - 2]: 1.4ms
* a[i] = a[i - 1] / a[i - 2]: 11.2ms
* a[rand] = a[rand] + a[rand]: 6 ms

Cache locality can make things about 4x slower

## STL Data structures

* vec.push_back(ll): 10ms
* vec[i] (access): 1.4ms
* set<ll>.insert(ll): 250ms
* set<ll>.erase(ll): 150ms
* uset<ll>.insert(ll): 670ms
    * Reserving 250K beforehand -> 300ms
* uset<ll>.find(ll): 1ms
* uset<ll>.erase(ll): 320ms
To be determined: a somewhat contradictory timing gave this:
* `map<ll, ll>.insert()` random keys: 1000ms
* `set<ll>.insert()` random keys: 650ms
* `umap<ll, ll>.insert()` random keys: 500ms

Interestingly, uset<> is actually quite slow.

## lib/nt.h
Each thing run 1mil times
* `nt::get_digits(1bil, any base): 120ms` 
* `nt::sum_digits(1bil): 20ms`
* `MI * MI`: 12ms

## lib/ndarray.h

Used F_Chips_on_a_Line to benchmark this, which had 550M iterations in the hot-loop and
a time limit of 5s. The update was of the form
```
dp(n, i, w) = dp(n, i - 1, w) + dp(n - 1, i, w - fib[i]);
```
where `dp` was of type `MI`.

Comparison of performances
* Using C-style array `MI dp[2][11][50000]`: 2ms
* `std::array<>`: 2ms
* `ndarray` with bounds checking and `CHECK_DEFAULT=true`: 2.5ms
* `ndarray` with bounds checking and `CHECK_DEFAULT=false`: 2.4ms
* `ndarray` without bounds checking, and `CHECK_DEFAULT_VALUE=false`: 2.2ms
* `vvvMI`: 2.5ms

Using `std::array` seems to still have a 20% advantage over `ndarray` in general. For a `2s` time
limit problem, this means C-style can do `1e9` accesses while `ndarray` can do `8e8`.

## Graph-related constant factors

* Constructing vvpl with 1mil edges: `135ms`
* `atcoder::scc`: `350ms`.
* `graph::topo_sort`: `110ms`

# Local testing of constant factors

* Jonathan's laptop is about 3x faster than cf servers