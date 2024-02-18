#pragma once
#include <lib/common.h>

namespace fft {
typedef complex<double> C;
void fft(vector<C>& a)
{
    ll n = len(a), L = 31 - __builtin_clz(n);
    static vector<complex<long double>> R(2, 1);
    static vector<C> rt(2, 1); // (^ 10% faster if double)
    for (static int k = 2; k < n; k *= 2) {
        R.resize(n);
        rt.resize(n);
        auto x = polar(1.0L, acos(-1.0L) / k);
        rep(i, k, 2 * k) rt[i] = R[i] = i & 1 ? R[i / 2] * x : R[i / 2];
    }
    vi rev(n);
    rep(i, 0, n) rev[i] = (rev[i / 2] | (i & 1) << L) / 2;
    rep(i, 0, n) if (i < rev[i]) swap(a[i], a[rev[i]]);
    for (int k = 1; k < n; k *= 2)
        for (int i = 0; i < n; i += 2 * k)
            rep(j, 0, k)
            {
                // C z = rt[j+k] * a[i+j+k]; // (25% faster if hand-rolled)  /// include-line
                auto x = (double*)&rt[j + k], y = (double*)&a[i + j + k]; /// exclude-line
                C z(x[0] * y[0] - x[1] * y[1], x[0] * y[1] + x[1] * y[0]); /// exclude-line
                a[i + j + k] = a[i + j] - z;
                a[i + j] += z;
            }
}
vld conv(const vld& a, const vld& b)
{
    if (a.empty() || b.empty())
        return {};
    vld res(len(a) + len(b) - 1);
    ll L = 32 - __builtin_clz(len(res)), n = 1 << L;
    vector<C> in(n), out(n);
    copy(ALL(a), in.begin());
    rep(i, 0, len(b)) in[i].imag(b[i]);
    fft(in);
    for (C& x : in)
        x *= x;
    rep(i, 0, n) out[i] = in[-i & (n - 1)] - conj(in[i]);
    fft(out);
    rep(i, 0, len(res)) res[i] = imag(out[i]) / (4 * n);
    return res;
}

template <ll M = MOD>
vl conv_mod(const vl& a, const vl& b)
{
    if (a.empty() || b.empty())
        return {};
    vl res(len(a) + len(b) - 1);
    ll B = 32 - __builtin_clz(len(res)), n = 1 << B, cut = ll(sqrt(M));
    vector<C> L(n), R(n), outs(n), outl(n);
    rep(i, 0, len(a)) L[i] = C((ll)a[i] / cut, (ll)a[i] % cut);
    rep(i, 0, len(b)) R[i] = C((ll)b[i] / cut, (ll)b[i] % cut);
    fft(L), fft(R);
    rep(i, 0, n)
    {
        ll j = -i & (n - 1);
        outl[j] = (L[i] + conj(L[j])) * R[i] / (2.0 * n);
        outs[j] = (L[i] - conj(L[j])) * R[i] / (2.0 * n) / 1i;
    }
    fft(outl), fft(outs);
    rep(i, 0, len(res))
    {
        ll av = ll(real(outl[i]) + .5), cv = ll(imag(outs[i]) + .5);
        ll bv = ll(imag(outl[i]) + .5) + ll(real(outs[i]) + .5);
        res[i] = ((av % M * cut + bv) % M * cut + cv) % M;
    }
    return res;
}
}