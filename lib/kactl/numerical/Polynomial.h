/**
 * Author: David Rydh, Per Austrin
 * Date: 2003-03-16
 * Description:
 */
#include <lib/common.h>

namespace kactl {
struct Poly {
	vector<double> a;
	double operator()(double x) const {
		double val = 0;
		for (int i = len(a); i--;) (val *= x) += a[i];
		return val;
	}
	void diff() {
		rep(i,1,len(a)) a[i-1] = i*a[i];
		a.pop_back();
	}
	void divroot(double x0) {
		double b = a.back(), c; a.back() = 0;
		for(int i=len(a)-1; i--;) c = a[i], a[i] = a[i+1]*x0+b, b=c;
		a.pop_back();
	}
};
}