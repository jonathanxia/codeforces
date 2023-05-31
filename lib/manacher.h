#include <lib/common.h>

array<vl, 2> manacher(const string& s) {
	int n = s.size();
	array<vl, 2> p = {vl(n+1), vl(n)};
	rep(z, 0, 1) {
        for (int i = 0, l = 0, r = 0; i < n; i++) {
            int t = r - i + !z;
            if (i < r)
                p[z][i] = min((ll) t, p[z][l + t]);
            int L = i - p[z][i], R = i + p[z][i] - !z;
            while (L >= 1 && R + 1 < n && s[L - 1] == s[R + 1])
                p[z][i]++, L--, R++;
            if (R > r)
                l = L, r = R;
        }
    }
	return p;
}

int main() {
    str s = "abbcdcb";

    auto stuff = manacher(s);

    print("even palindromes", stuff[0]);
    print("odd palindromes", stuff[1]);
    return 0;
}