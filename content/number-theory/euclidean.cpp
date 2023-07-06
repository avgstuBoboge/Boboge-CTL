/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Compute $\sum_{i = 1}^n \lfloor \frac{a i + b}{c} \rfloor$ for integer numbers $a, b, c, n$.
 * Time: O(\log c).
 * Status: tested on https://ac.nowcoder.com/acm/contest/148/H, https://qoj.ac/problem/3004.
 */
template<class T>
T Euclidean(ll a, ll b, ll c, ll n) {
    T res = 0;
    if (a >= c || b >= c) {
        res += T{a / c} * n * (n + 1) / 2;
        res += T{b / c} * (n + 1);
        a %= c;
        b %= c;
    }
    if (a != 0) {
        ll m = ((i128) a * n + b) / c;
        res += T{m} * n - Euclidean<T>(c, c - b - 1, a, m - 1);
    }
    return res;
}