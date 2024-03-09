/**
 * Author: Boboge
 * Date: 23-02-08
 * Description: BSGS for discrete log. Formally, it solves $a ^ x \equiv b (\mod\, p)$ given integer $a, b$ and a prime number $p$. Returns an solution $x$ if there exists.
 * Time: O(\sqrt{p} \log p).
 * Status: tested on https://www.luogu.com.cn/problem/P3846.
 */
pair<bool, int> ModLog(Z a, Z b) {
    int p = mod;
    int sqr = sqrt(p) + 0.5;
    while (1LL * sqr * sqr < p) sqr++;
    Z c = 1;
    vector<pair<Z, int>> vec;
    for (int i = 1; i <= sqr; ++i) {
        c *= a;
        vec.emplace_back(b * c, -i);
    }
    sort(vec.begin(), vec.end());
    Z d = 1;
    for (int i = 1; i <= sqr; ++i) {
        d *= c;
        auto it = lower_bound(vec.begin(), vec.end(), make_pair(d, -p));
        if (it != vec.end() && it->first == d) {
            return {true, i * sqr + it->second};
        }
    }
    return {false, 0};
}