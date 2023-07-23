#include <lib/common.h>

namespace nt {
    vl primes;
    vl isnotprime;
    bool sieve_done = false;

    void do_sieve(ll max_prime) {
        isnotprime.resize(max_prime + 1);
        rep(d, 2, max_prime) {
            if (!isnotprime[d]) {
                primes.push_back(d);

                int x = 2 * d;
                while (x <= max_prime) {
                    isnotprime[x] = true;
                    x += d;
                }
            }
        }
        sieve_done = true;
    }

    bool is_prime(ll n) {
        // Checks if n is prime
        if (n <= 1) {
            return false;
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

    ll sum_digits(ll n, ll b) {
        int sum = 0;
        while (n > 0) {
            sum += n % b;
            n /= b;
        }
        return sum;
    }

    vl get_digits(ll n, ll b, ll pad=-1) {
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

    ll digits_to_num(const vl& digs, ll b) {
        ll s = 0;
        dep(i, digs.size() - 1, 0) {
            s *= b;
            s += digs[i];
        }
        return s;
    }

    ll mod(ll a, ll p) {
        if (p > 0) {
            return (a % p + p) % p;
        }
        return a;
    }

    ll MOD = 998244353LL;
    // ll MOD = 1000000007;
    ll mod(ll a) {
        return mod(a, MOD);
    }

    // Function to calculate (base^exponent) % modulus using repeated squaring
    ll pow(ll base, ll exponent, ll modulus=MOD) {
        ll result = 1;

        while (exponent > 0) {
            // If the exponent is odd, multiply the result by base
            if (exponent & 1) {
                if (modulus > 0) {
                    result = (result * base) % modulus;
                }
                else {
                    result = result * base;
                }
            }
            exponent >>= 1;
            if (exponent == 0) {
                break;
            }

            // Square the base and reduce the exponent by half
            if (modulus > 0) {
                base = (base * base) % modulus;
            }
            else {
                base = base * base;
            }
        }

        return result;
    }

    ll inv(ll x, ll y) {
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

    ll mdiv(ll x, ll y, ll m=MOD) {
        if (m <= 0) {
            return x / y;
        }
        x = mod(x);
        y = mod(y);
        return mod(x * inv(y, m), m);
    }

    ll v_p(ll x, ll p) {
        ll res = 0;
        while (x % p == 0) {
            ++res;
            x /= p;
        }
        return res;
    }

    ll factorial(ll x) {
        ll p = 1;
        rep(i, 1, x) {
            p *= i;
            p = mod(p);
        }
        return p;
    }

    bool is_pow_of_2(ll n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }

    ll phi(ll n) {
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

    ll num_divisors(ll n) {
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

    ll sum_divisors(ll n) {
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

    umapll primeFactorization(ll n) {
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
    ll choose(ll n, ll k, ll m=-1) {
        ll p = 1;
        rep(i, 1, k) {
            p = p * (n - k + i) / i;
            if (m > 0) {
                p = nt::mod(p, m);
            }
        }
        return p;
    }

    vl precompute_choose(ll n1, ll n2, ll k, ll m=-1) {
        vl result(n2 - n1 + 1);
        ll idx = max(k - n1, 0LL);
        if (idx > n2 - n1) {
            return result;
        }
        if (n1 + idx == k) {
            result[idx] = 1;
        }
        else {
            result[idx] = choose(n1 + idx, k, m);
        }
        rep(i, idx + 1, n2 - n1) {
            result[i] = result[i - 1] * (n1 + i) / (n1 + i - k);
            if (m > 0) {
                result[i] %= m;
            }
        }
        return result;
    }

    vl precompute_choose2(ll n, ll k1, ll k2, ll m = -1) {
        vl result(k2 - k1 + 1);
        result[0] = choose(n, k1, m=m);
        rep(i, k1 + 1, k2) {
            if (m > 0) {
                result[i] = nt::mdiv(
                    result[i - 1] * (n - i + 1), i, m);
            }
            else {
                result[i] = result[i - 1] * (n - i + 1) / i;
            }
        }
        return result;
    }

    using namespace nt;
    vl precompute_catalan(ll n, ll m = MOD) {
        vl result(n + 1);
        result[0] = 1;
        rep(i, 1, n) {
            result[i] = nt::mod(result[i - 1] * 2 * i, m);
            result[i] = nt::mod(result[i] * (2 * i - 1), m);
            result[i] = nt::mdiv(result[i], i + 1, m);
            result[i] = nt::mdiv(result[i], i, m);
        }
        return result;
    }

    vl precompute_fac(ll n, ll m = MOD) {
        vl result(n + 1);
        result[0] = 1;
        rep(i, 1, n) {
            result[i] = mod(result[i - 1] * i, m);
        }
        return result;
    }
}