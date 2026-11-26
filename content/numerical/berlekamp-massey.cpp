/**
 * Author: Yuhao Yao
 * Date: 22-10-30
 * Source: Adpated from https://github.com/anroysko/contestlib/blob/master/src/math/berlekamp_massey/code.cpp.
 * Description: Berlekamp Massey algorithm.
 * Status: tested on https://qoj.ac/contest/821/problem/2574.
*/
template<int mod>
class BerlekampMassey {
private:
	static ll mPow(ll a, ll k) {
		ll res = 1;
		for (; k; k >>= 1, a = a * a % mod) if (k & 1) res = res * a % mod;
		return res;
	}
	static void chadd(int &x, int y) { x += y; if (x >= mod) x -= mod; }
	static void chsub(int &x, int y) { x -= y; if (x < 0) x += mod; }
	static void polyMulMod(vi &a, const vi &b, const vi &c) {
		int n = sz(c) - 1;
		revrep(i, 0, n * 2 - 2) {
			int v = 0;
			rep(x, max(0, i + 1 - n), min(n - 1, i)) chadd(v, 1ll * a[x] * b[i - x] % mod);
			a[i] = v;
		}
		revrep(i, n, n * 2 - 2) revrep(j, 0, n) chsub(a[i - j], 1ll * c[j] * a[i] % mod);
	}
	vi nxt, rec, old, seq;
	int t;
	// Given a sequence seq[0], ..., seq[n - 1] \in [0, P), finds the minimum t and associated rec[0], ..., rec[t] \in [0, P) s.t.
	// 1. rec[0] = 1 (mod P)
	// 2. \sum_{j = 0}^{t} rec[j] seq[i - j] = 0 (mod P) for every i \in [t, n)
	// Time complexity: O(nt)
public:
	BerlekampMassey(const vi &s) : nxt(sz(s) + 1, 0), rec(sz(s) + 1, 0), old(sz(s) + 1, 0), seq(s), t(0) {
		int old_t = 0, old_i = -1, old_d = 1;
		rec[0] = 1, old[0] = 1;
		rep(i, 0, sz(seq) - 1) {
			int d = s[i];
			rep(j, 1, t) chadd(d, 1ll * rec[j] * seq[i - j] % mod);
			if (d == 0) continue;
			int mult = 1ll * d * mPow(old_d, mod - 2) % mod;
			rep(j, 0, t) nxt[j] = rec[j];
			rep(j, 0, old_t) chsub(nxt[j + i - old_i], 1ll * old[j] * mult % mod);
			if (t * 2 <= i) {
				old_i = i, old_d = d, old_t = t;
				t = i + 1 - t;
				swap(old, rec);
			}
			swap(rec, nxt);
		}
		rec.resize(t + 1, 0);
	}
	// Returns seq[k], assuming \sum_{j = 0}^{t} rec[j] seq[i - j] = 0 (mod P) holds for i >= n
	// Time complexity: O(t^2 log k)
	int kthTerm(ll k) {
		if (t == 1) return 1ll * seq[0] * mPow((mod - rec[1]) % mod, k) % mod;
		vi cur(t * 2 + 2, 0), mult(t * 2 + 2, 0);
		cur[0] = 1, mult[1] = 1;
		for (; k > 0; k >>= 1) {
			if (k & 1) polyMulMod(cur, mult, rec);
			polyMulMod(mult, mult, rec);
		}
		int res = 0;
		rep(i, 0, t) chadd(res, 1ll * cur[i] * seq[i] % mod);
		return res;
	}
	vi getRec() { return rec; }
};
