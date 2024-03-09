/**
 * Author: Boboge
 * Date: 23-02-11
 * Description: lagrange interpolation, we know some $x$ and $f(x)$ for a polynomial(at least $n$ pairs), we can know for some $f(k)$.
 * Time: O(N ^ 2 \log N) for normal, O(N \log N) for special one.
 * Status: tested on https://www.luogu.com.cn/problem/P4781.
 */
Z lagrange(int n, int k, vector<Z> &x, vector<Z> &y) {
    Z ret = 0;
    for (int i = 0; i < n; ++i) {
        Z s1 = y[i];
        Z s2 = 1;
        for (int j = 0; j < n; ++j) {
            if (i == j) continue;
            s1 *= k - x[j];
            s2 *= x[i] - x[j];
        }
        ret += s1 / s2;
    }
    return ret;
}

//$x_i = i$, we have $y_0 ... y_n$
Z lagrange(int n, int m, vector<Z> &y) {
    assert(y.size() > n);
    if (m <= n) return y[m];
    Z ret = 0;
    Z all = 1;
    vector<Z> fac(n + 1);
    for (int i = 0; i <= n; ++i) {
        fac[i] = (i == 0 ? 1 : fac[i - 1] * i);
        all *= m - i;
    }
    for (int i = 0; i <= n; ++i) {
        Z fz = all / (m - i);
        Z fm = fac[i] * fac[n - i] * ((n - i) % 2 == 0 ? 1 : -1);
        ret += y[i] * fz / fm;
    }
    return ret;
}