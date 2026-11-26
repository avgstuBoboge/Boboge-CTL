/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: check if point $a$ is inside / on / outside the given simple (not necessarily convex) Polygon $poly$.
 *  Return 0 if outside; 1 if inside; 2 if on the border. 
 *  $poly$ can be either clockwise or counter-clockwise and should not be self-intersecting. Consecutive collinear points in $poly$ should be fine \textbf{but all points should be distinct}.
 *  For c.c.w Polygon, $cnt = 2$ indicates strictly inside; for c.w Polygon, $cnt = -2$ indicates strictly inside.
 *  \textbf{Needed function(s): dis\_to\_line, project\_len, dis\_to\_seg, on\_seg}.
 * Time: O(|poly|).
 * Status: (long long) tested on https://open.kattis.com/problems/pointinpolygon;
 * 	(double tested on) https://acm.hdu.edu.cn/showproblem.php?pid=6419.
 */
template<class P>
int checkinPoly(P a, const vector<P> &poly) {
	int cnt = 0;
	rep(i, 0, sz(poly) - 1) {
		P p = poly[i];
		P q = poly[(i + 1) % sz(poly)];
		if (a.on_seg(p, q)) return 2;
		int sgn1 = P::cmp(a.y, p.y);
		int sgn2 = P::cmp(a.y, q.y);
		if ((sgn2 - sgn1) * P::sgn(a.dis_to_line(p, q)) > 0) {
			cnt -= sgn2 - sgn1;
		}
	}
	return cnt == 0 ? 0 : 1;
}
