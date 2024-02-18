#pragma once
/**
 * Author: Ulf Lundstrom
 * Date: 2009-03-21
 * License: CC0
 * Source: tinyKACTL
 * Description: Returns twice the signed area of a polygon.
 *  Clockwise enumeration gives negative area. Watch out for overflow if using int as T!
 * Status: Stress-tested and tested on kattis:polygonarea
 */
#include <lib/common.h>

#include <lib/kactl/geometry/Point.h>

namespace kactl {
template<class T>
T polygonArea2(vector<Point<T>>& v) {
	T a = v.back().cross(v[0]);
	rep(i,0,len(v)-1) a += v[i].cross(v[i+1]);
	return a;
}
}