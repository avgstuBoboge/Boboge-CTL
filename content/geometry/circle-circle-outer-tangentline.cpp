/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the outer two tangent lines of two circles.
 *  \textbf{Needed function(s): rotate}.
 * Status: https://qoj.ac/contest/824/problem/2614.
 */
template<class T, class P = Point<T>>
vector<pair<P, P>> CircleCirlceOuterTagentLine(P o1, T r1, P o2, T r2) {
	if (P::cmp(r2, (o1 - o2).len() + r1) >= 0) return {};
	if (P::cmp(r1, (o1 - o2).len() + r2) >= 0) return {};
	T val = (r1 - r2) / (o1 - o2).len();
	T theta = acos(max(min(val, T{1}), T{-1}));
	vector<pair<P, P>> res;
	P v = (o2 - o1).unit();
	res.emplace_back(o1 + v.rotate(theta) * r1, o2 + v.rotate(theta) * r2);	
	res.emplace_back(o1 + v.rotate(-theta) * r1, o2 + v.rotate(-theta) * r2);	
	return res;
}
