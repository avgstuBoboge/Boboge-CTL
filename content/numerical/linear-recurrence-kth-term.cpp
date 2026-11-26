/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Suppose $a_i = \sum_{j = 1} ^ {d} c_j * a_{i - j}$, then just let $A = \{a_0, ..., a_{d - 1}\}$ and $C = \{c_1, ..., c_d\}$.\\
 *  Here is how it works. Let $Q(x)$ be the characteristic polynomial of our recurrence, and $F(x) = \sum_{i = 0}^{\infty} a_i x^i$ be the generating formal power series of our sequence. Then it can be seen that all nonzero terms of $F(x) Q(x)$ are of at most $(n - 1)$-st power. This means that $F(x) = P(x) / Q(x)$ for some polynomial $P(x)$. Moreover, we know what $P(x)$ is: it is basically the first $n$ terms of $F(x) Q(x)$, that is, can be found in one multiplication of $a_0 + \ldots + a_{n - 1} x^{n - 1}$ and $Q(x)$, and then trimming to the proper degree.
 * Time: O(d \log^2 d).
 * Status: tested on https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence.
 */
#include "polynomial.cpp"
template<class T>
T fps_coeff(Poly<T> P, Poly<T> Q, ll k) {
	while (k >= sz(Q)) {
		auto nQ(Q);
		rep(i, 0, sz(nQ) - 1) if (i & 1) nQ[i] = 0 - nQ[i];
		auto PQ = P * nQ;
		auto Q2 = Q * nQ;
		Poly<T> R, S;
		rep(i, 0, sz(PQ) - 1) if ((k + i) % 2 == 0) R.push_back(PQ[i]);
		rep(i, 0, sz(Q2) - 1) if (i % 2 == 0) S.push_back(Q2[i]);
		swap(P, R);
		swap(Q, S);
		k >>= 1;
	}
	return (P * Q.inv())[k];
}
template<class T>
T linear_rec_kth(const Poly<T> &A, const Poly<T> &C, ll k) {
	Poly<T> Q{1}; // Q is characteristic polynomial.
	for (auto x: C) Q.push_back(0 - x);
	auto P = A * Q;
	P.resize(sz(Q) - 1);
	return fps_coeff(P, Q, k);
}
