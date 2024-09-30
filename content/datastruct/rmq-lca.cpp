/**
 * Author: Boboge
 * Date: 24-10-01
 * Description: Transform LCA problem of tree $T$ to RMQ on dfs order. The root is set as $0$ by default.
 *  $g$ should be the adjacent list of the tree $T$.
 * Time: O(|V|\log |V|) for precalculation and O(1) for each $lca$ query.
 * Status: tested on https://www.luogu.com.cn/problem/P3379.
 */
struct LCA {
    int n;
    vector<vector<int>> st;
    vector<int> dfn;

    int func(int x, int y) {
        return dfn[x] < dfn[y] ? x : y;
    }

    LCA(const vector<vector<int>> &g, int rt = 0) : n(g.size()), dfn(n) {
        int now = 0;
        vector<int> init(n);
        st.assign(__lg(n) + 1, vector<int>(n));
        auto dfs = [&](auto &dfs, int u, int fa) -> void {
            dfn[u] = now++;
            init[dfn[u]] = fa;
            for (int v: g[u]) {
                if (v == fa) continue;
                dfs(dfs, v, u);
            }
        };
        dfs(dfs, rt, -1);
        st[0] = init;
        for (int j = 1; j < st.size(); ++j) {
            for (int i = 0; i + (1 << (j - 1)) < n; ++i) {
                st[j][i] = func(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    int lca(int u, int v) {
        if (u == v) return u;
        if (dfn[u] > dfn[v]) swap(u, v);
        int l = dfn[u] + 1, r = dfn[v];
        int k = __lg(r - l + 1);
        return func(st[k][l], st[k][r - (1 << k) + 1]);
    }
};