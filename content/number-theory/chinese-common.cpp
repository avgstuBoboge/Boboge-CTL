/**
 * Author: Boboge
 * Date: 23-02-08
 * Description: exCRT, solving non-coprime $m_i$, return {-1, -1} if no solution.
 * Any $a + k \times m$ can be a solution.
 * Change to python if it the CRT exceeds.
 * Time: O(n \log LCM).
 * Status: tested on https://www.luogu.com.cn/problem/P4777.
*/
template<class T>
pair<T, T> merge(T a1, T m1, T a2, T m2) {
    if (m1 == -1 || m2 == -1) return {-1, -1};
    auto [y1, y2] = exgcd(m1, m2);
    T g = m1 * y1 + m2 * y2;
    if ((a2 - a1) % g) return {-1, -1};
    y1 = (i128) y1 * ((a2 - a1) / g) % (m2 / g);
    if (y1 < 0) y1 += m2 / g;
    T M = m1 / g * m2;
    T A = m1 * y1 + a1;
    return {A, M};
}

template<class T>
pair<T, T> exCRT(const vector<T> &as, const vector<T> &ms) {
    T a = 0, m = 1;
    for (int i = 0; i < as.size(); ++i) {
        T a2 = as[i], m2 = ms[i];
        auto [x, y] = merge(a, m, a2, m2);
        a = x, m = y;
    }
    return {a, m};
}