/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Calculate the area of union of Simple c.c.w Polygons $polys$. Points of each polygon should be distinct.
 *  \textbf{Needed function(s): dis\_to\_line, project\_len}.
 * Time: O(n^2 \log n), where $n$ is the total number of points in all Polygons.
 * Status: tested on https://codeforces.com/gym/101673/problem/A.
 */
template<class P, class T = typename P::type>
T PolyUnionArea(const vector<vector<P>> &polys) {
	T ans = 0;
	rep(ind, 0, sz(polys) - 1) {
		auto &poly = polys[ind];
		rep(i, 0, sz(poly) - 1) {
			P a = poly[i];
			P b = poly[(i + 1) % sz(poly)];
			vector<pair<T, int>> vec{{0, 1}, {1, -1}};
			rep(ind2, 0, sz(polys) - 1) {
				if (ind2 == ind) continue;
				auto &poly2 = polys[ind2];
				rep(j, 0, sz(poly2) - 1) {
					P c = poly2[j];
					P d = poly2[(j + 1) % sz(poly2)];
					int sgn1 = P::sgn(c.dis_to_line(a, b));
					int sgn2 = P::sgn(d.dis_to_line(a, b));
					if (sgn1 == 0 && sgn2 == 0) {
						if (P::sgn((d - c).cross(b - a)) < 0 || i < j) {
							auto l = c.project_len(a, b) / (b - a).len();
							auto r = d.project_len(a, b) / (b - a).len();
							if (l > r) swap(l, r);
							vec.emplace_back(l, -1);
							vec.emplace_back(r, 1);
						}
					} else if ((sgn1 < 0) ^ (sgn2 < 0)) {
						vec.emplace_back((c - a).cross(d - a) / (b - a).cross(d - c), sgn1 < 0 ? -1 : 1);
					}
				}
			}
			sort(all(vec));
			int cnt = 0;
			T last = 0;
			for (auto [d, c]: vec) {
				chmax(d, T{0});
				chmin(d, T{1});
				if (cnt > 0) ans += a.cross(b) / 2.0 * (d - last);
				cnt += c;
				last = d;
			}
		}
	}
	return ans;
}
