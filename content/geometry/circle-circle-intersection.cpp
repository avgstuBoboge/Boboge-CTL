/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Compute the intersection points of two circles. For two tangent circles, the tangent point is returned twice in the vector.
 *  \textbf{Needed function(s): rotate}.
 * Status: (double) tested on https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 */
template<class T, class P = Point<T>>
vector<P> capCircleCircle(P o1, T r1, P o2, T r2) {
	if (P::cmp((o1 - o2).len(), r1 + r2) > 0) return {};
	if (P::cmp(max(r1, r2), min(r1, r2) + (o1 - o2).len()) > 0) return {};
	T val = (r1 * r1 + (o2 - o1).len2() - r2 * r2) / (2 * r1 * (o2 - o1).len());
	T theta = acos(max(min(val, T{1}), T{-1}));
	P u = (o2 - o1).unit() * r1;
	P p1 = o1 + u.rotate(-theta);
	P p2 = o1 + u.rotate(theta);
	return {p1, p2};
}
