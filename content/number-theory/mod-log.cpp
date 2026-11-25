/**
 * Author: Boboge
 * Date: 23-02-08
 * Description: BSGS for discrete log. Formally, it solves $a ^ x \equiv b (\mod\, p)$ given integer $a, b$ and a prime number $p$. Returns an solution $x$ if there exists.
 *  Requires $a \ne 0 \pmod p$; zero bases are not supported. The modulus comes from $Z::getMod()$.
 * Time: O(\sqrt{p} \log p).
 * Status: tested on https://www.luogu.com.cn/problem/P3846.
 */
pair<bool, int> ModLog(Z a, Z b) {
    int p = Z::getMod();
    int sqr = sqrt(p) + 0.5;
    while (1LL * sqr * sqr < p) sqr++;
    Z c = 1;
    vector<pair<Z, int>> vec;
    rep(i, 1, sqr) {
        c *= a;
        vec.emplace_back(b * c, -i);
    }
    sort(all(vec));
    Z d = 1;
    rep(i, 1, sqr) {
        d *= c;
        auto it = lower_bound(all(vec), make_pair(d, -p));
        if (it != vec.end() && it->first == d) {
            return {true, i * sqr + it->second};
        }
    }
    return {false, 0};
}
