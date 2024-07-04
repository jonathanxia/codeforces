/**
 * Source: kactl
 * Description: Various self-explanatory methods for string hashing.
 * Use on Codeforces, which lacks 64-bit support and where solutions can be hacked.
 * Status: stress-tested
 *
 * Fixed for own usage. Note hashInterval is now inclusive range
 *
 * Usage: https://codeforces.com/contest/1943/submission/251851687
 *
 *
 * // In the main() function
 * kactl::hash_init();
 *
 * s = "abcd";
 * HashInterval h1(s);
 * h1.hashInterval(3, 5) == h1.hashInterval(5, 7)
 */
#pragma once
#include <lib/common.h>
#include <sys/time.h>

namespace kactl {

typedef uint64_t ull;
static int C; // initialized below
static bool initialized = false; // prevent user error

// Arithmetic mod two primes and 2^32 simultaneously.
// "typedef uint64_t H;" instead if Thue-Morse does not apply.
template<int M, class B>
struct A {
	int x; B b; A(int x_=0) : x(x_), b(x_) {}
	A(int x_, B b_) : x(x_), b(b_) {}
	A operator+(A o){int y = x+o.x; return{y - (y>=M)*M, b+o.b};}
	A operator-(A o){int y = x-o.x; return{y + (y< 0)*M, b-o.b};}
	A operator*(A o) { return {(int)(1LL*x*o.x % M), b*o.b}; }
	explicit operator ull() const { return x ^ ull(b) << 21; }
	bool operator==(A o) const { return ull(*this) == ull(o); }
	bool operator<(A o) const { return (ull)*this < (ull)o; }
};
typedef A<1000000007, A<1000000009, unsigned>> H;

struct HashInterval {
	vector<H> ha, pw;
	HashInterval(string& str) : ha(len(str)+1), pw(ha) {
        assert(initialized);
		pw[0] = 1;
		rep(i,0,len(str))
			ha[i+1] = ha[i] * C + str[i],
			pw[i+1] = pw[i] * C;
	}
	H hashInterval(int a, int b) { // hash [a, b]
        b++;
		return ha[b] - ha[a] * pw[b - a];
	}
};

vector<H> getHashes(string& str, int length) {
    assert(initialized);
	if (len(str) < length) return {};
	H h = 0, pw = 1;
	rep(i,0,length)
		h = h * C + str[i], pw = pw * C;
	vector<H> ret = {h};
	rep(i,length,len(str)) {
		ret.push_back(h = h * C + str[i] - pw * str[i-length]);
	}
	return ret;
}

H hashString(string& s){
    assert(initialized);
    H h{}; for(char c:s) h=h*C+c;return h;
}


void hash_init() {
	timeval tp;
	gettimeofday(&tp, 0);
	C = (int)tp.tv_usec; // (less than modulo)
	assert((ull)(H(1)*2+1-3) == 0);
    initialized=true;
}

}