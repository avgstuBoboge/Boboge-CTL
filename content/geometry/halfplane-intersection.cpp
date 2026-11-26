/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the intersection of Half Planes, which is a Convex hull. A Half Plane is represented by the left hind side of a directed line $ab$ (i.e. counter-clockwise).
 *  Please make sure the intersection of Half Planes in $ls$ is bounded.
 *  Also make sure that there is no HalfPlane with direction $dir() = (0, 0)$.
 *  If the intersection is empty, then the returned vector has a size at most 2.
 *  Otherwise a Convex hull is returned, which has no consectuive collinear points.
 *  Only works for \textbf{double} and \textbf{long double}.
 *  \textbf{Needed function(s): argcmp, dis\_to\_line}.
 * Status: tested on https://official.contest.yandex.com/opencupXXII/contest/38278/problems/K/, https://www.luogu.com.cn/problem/P6505, https://qoj.ac/contest/782/problem/2162, https://qoj.ac/contest/852/problem/2875.
 */
template<class P> /// start-hash
struct HalfPlane {
	P a, b; // make sure a != b.
	P dir() const { return b - a; }
	bool include(P p) const { return p.dis_to_line(a, b) < -P::eps; }
	bool operator <(const HalfPlane &rhs) const { 
		return P::argcmp(dir(), rhs.dir()) < 0;
	}
	pair<bool, P> capLL(const HalfPlane &rhs) const {
		auto s0 = (a - rhs.a).cross(rhs.dir());
		auto s1 = (a - b).cross(rhs.dir());
		if (P::sgn(s1) == 0) return {false, P{}};
		return {true, a + (b - a) * s0 / s1};
	}
}; /// end-hash
template<class P, class HP = HalfPlane<P>> /// start-hash
vector<P> HPI(vector<HalfPlane<P>> hps) {
	// please make sure hps is closed.  
	auto Samedir = [](HP &r, HP &s) { return (r < s || s < r) == 0; };
	sort(all(hps), [&](HP &r, HP &s) { return Samedir(r, s) ? s.include(r.a) : r < s; });
	// assuming hps is closed then the intersect function should be fine.
	auto check = [](HP &w, HP &r, HP &s) {
		auto [res, p] = r.capLL(s);
		if (res == 0) return false; // if r and s are parallel then it implies the intersection is empty.
		return w.include(p);
	};
	deque<HP> q;
	rep(i, 0, sz(hps) - 1) {
		if (i && Samedir(hps[i], hps[i - 1])) continue;
		while (sz(q) > 1 && !check(hps[i], q.end()[-2], q.end()[-1])) q.pop_back();
		while (sz(q) > 1 && !check(hps[i], q[0], q[1])) q.pop_front();
		q.push_back(hps[i]);
	}
	while (sz(q) > 2 && !check(q[0], q.end()[-2], q.end()[-1])) q.pop_back();
	while (sz(q) > 2 && !check(q.back(), q[0], q[1])) q.pop_front();
	vector<P> res;
	rep(i, 0, sz(q) - 1) res.push_back(q[i].capLL(q[(i + 1) % sz(q)]).second);
	return res;
} /// end-hash
