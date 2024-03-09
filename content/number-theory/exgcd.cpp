/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-08
 * Description: Solve the integer equation $a x + b y = \gcd(a, b)$ for $a, b \ge 0$ and returns $x$ and $y$ such that $|x| \le b$ and  $|y| \le a$. \textbf{Note that} retured value $x$ and $y$ are not guaranteed to be positive!
 * Time: O(\log \max\{a, b\}).
 * Status: tested on https://ac.nowcoder.com/acm/contest/5667/J, https://ac.nowcoder.com/acm/contest/5668/F, https://codeforces.com/gym/101206/problem/F, https://codeforces.com/contest/772/problem/C.
 */
template<class T>
pair<T, T> exgcd(T a, T b) {
    if (b == 0) return {1, 0};
    auto [x, y] = exgcd(b, a % b);
    return {y, x - a / b * y};
}
