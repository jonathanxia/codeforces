#pragma once
/**
 * Author: Lukas Polacek
 * Date: 2009-09-28
 * License: CC0
 * Source: folklore
 * Description: Operators for modular arithmetic. You need to set {\tt mod} to
 * some number first and then you can use the structure.
 * Edit by Kevin Xia: The original constructor for Mod didn't apply % mod to xx.
 * This means that the invariant that x be between [0, mod) is violated.
 */
#include <lib/common.h>

#include <lib/kactl/number-theory/euclid.h>

namespace kactl {
const ll mod = 17; // change to something else
struct Mod {
	ll x;
	Mod(ll xx) : x(((xx % mod) + mod) % mod) {}
	Mod operator+(Mod b) { return Mod((x + b.x) % mod); }
	Mod operator-(Mod b) { return Mod((x - b.x + mod) % mod); }
	Mod operator*(Mod b) { return Mod((x * b.x) % mod); }
	Mod operator/(Mod b) { return *this * invert(b); }
	Mod invert(Mod a) {
		ll x, y, g = euclid(a.x, mod, x, y);
		assert(g == 1); return Mod((x + mod) % mod);
	}
	Mod operator^(ll e) {
		if (!e) return Mod(1);
		Mod r = *this ^ (e / 2); r = r * r;
		return e&1 ? *this * r : r;
	}
};
}