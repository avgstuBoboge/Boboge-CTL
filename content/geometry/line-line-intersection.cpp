/**
 * Author: Yuhao Yao
 * Date: 22-11-01
 * Description: Returns 1 and the intersection point if Line $ab$ and Line $cd$ do not degenerate and they are not parellel. Returns 0 (and an arbitrary point) otherwise.
 *  \textbf{Only} works for \textbf{double} or \textbf{long double}.
 * Status: (double) tested on https://ac.nowcoder.com/acm/contest/33188/G, https://acm.hdu.edu.cn/showproblem.php?pid=6419, https://codeforces.com/gym/256788/problem/C.
 */
template<class P>
pair<bool, P> capLineLine(P a, P b, P c, P d) {
	auto s0 = (a - c).cross(d - c);
	auto s1 = (a - b).cross(d - c);
	if (P::sgn(s1) == 0) return {false, P{}};
	return {true, a + (b - a) * s0 / s1};
}
