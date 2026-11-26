/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: For convex function $f: \mathbb{R}^d \to \mathbb{R}$, we can approximately find the global minimum using ternary search on each coordinate recursively.
 *  $d$ is the dimension; $mn, mx$ record the minimum and maximum possible value of each coordinate (the region you do ternary search); $f$ is the convex function.
 *  $T$ can be \textbf{double} or \textbf{long double}.
 * Time: O(\log(1 / \epsilon) ^ {d} \cdot C), where $C$ is the time for evaluating the function $f$.
 * Status: tested on https://codeforces.com/gym/101981/problem/D.
 */
template<class T> T RecTS(int d, const vector<T> &mn, const vector<T> &mx, function<T(const vector<T>&)> f) {
	vector<T> xs(d);
	auto dfs = [&](auto &dfs, int dep) {
		if (dep == d) return f(xs);
		T l = mn[dep], r = mx[dep];
		rep(_, 1, 60) { // change here if time is tight.
			T m1 = (l * 2 + r) / 3;
			T m2 = (l + r * 2) / 3;
			xs[dep] = m1; T res1 = dfs(dfs, dep + 1);
			xs[dep] = m2; T res2 = dfs(dfs, dep + 1);
			if (res1 < res2) r = m2;
			else l = m1;
		}
		xs[dep] = (l + r) / 2;
		return dfs(dfs, dep + 1);
	};
	return dfs(dfs, 0);
}
