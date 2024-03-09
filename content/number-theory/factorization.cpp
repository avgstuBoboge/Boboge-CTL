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

    inline i64 mul(i64 a, i64 b, i64 c) { /// start-hash
        return (i128) a * b % c;
    }

    i64 mPow(i64 a, i64 k, i64 mod) {
        i64 res = 1;
        for (; k; k >>= 1, a = mul(a, a, mod)) if (k & 1) res = mul(res, a, mod);
        return res;
    }

    bool miller(i64 n) {
        auto test = [&](i64 n, int a) {
            if (n == a) return true;
            if (n % 2 == 0) return false;
            i64 d = (n - 1) >> ctz(n - 1);
            i64 r = mPow(a, d, n);
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

    mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
    i64 myrand(i64 a, i64 b) { return uniform_int_distribution<i64>(a, b)(rng); }

    i64 pollard(i64 n) { // return some nontrivial factor of n.
        if (miller(n)) return n;
        if (n % 2 == 0) return 2;
        i64 st = 0;
        auto f = [&](i64 x) { return (__int128_t(x) * x + st) % n; };
        while (true) {
            st++;
            i64 x = st, y = f(x);
            while (true) {
                i64 p = gcd((y - x + n), n);
                if (p == 0 || p == n) break;
                if (p != 1) return p;
                x = f(x);
                y = f(f(y));
            }
        }
    }

    vector<i64> factorize(i64 n) {
        vector<i64> res;
        auto dfs = [&](auto &dfs, i64 x) {
            if (x == 1) return;
            if (miller(x)) res.push_back(x);
            else {
                i64 d = pollard(x);
                dfs(dfs, d);
                dfs(dfs, x / d);
            }
        };
        dfs(dfs, n);
		sort(res.begin(), res.end());
        return res;
    } /// end-hash
}