#include <common.h>

const ll MAX_PRIME = 2000;
vl primes;
vl isnotprime(MAX_PRIME + 1);

void do_sieve() {
    rep(d, 2, MAX_PRIME) {
        if (!isnotprime[d]) {
            primes.push_back(d);

            int x = 2 * d;
            while (x <= MAX_PRIME) {
                isnotprime[x] = true;
                x += d;
            }
        }
    }
}

int main() {
    do_sieve();
    print(primes);
}