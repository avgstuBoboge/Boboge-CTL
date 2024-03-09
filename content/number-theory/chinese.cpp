/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Chinese Remainder Theorem for solveing equations $x \equiv a_i (mod~ m_i)$ for $i = 0, 1, ..., n - 1$ such that all $m_i$-s are pairwise-coprime. Returns $a$ such $x = a + k\cdot (\prod_{i = 0}^{n - 1} m_i)),\, k \in \mathbb{Z}$ are solutions.
 *   \textbf{Note that} you need to choose type $T$ to fit $(\prod_{i} m_i) \cdot (\max_{i} m_i)$. 
 * Time: O(n \log (\prod_{i = 0}^{n - 1} m_i)).
 * Status: tested on https://codeforces.com/gym/102056/problem/C.
*/
template<class T>
T CRT(const vector<T> &as, const vector<T> &ms) {
    T M = 1, res = 0;
    for (auto x: ms) M *= x;
    for (int i = 0; i < as.size(); ++i) {
        T m = ms[i], Mi = M / m;
        auto [x, y] = exgcd(Mi, m);
        res = (res + as[i] % m * Mi * x) % M;
    }
    return (res + M) % M;
}
