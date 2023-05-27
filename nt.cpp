#include <common.h>

// Number Theory
namespace nt {
    ll sum_digits(ll n, ll b) {
        int sum = 0;
        while (n > 0) {
            sum += n % b;
            n /= b;
        }
        return sum;
    }

    vl get_digits(ll n, ll b) {
        vl ans;
        while (n > 0) {
            ans.push_back(n % b);
            n /= b;
        }

        return ans;
    }

    ll digits_to_num(vl& digs, ll b) {
        ll s = 0;
        dep(i, digs.size() - 1, 0) {
            s *= b;
            s += digs[i];
        }
        return s;
    }

    ll mod(ll a, ll p) {
        return (a % p + p) % p;
    }

    // ll M = pow(10, 9) + 7;
    ll M = 998244353;
    ll mod(ll a) {
        return mod(a, M);
    }

    // Function to calculate (base^exponent) % modulus using repeated squaring
    ll mpow(ll base, ll exponent, ll modulus=M) {
        ll result = 1;

        while (exponent > 0) {
            // If the exponent is odd, multiply the result by base
            if (exponent & 1)
                result = (result * base) % modulus;

            // Square the base and reduce the exponent by half
            base = (base * base) % modulus;
            exponent >>= 1;
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

    ll gcd(ll a, ll b) {
        a = abs(a);
        b = abs(b);
        if (a > b) {
            ass(a, b, b, a);
        }
        while (a > 0) {
            ass(a, b, b % a, a);
        }
        return b;
    }

    ll mdiv(ll x, ll y) {
        x = mod(x);
        y = mod(y);
        return mod(x * inv(y, M), M);
    }

    ll v_p(ll x, ll p) {
        ll res = 0;
        while (x % p == 0) {
            ++res;
            x /= p;
        }
        return res;
    }

    bool is_pow_of_2(ll n) {
        return (n > 0) && ((n & (n - 1)) == 0);
    }
}