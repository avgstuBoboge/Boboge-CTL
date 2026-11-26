/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the area of Convex Hull of Union of Circles.
 * Usage: input $os$ and $rs$ should have same positive sizes.
 * Time: O(n^3), where $n$ is the number of cycles.
 * Status: tested on https://qoj.ac/contest/824/problem/2614, https://codeforces.com/gym/101673/problem/B (compute perimeter instead).
 */
#include "circle-circle-outer-tangentline.cpp"
#include "graham.cpp"
template<class T, class P = Point<T>>
T CirclesHullArea(const vector<P> &os, const vector<T> &rs) {
	vector<pair<P, T>> cs;
	revrep(i, 0, sz(os) - 1) {
		auto o1 = os[i];
		auto r1 = rs[i];
		int ok = 1;
		for (auto [o2, r2]: cs) if (o1 == o2 && r1 == r2) ok = 0;
		if (ok) cs.emplace_back(o1, r1);
	}
	vector<P> ps;
	rep(i, 0, sz(cs) - 1) {
		auto [o1, r1] = cs[i];
		rep(j, i + 1, sz(cs) - 1) {
			auto [o2, r2] = cs[j];
			auto tmp = CircleCirlceOuterTagentLine(o1, r1, o2, r2);
			for (auto [a, b]: tmp) {
				ps.push_back(a);
				ps.push_back(b);
			}
		}
	}
	vector<P> nps;
	for (auto p: ps) {
		int ok = 1;
		for (auto [o, r]: cs) if (P::cmp((p - o).len(), r) < 0) ok = 0;
		if (ok) nps.push_back(p);
	}
	swap(ps, nps);
	static const T pi = acos(-1.0);
	if (ps.empty()) {
		auto r = *max_element(all(rs));
		return pi * r * r;
	} else {
		auto poly = Graham(ps);
		int n = sz(poly);
		vi ids(n);
		rep(i, 0, n - 1) {
			auto p = poly[i];
			rep(ind, 0, sz(cs) - 1) {
				auto [o, r] = cs[ind];
				if (P::cmp((p - o).len(), r) == 0) ids[i] = ind;
			}
		}
		T ans = 0;
		rep(i, 0, n - 1) {
			if (ids[i] == ids[(i + 1) % n]) {
				int ind = ids[i];
				auto [o, r] = cs[ind];
				auto a = poly[i] - o;
				auto b = poly[(i + 1) % n] - o;
				auto theta = atan2(b.y, b.x) - atan2(a.y, a.x);
				if (P::sgn(theta) < 0) theta += pi * 2;
				ans += theta * r * r / 2;
				ans += (poly[i] - poly[0]).cross(poly[(i + 1) % n] - poly[0]) / 2;
				ans -= a.cross(b) / 2;
			} else ans += (poly[i] - poly[0]).cross(poly[(i + 1) % n] - poly[0]) / 2;
		}
		return ans;
	}
}
