/**
 * Author: Yuhao Yao
 * Source: Adapted from tourist code.
 * Date: 22-10-25
 * Description: Solves a general linear maximization problem: maximize $c^\top x$ subject to $Ax \le b$, $x \ge 0$. Returns \{$res$, $x$\}:
 *  $res = 0$ if the program is infeasible; $res = 1$ if there exists an optimal solution; $res = 2$ if the program is unbounded. 
 *  $x$ is valid only when $res = 1$.
 *  $T$ can be \textbf{double} or \textbf{long double}.
 * Time: O(NM * \#pivots), where $N$ is the number of constraints and $M$ is the number of variables.
 * Status: tested on https://acm.hdu.edu.cn/showproblem.php?pid=6248.
 */
template<class T>
pair<int, vector<T>> Simplex(const vector<vector<T>> &A, const vector<T> &b, const vector<T> &c) {
	const T eps = 1e-8;
	assert(sz(A) > 0 && sz(A[0]) > 0);
	int n = sz(A);
	int m = sz(A[0]);
	vector<vector<T>> a(n + 1, vector<T>(m + 1));
	rep(i, 0, n - 1) rep(j, 0, m - 1) a[i + 1][j + 1] = A[i][j];
	rep(i, 0, n - 1) a[i + 1][0] = b[i];
	rep(j, 0, m - 1) a[0][j + 1] = c[j];
	vi left(n + 1), up(m + 1);
	iota(all(left), m);
	iota(all(up), 0);
	auto pivot = [&](int x, int y) {
		swap(left[x], up[y]);
		T k = a[x][y];
		a[x][y] = 1;
		vi pos;
		rep(j, 0, m) {
			a[x][j] /= k;
			if (fabs(a[x][j]) > eps) pos.push_back(j);
		}
		rep(i, 0, n) {
			if (fabs(a[i][y]) < eps || i == x) continue;
			k = a[i][y];
			a[i][y] = 0;
			for (int j : pos) a[i][j] -= k * a[x][j];
		}
	};
	while (1) {
		int x = -1;
		rep(i, 1, n) if (a[i][0] < -eps && (x == -1 || a[i][0] < a[x][0])) {
			x = i;
		}
		if (x == -1) break;
		int y = -1;
		rep(j, 1, m) if (a[x][j] < -eps && (y == -1 || a[x][j] < a[x][y])) {
			y = j;
		}
		if (y == -1) return {0, vector<T>{}}; // infeasible
		pivot(x, y);
	}
	while (1) {
		int y = -1;
		rep(j, 1, m) if (a[0][j] > eps && (y == -1 || a[0][j] > a[0][y])) {
			y = j;	
		}
		if (y == -1) break;
		int x = -1;
		rep(i, 1, n) if (a[i][y] > eps && (x == -1 || a[i][0] / a[i][y] < a[x][0] / a[x][y])) {
			x = i;
		}
		if (x == -1) return {2, vector<T>{}}; // unbounded
		pivot(x, y);
	}
	vector<T> ans(m);
	rep(i, 1, n) {
		if (1 <= left[i] && left[i] <= m) {
			ans[left[i] - 1] = a[i][0];
		}
	}
	return {1, ans};
}
