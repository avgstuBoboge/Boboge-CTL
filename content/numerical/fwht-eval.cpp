/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Let $b = fwt(a)$. One can calculate $b_{id}$ for some index $id$ in $O(N)$ time. Length of $a$ should be a power of $2$.
 * Time: O(N), where $N$ is the length of $a$.
 * Status: tested.
 */
template<class T>
T fwt_eval(const vector<T> &a, int id) {
	int n = sz(a);
	T res = 0;
	rep(i, 0, n - 1) {
		if (__builtin_popcount(i & id) & 1) res -= a[i];
		else res += a[i];
	}
	return res;
}
