/**
 * Author: Yuhao Yao
 * Date: 22-10-20
 * Description: 2D Sparse Table of 2D vector of size $N \times M$.
 * Time: O(N M \log N \log M) for construction, O(1) per query.
 * Status: tested on https://codeforces.com/gym/101206/problem/F.
 */
template<class T, class F = function<T(const T&, const T&)>>
class SparseTable2D {
	using vt = vector<T>;
	using vvt = vector<vt>;
	int n, m;
	vector<vector<vvt>> st;
	const F func;
public:
	SparseTable2D(const vvt &init, const F &f): n(sz(init)), func(f) {
		assert(n > 0);
		m = sz(init[0]);
		assert(m > 0);
		st.assign(__lg(n) + 1, vector<vvt>(__lg(m) + 1, vvt(n, vt(m))));
		st[0][0] = init;
		rep(j, 1, __lg(m)) rep(x, 0, n - 1) rep(y, 0, m - (1 << j)) {
			st[0][j][x][y] = func(st[0][j - 1][x][y], st[0][j - 1][x][y + (1 << (j - 1))]);
		}
		rep(i, 1, __lg(n)) rep(j, 0, __lg(m)) rep(x, 0, n - (1 << i)) rep(y, 0, m - (1 << j)) {
			st[i][j][x][y] = func(st[i - 1][j][x][y], st[i - 1][j][x + (1 << (i - 1))][y]);
		}
	}
	T ask(int x1, int y1, int x2, int y2) {
		assert(0 <= x1 && x1 <= x2 && x2 < n);
		assert(0 <= y1 && y1 <= y2 && y2 < m);
		int kx = __lg(x2 - x1 + 1);
		int ky = __lg(y2 - y1 + 1);
		int lx = 1 << kx;
		int ly = 1 << ky;
		T res = func(st[kx][ky][x1][y1], st[kx][ky][x1][y2 - ly + 1]);
		res = func(res, st[kx][ky][x2 - lx + 1][y1]);
		res = func(res, st[kx][ky][x2 - lx + 1][y2 - ly + 1]);
		return res;
	}
};