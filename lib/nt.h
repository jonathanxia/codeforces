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

ll sum_digits(ll n, ll b)
{
    int sum = 0;
    while (n > 0) {
        sum += n % b;
        n /= b;
    }
    return sum;
}

vl get_digits(ll n, ll b, ll pad = -1)
{
    vl ans;
    while (n > 0) {
        ans.push_back(n % b);
        n /= b;
    }
    while (len(ans) < pad) {
        ans.pb(0);
    }
    return ans;
}

ll digits_to_num(const vl& digs, ll b)
{
    ll s = 0;
    DOR(i, len(digs) - 1, 0)
    {
        s *= b;
        s += digs[i];
    }
    return s;
}

// Function to calculate (base^exponent) % modulus using repeated squaring
ll pow(ll base, ll exponent, ll modulus = MOD)
{
    base = mod(base, modulus);
    ll result = 1;

    while (exponent > 0) {
        // If the exponent is odd, multiply the result by base
        if (exponent & 1) {
            if (modulus > 0) {
                result = (result * base) % modulus;
            } else {
                result = cmul(result, base);
            }
        }
        exponent >>= 1;
        if (exponent == 0) {
            break;
        }

        // Square the base and reduce the exponent by half
        if (modulus > 0) {
            base = (base * base) % modulus;
        } else {
            base = cmul(base, base);
        }
    }

    return result;
}

ll get_digit(ll n, ll b, ll i) {
    if (b == 2) {
        return ((1LL << i) & n) > 0;
    }
    else {
        return (n / nt::pow(b, i, -1)) % b;
    }
}

ll inv(ll x, ll y)
{
    ll p = y;

    ll ax = 1;
    ll ay = 0;
    while (x > 0) {
        ll q = y / x;
        tie(ax, ay) = make_tuple(ay - q * ax, ax);
        tie(x, y) = make_tuple(y % x, x);
    }

    return mod(ay, p);
}

ll mdiv(ll x, ll y, ll m = MOD)
{
    if (m <= 0) {
        return x / y;
    }
    x = mod(x, m);
    y = mod(y, m);
    return mod(x * inv(y, m), m);
}

ll v_p(ll x, ll p)
{
    ll res = 0;
    while (x % p == 0) {
        ++res;
        x /= p;
    }
    return res;
}

ll factorial(ll x, ll m = MOD)
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
bool factorial_computed = false;
void precompute_fac(ll n, ll m = MOD)
{
    factorial.resize(n + 1);
    factorial[0] = 1;
    FOR(i, 1, n)
    {
        factorial[i] = mod(factorial[i - 1] * i, m);
    }
    factorial_computed = true;
}

ll choose(ll n, ll k, ll m = MOD)
{
    if (k > n)
        return 0;

    ll ans = mdiv(factorial[n], factorial[k], m);
    return mdiv(ans, factorial[n - k], m);
}
}