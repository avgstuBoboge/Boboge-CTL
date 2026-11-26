/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: check if Segment $ab$ is inside the given simple (not necessarily convex) Polygon $poly$, (i.e. no part of the segment is outside the polygon).
 *  Return 0 if the segment has part outside the polygon, otherwise 1. 
 *  $poly$ should be c.c.w and non-self-intersecting. Consecutive collinear points in $poly$ should be fine.
 *  If $a = b$, then we need the function \textbf{checkinPoly}.
 *  \textbf{Needed function(s): dis\_to\_line}.
 * Time: O(|poly| \log |poly|).
 * Status: (long long) tested on https://official.contest.yandex.com/mw2021spring/contest/26875/problems/M. Not sure how strong the tests are.
 */
#include "check-in-poly.cpp"
template<class P>
bool checkSeginPoly(P a, P b, const vector<P> &poly) {
	using T = typename P::type;
	if (a == b) return checkinPoly(a, poly) != 0;
	vector<pair<T, int>> res;
	int cnt = -1;
	rep(i, 0, sz(poly) - 1) {
		P p = poly[i];
		P q = poly[(i + 1) % sz(poly)];
		int sgn1 = P::sgn(p.dis_to_line(a, b));
		int sgn2 = P::sgn(q.dis_to_line(a, b));
		if ((sgn2 - sgn1) * P::sgn(a.dis_to_line(p, q)) > 0) {
			int c = sgn2 - sgn1;
			cnt -= c;
			if ((sgn2 - sgn1) * P::sgn(b.dis_to_line(p, q)) < 0) {
				if (sgn1 * sgn2 == -1) return 0; // properly intersect!
				if (sgn1 == 0) res.emplace_back((p - a).len2(), c);
				if (sgn2 == 0) res.emplace_back((q - a).len2(), c);
			}
		}
	}
	if (cnt == -1) return 0;
	sort(all(res));
	for (auto [_, c]: res) {
		cnt += c;
		if (cnt == -1) return 0;
	}
	return 1;
}
