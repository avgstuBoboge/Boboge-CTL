/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-08
 * Description: Primality test and Fast Factorization. The $mul$ function supports $0 \le a, b < c < 7.268 \times 10^{18}$ and is a little bit faster than \_\_int128.
 * Time: O(x ^ {1 / 4}) for pollard-rho and same for factorizing $x$.
 * Status: tested on https://judge.yosupo.jp/problem/factorize, https://qoj.ac/contest/821/problem/2574.
 */
namespace Factorization {
    template<class T>
    constexpr int ctz(T x) { return sizeof(T) & 8 ? __builtin_ctzll(x) : __builtin_ctz(x); }

    template<class T>
    constexpr T gcd(T x, T y) {
        if (!x || !y) return x ^ y;
        int kx = ctz(x);
        x >>= kx;
        int ky = ctz(y);
        y >>= ky;
        for (;; y >>= ctz(y)) {
            if (x > y) swap(x, y);
            y -= x;
            if (!y) return x << min(kx, ky);
        }
    }

    inline ll mul(ll a, ll b, ll c) { /// start-hash
        return (i128) a * b % c;
    }

    ll mPow(ll a, ll k, ll mod) {
        ll res = 1;
        for (; k; k >>= 1, a = mul(a, a, mod)) if (k & 1) res = mul(res, a, mod);
        return res;
    }

    bool miller(ll n) {
        auto test = [&](ll n, int a) {
            if (n == a) return true;
            if (n % 2 == 0) return false;
            ll d = (n - 1) >> ctz(n - 1);
            ll r = mPow(a, d, n);
            while (d < n - 1 && r != 1 && r != n - 1) {
                d <<= 1;
                r = mul(r, r, n);
            }
            return r == n - 1 || d & 1;
        };

        if (n == 2) return 1;
        for (int p: {2, 3, 5, 7, 11, 13, 17, 23, 29}) if (test(n, p) == 0) return 0;
        return 1;
    } /// end-hash

    mt19937 rng(114514); /// start-hash
    ll myrand(ll a, ll b) { return uniform_int_distribution<ll>(a, b)(rng); }

    ll pollard(ll n) { // return some nontrivial factor of n.
        if (miller(n)) return n;
        if (n % 2 == 0) return 2;
        ll st = 0;
        auto f = [&](ll x) { return (__int128_t(x) * x + st) % n; };
        while (true) {
            st++;
            ll x = st, y = f(x);
            while (true) {
                ll p = gcd((y - x + n), n);
                if (p == 0 || p == n) break;
                if (p != 1) return p;
                x = f(x);
                y = f(f(y));
            }
        }
    }

    vector<ll> factorize(ll n) {
        vector<ll> res;
        auto dfs = [&](auto &dfs, ll x) {
            if (x == 1) return;
            if (miller(x)) res.push_back(x);
            else {
                ll d = pollard(x);
                dfs(dfs, d);
                dfs(dfs, x / d);
            }
        };
        dfs(dfs, n);
		sort(res.begin(), res.end());
        return res;
    } /// end-hash
}