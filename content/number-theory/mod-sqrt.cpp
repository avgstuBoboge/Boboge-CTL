/**
 * Author: Yuhao Yao
 * Date: 22-10-26
 * Description: Tonelli-Shanks algorithm for modular square roots. Formally, it solves $x^2 \equiv a (mod~ p)$ for prime $p$ and return arbitrary solution if there exists.
 * It will have most 2 solution, a and mod - a (maybe same).
 *  Usually we use $modnum$ as template parameter.
 * Time: O(\log^2 p) worst case, often O(\log p).
 * Status: tested on https://www.luogu.com.cn/problem/P5491, https://judge.yosupo.jp/problem/sqrt_mod.
 */
pair<bool, Z> ModSqrt(Z a) {
    int p = mod; //make mod not const if you need to change
    if (p == 2) return {true, a};
    if (a.pow((p - 1) / 2) == p - 1) return {false, 0};
    if (p % 4 == 3) return {true, a.pow((p + 1) / 4)};
    Z b = 1;
    while (b.pow((p - 1) / 2) == 1) b += 1;
    int d = (p - 1) / 2, k = 0;
    while (d % 2 == 0) {
        d /= 2;
        k /= 2;
        if (a.pow(d) * b.pow(k) + 1 == 0) k += (p - 1) / 2;
    }
    return {true, a.pow((d + 1) / 2) * b.pow(k / 2)};
}