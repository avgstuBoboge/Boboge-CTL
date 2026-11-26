/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the intersection (Segments) of a non-self-intersecting Polygon $poly$ and a Line $ab$.
 *  Line $ab$ should be non-degenerate.
 *  Returned Segments are not sorted in direction $ab$.
 *  Only works for double or long double.
 *  \textbf{Needed function(s): dis\_to\_line}.
 * Time: O(|poly| \log |poly|).
 * Status: (double) tested on https://codeforces.com/gym/101471/problem/A. Need more tests.
 */
template<class P>
vector<pair<P, P>> capPolyLine(const vector<P> &poly, P a, P b) {
	using T = typename P::type;
	vector<tuple<T, P, int>> vec;
	rep(i, 0, sz(poly) - 1) {
		P p = poly[i];
		P q = poly[(i + 1) % sz(poly)];
		int sgn1 = P::sgn(p.dis_to_line(a, b));
		int sgn2 = P::sgn(q.dis_to_line(a, b));
		if (sgn1 != sgn2) {
			auto s0 = (p - a).cross(b - a);
			auto s1 = (q - a).cross(b - a);
			T d = (p - b).cross(q - b) / (b - a).cross(q - p) * (b - a).len();
			vec.emplace_back(d, (q * s0 - p * s1) / (s0 - s1), sgn2 - sgn1);
		}
	}
	sort(all(vec));
	vector<pair<P, P>> res;
	P last{};
	int cnt = -1;
	for (auto [_, p, c]: vec) {
		if (cnt < 0) last = p;
		cnt += c;
		if (cnt < 0) res.emplace_back(last, p);
	}
	return res;
}
