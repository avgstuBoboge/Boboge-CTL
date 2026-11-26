/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Given a c.c.w convex hull $p_0...p_{n - 1}$ and a vector of lines $ls$, for each line check if it intersects the hull.
 *  $p_0, \cdots, p_{n - 1}$ should be distinct points. (It should be fine that $3$ of them are collinear.)
 *  Returns $0$ if the line does not intersect the hull; $1$ if it intersects the hull properly; $2$ if it passes through exactly a point or an edge of the hull.
 *  \textbf{Needed function(s): argcmp, dis\_to\_line}.
 * Time: $O(\log n)$.
 * Status: tested on https://www.acmicpc.net/problem/7057.
 */
template<class P>
vi capHullLine(vector<P> hull, const vector<pair<P, P>> &ls) {
	auto it = min_element(all(hull), [&](P a, P b) {
		return P::cmp(a.y, b.y) != 0 ? a.y > b.y : P::cmp(a.x, b.x) < 0;
	});
	rotate(hull.begin(), it, hull.end());
	int n = sz(hull);
	vector<P> vs(n);
	rep(i, 0, n - 1) vs[i] = hull[(i + 1) % n] - hull[i];
	vi res;
	for (auto [p, q]: ls) {
		auto dir = q - p;
		auto cmp = [](P a, P b) { return P::argcmp(a, b) < 0; };
		int l = (lower_bound(all(vs), dir, cmp) - vs.begin()) % n;
		int r = (lower_bound(all(vs), P{} - dir, cmp) - vs.begin()) % n;
		int s1 = P::sgn(hull[l].dis_to_line(p, q));
		int s2 = P::sgn(hull[r].dis_to_line(p, q));
		if (s1 == 0 || s2 == 0) res.push_back(2);
		else res.push_back(s1 != s2);
	}
	return res;
}
