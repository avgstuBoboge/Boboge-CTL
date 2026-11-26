/**
 * Author: Yuhao Yao
 * Date: 22-10-29
 * Description: Compute the tangent lines of a Point $q$ to c.c.w convex hull $p_0...p_{n - 1}$.
 *  $p_0, \cdots, p_{n - 1}$ should be distinct points. (It should be fine that $3$ of them are collinear.)
 *  $q$ should be strictly outside the convex hull.
 *  Returns a pair $(l, r)$ such that edges $p_l p_{l + 1}, \cdots, p_{r - 1} p_r$ can be strictly seen from Point $q$.
 *  \textbf{Needed function(s): dis\_to\_line}.
 * Time: $O(\log n)$.
 * Status: tested on https://ac.nowcoder.com/acm/contest/11261/J, https://codeforces.com/gym/101201/problem/E.
 */
template<class P>
pii ConvexHullTangent(const vector<P> &poly, P q) {
	int n = sz(poly);
	auto solve = [&](function<bool(int i, int j)> onright) {
		bool up = onright(0, 1);
		int l = 1, r = n;
		while (l < r) {
			int mid = (l + r) >> 1;
			if (onright(0, mid)) {
				if (up) l = mid + 1;
				else r = mid;
			} else {
				if (onright(mid, (mid + 1) % n)) r = mid;
				else l = mid + 1;
			}
		}
		return l % n;
	};
	int l = solve([&](int i, int j) { return q.dis_to_line(poly[i], poly[j]) > P::eps; });
	int r = solve([&](int i, int j) { return q.dis_to_line(poly[i], poly[j]) < -P::eps; });
	return {l, r};
}
