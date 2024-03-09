/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-11
 * Description: Finding a Maximum Clique of a graph $G = (V, E)$. Should be fine with $|V| \le 60$. (The algorithm actually enumberates all maximal clique, without double counting.)
 * Status: tested on https://judge.yosupo.jp/problem/maximum_independent_set, https://codeforces.com/contest/1578/problem/K.
 */
template<int L>
vector<int> BronKerbosch(int n, const vector<pair<int, int>> &es) {
    using bs = bitset<L>;
    vector<bs> nbrs(n);
    for (auto [x, y]: es) {
        nbrs[x].set(y);
        nbrs[y].set(x);
    }
    bs best;
    auto dfs = [&](auto &dfs, const bs &R, const bs &P, const bs &X) {
        if (P.none() && X.none()) {
            if (R.count() > best.count()) best = R;
            return;
        }
        bs tmp = P & ~nbrs[(P | X)._Find_first()];
        for (int v = tmp._Find_first(); v != L; v = tmp._Find_next(v)) {
            bs nR = R;
            nR.set(v);
            dfs(dfs, nR, P & nbrs[v], X & nbrs[v]);
        }
    };
    dfs(dfs, bs{}, bs{string(n, '1')}, bs{});
    vector<int> res;
    for (int i = 0; i < n; ++i) if (best[i]) res.push_back(i);
    return res;
}
