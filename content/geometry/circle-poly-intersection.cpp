/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the intersection area of a Circle and a Polygon.
 *  Only works for double or long double.
 * Status: (double) tested on https://official.contest.yandex.com/opencupXXII/contest/38278/problems/K/.
 */
template<class T, class P = Point<T>>
T capCirclePoly(P o, T r, const vector<P> &poly) {
	auto tri = [&](P p, P q) {
		#define arg(p, q) atan2(p.cross(q), p.dot(q))
		T r2 = r * r;
		P d = q - p;
		if (p == q) return T{};
		T a = d.dot(p) / d.len2(), b = (p.len2() - r2) / d.len2();
		T det = a * a - b;
		if (P::sgn(det) <= 0) return arg(p, q) * r2 / 2;
		T s = max(T{0}, -a - sqrt(det)), t = min(T{1}, -a + sqrt(det));
		if (t < 0 || 1 < s) return arg(p, q) * r2 / 2;
		P u = p + d * s, v = p + d * t;
		return (p == u ? 0 : arg(p, u) * r2 / 2) + u.cross(v) / 2 + (v == q ? 0 : arg(v, q) * r2 / 2);
		#undef arg
	};
	T sum = 0;
	rep(i, 0, sz(poly) - 1) sum += tri(poly[i] - o, poly[(i + 1) % sz(poly)] - o);
	return sum;
}
