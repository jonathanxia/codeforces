#pragma once
/**
 * Author: Noam527
 * Date: 2019-04-24
 * License: CC0
 * Source: folklore
 * Description:
 * Status: tested
 */
#include <lib/common.h>

namespace kactl {
ll modpow(ll b, ll e, ll m=MOD) {
	ll ans = 1;
	for (; e; b = b * b % m, e /= 2)
		if (e & 1) ans = ans * b % m;
	return ans;
}
}