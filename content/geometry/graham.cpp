/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Given a set of \textbf{distinct} points, compute the Convex Hull of them.
 *  By setting $nonStrict = 1$, we also have the points on the border of the Convex Hull.
 *  When using double / long double the exact shape of returned Convex Hull might not be trustful (especially for imprecise points), so you should only use it for calculating the area / perimeter?
 * Time: O(|poly| \log |poly|).
 * Status: tested. (long long, nonStrict = 0 & 1) tested on https://codeforces.com/gym/103470/problem/F.
 */
template<class P>
vector<P> Graham(vector<P> as, int nonStrict = 0) {
	int n = sz(as);
	if (n <= 1) return as;
	swap(as[0], *min_element(all(as)));
	P o = as[0];
	sort(as.begin() + 1, as.end(), [&](P a, P b) {
		auto res = P::sgn((b - o).cross(a - o));
		return res < 0 || (res == 0 && P::cmp((a - o).len2(), (b - o).len2()) < 0);
	});
	vector<P> res{as[0], as[1]};
	rep(i, 2, n - 1) {
		while (sz(res) > 1 && P::sgn((as[i] - res.back()).cross(res.back() - res.end()[-2])) >= nonStrict) res.pop_back();
		res.push_back(as[i]);
	}
	if (nonStrict && P::sgn((as[1] - o).cross(as[n - 1] - o)) != 0) {
		revrep(i, 1, n - 2) {
			if (P::sgn((as[i] - o).cross(as[n - 1] - o)) != 0) break;
			res.push_back(as[i]);
		}
	}
	return res;
}
