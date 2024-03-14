#pragma once
#include <lib/common.h>

namespace nt {
vl primes;
vl is_composite;
bool sieve_done = false;

void do_sieve(ll max_prime)
{
    is_composite.resize(max_prime + 1);
    FOR(d, 2, max_prime)
    {
        if (!is_composite[d]) {
            primes.push_back(d);

            int x = 2 * d;
            while (x <= max_prime) {
                is_composite[x] = d;
                x += d;
            }
        }
    }
    sieve_done = true;
}

bool is_prime(ll n)
{
    // Checks if n is prime
    if (n <= 1) {
        return false;
    }

    if (n < len(is_composite)) {
        return !is_composite[n];
    }

    ll p = *prev(primes.end());
    if (p * p < n) {
        throw out_of_range("Generate more primes please");
    }

    ll i = 0;
    while (primes[i] * primes[i] <= n) {
        if (n % primes[i] == 0) {
            return false;
        }
        i++;
    }
    return true;
}

template <typename T=ll, typename T2=ll>
T sum_digits(T n, T2 b)
{
    T sum(0);
    while (n > 0) {
        sum += n % b;
        n /= b;
    }
    return sum;
}

template <typename T=ll, typename T2=ll>
vector<T2> get_digits(T n, T2 b, ll pad = -1)
{
    vector<T2> ans;
    while (n > 0) {
        ans.push_back(T2(n % b));
        n /= b;
    }
    while (len(ans) < pad) {
        ans.pb(T2(0));
    }
    return ans;
}

template <typename T=ll, typename T2=ll>
T digits_to_num(const vector<T2>& digs, T2 b)
{
    T s(0);
    DOR(i, len(digs) - 1, 0)
    {
        s *= b;
        s += digs[i];
    }
    return s;
}

/**
 * Computes pow() under a mod.
 * 
 * Specficially, base^e (mod m)
*/
template <typename T1=ll, typename T2=ll, typename T3=ll>
typename std::enable_if<!std::is_same<T1, int>::value, T1>::type
pow(T1 base, T2 e, T3 m=MOD)
{
    base = mod(base, m);
    T1 result(1); // Assumes 1 is the identity element

    while (e > 0) {
        if (e & 1) result = (result * base) % m;
        e /= 2;
        if (e == 0) break;
        base = (base * base) % m;
    }
    return result;
}

// Specialization for ints, because they are special
template <typename T2=ll, typename T3=ll>
ll pow(int base, T2 e, T3 m=MOD) {
    return pow<ll, T2, T3>(ll(base), e, m);
}

template <typename T1=ll, typename T2=ll>
T2 get_digit(T1 n, T2 b, ll i) {
    if (b == 2) {
        return ((1LL << i) & n) > 0;
    }
    else {
        return (n / nt::pow(b, i, -1)) % b;
    }
}

template <typename T1=ll>
int get_bit(T1 n, ll i) {
    return ((1LL << i) & n) > 0;
}

template <typename T=ll>
T inv(T x, T y)
{
    T p = y;

    T ax = 1;
    T ay = 0;
    while (x > 0) {
        T q = y / x;
        tie(ax, ay) = make_tuple(ay - q * ax, ax);
        tie(x, y) = make_tuple(y % x, x);
    }

    return mod(ay, p);
}

template <typename T=ll>
T mdiv(T x, T y, T m = MOD)
{
    if (m <= 0) {
        return x / y;
    }
    x = mod(x, m);
    y = mod(y, m);
    return mod(x * inv(y, m), m);
}

template <typename T=ll, typename S=ll>
ll v_p(T x, S p)
{
    ll res = 0;
    while (x % p == 0) {
        ++res;
        x /= p;
    }
    return res;
}

template <typename T, typename S>
T factorial(T x, S m = MOD)
{
    ll p = 1;
    FOR(i, 1, x)
    {
        p *= i;
        p = mod(p, m);
    }
    return p;
}

bool is_pow_of_2(ll n)
{
    return (n > 0) && ((n & (n - 1)) == 0);
}

// Computes the largest non-negative integer
// e such that b^e <= x
ll floor_log(ll x, ll b) {
    assert(b > 1);
    ll ans = 0;
    while (x >= b) {
        ans++; x /= b;
    }
    return ans;
}

// Computes the first 2^i st 2^i >= x / y,
// x and y must be positive
ll ratio_log2(ll x, ll y) {
    // 2^(-j) >= x / y
    // y >= 2^j * x
    if (x > y) {
        return first_st(i, cmul(1LL << i, y) >= x, 0, 31);
    }
    else {
        return -last_st(j, cmul((1LL << j), x) <= y, 31, 0);
    }
};

ll phi(ll n)
{
    ll result = n;
    if (!sieve_done) {
        throw out_of_range("Sieve not done, please run do_sieve");
    }

    for (ll prime : primes) {
        if (prime * prime > n)
            break;
        if (n % prime == 0) {
            while (n % prime == 0) {
                n /= prime;
            }
            result -= result / prime;
        }
    }

    if (n > 1) {
        result -= result / n;
    }

    return result;
}

// Returns all possible values of
// floor(n / k) from k = 1 to n.
// There are 2*sqrt(n) such values
vl floor_fractions(ll n) {
    vl ret;
    for (ll k = 1; k * k <= n; k++) {
        ret.pb(n / k);
        if (k != n / k) ret.pb(k);
    }
    sort(ALL(ret));
    return ret;
}

// Returns all possible values of
// ceil(n / k) from k = 1 to n.
// There are 2*sqrt(n) such values
vl ceil_fractions(ll n) {
    vl ret;
    for (ll k = 1; k * k <= n; k++) {
        ret.pb(ceildiv(n, k));
        if (k != ceildiv(n, k)) ret.pb(k);
    }
    sort(ALL(ret));
    return ret;
}

vl get_divisors(ll n) {
    vl divisors;
    for (ll d = 1; d * d <= n; d++) {
        if (n % d == 0) {
            divisors.pb(d);
            if (d * d != n)
                divisors.pb(n / d);
        }
    }
    sort(ALL(divisors));
    return divisors;
}

ll num_divisors(ll n)
{
    ll divisors = 1;

    for (ll prime : primes) {
        if (prime * prime > n)
            break;

        ll count = 0;
        while (n % prime == 0) {
            n /= prime;
            count++;
        }

        divisors *= (count + 1);
    }

    if (n > 1) {
        divisors *= 2;
    }

    return divisors;
}

ll sum_divisors(ll n)
{
    ll sum = 1;

    for (ll prime : primes) {
        if (prime * prime > n)
            break;

        if (n % prime == 0) {
            ll factorSum = 1;
            ll power = 1;
            while (n % prime == 0) {
                n /= prime;
                power *= prime;
                factorSum += power;
            }
            sum *= factorSum;
        }
    }

    if (n > 1) {
        sum *= (n + 1);
    }

    return sum;
}

umapll primeFactorization(ll n)
{
    umapll factors;

    for (ll prime : primes) {
        if (prime * prime > n)
            break;

        ll exponent = 0;
        while (n % prime == 0) {
            n /= prime;
            exponent++;
        }

        if (exponent > 0) {
            factors[prime] = exponent;
        }
    }

    if (n > 1) {
        factors[n] = 1;
    }

    return factors;
}
}

namespace combo {
using namespace nt;
vl factorial;
vl ifactorial; // Stores 1 / factorial
bool factorial_computed = false;
void precompute_fac(ll n, ll m = MOD)
{
    factorial.resize(n + 1);
    ifactorial.resize(n + 1);
    factorial[0] = 1;
    FOR(i, 1, n)
    {
        factorial[i] = mod(factorial[i - 1] * i, m);
    }
    // Stealing idea from ecnerwala
    ifactorial[n] = mdiv(ll(1), factorial[n], m);

    DOR(i, n - 1, 0) {
        ifactorial[i] = mod(ifactorial[i + 1] * (i + 1), m);
    }

    factorial_computed = true;
}

ll choose(ll n, ll k, ll m = MOD)
{
    if (k > n)
        return 0;
    if (k < 0) return 0;
    return mod(mod(factorial[n] * ifactorial[k], m) * ifactorial[n - k], m);
}
} // namespace combo

