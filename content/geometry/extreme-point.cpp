/**
 * Author: Boboge
 * Date: 26-06-24
 * Description: Given a non-empty c.c.w. convex hull, find an index maximizing $f(p_i)$.
 *  $f$ should be a linear function on points, such as a cross product or dot product with a fixed vector.
 *  Values are compared using \texttt{P::cmp}; if the maximum is attained at multiple points, any one may be returned.
 * Time: $O(\log n)$.
 * Status: stress-tested.
 */
template<class P, class Func>
int extremePoint(const vector<P> &hull, Func f) {
	int n = sz(hull);
	assert(n > 0);
	if (n == 1) return 0;
	auto cmp = [&](int i, int j) {
		return P::cmp(f(hull[i]), f(hull[j]));
	};
	auto up = [&](int i) {
		return cmp((i + 1) % n, i) >= 0;
	};
	bool u0 = up(0);
	int l = 0, r = n;
	while (l + 1 < r) {
		int mid = midpoint(l, r);
		bool um = up(mid);
		if (um == u0) {
			if ((cmp(mid, 0) >= 0) == u0) l = mid;
			else r = mid;
		} else {
			if (um) l = mid;
			else r = mid;
		}
	}
	return r % n;
}
