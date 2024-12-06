/**
 * Author: Boboge
 * Date: 24-11-25
 * Description: Get the Dominator Tree of directed graph $G=(V, E)$. idm[root] = root, and idm[u] = -1 for vertices not reachable from root.
 * Time: O((|V|+|E|) \alpha(|V|,|E|)).
 * Status: tested on https://judge.yosupo.jp/submission/252293.
 */
auto domTree(int n, const vector<pair<int, int>> &es, int rt = 0) {
    vector g(3, vector<vector<int>>(n));
    for (auto [u, v]: es) {
        g[0][u].push_back(v);
        g[1][v].push_back(u);
    }
    vector<int> dfn(n, -1), pos(n), fth(n, -1), fa(n), mn(n), sdm(n), idm(n, -1);
    iota(fa.begin(), fa.end(), 0);
    iota(mn.begin(), mn.end(), 0);
    iota(sdm.begin(), sdm.end(), 0);
    int now = 0;
    auto dfs = [&](auto &dfs, int u) -> void {
        pos[now] = u;
        dfn[u] = now++;
        for (int v: g[0][u]) {
            if (dfn[v] == -1) {
                dfs(dfs, v);
                fth[v] = u;
            }
        }
    };
    auto find = [&](auto &dfs, int x) {
        if (fa[x] == x) {
            return x;
        }
        int tmp = fa[x];
        fa[x] = dfs(dfs, fa[x]);
        if (dfn[sdm[mn[tmp]]] < dfn[sdm[mn[x]]]) {
            mn[x] = mn[tmp];
        }
        return fa[x];
    };
    dfs(dfs, rt);
    for (int i = now - 1; i; --i) {
        int u = pos[i], res = 1e9;
        for (int v: g[1][u]) {
            if (dfn[v] == -1) continue;
            find(find, v);
            if (dfn[v] < dfn[u]) {
                res = min(res, dfn[v]);
            } else {
                res = min(res, dfn[sdm[mn[v]]]);
            }
        }
        sdm[u] = pos[res];
        fa[u] = fth[u];
        g[2][sdm[u]].push_back(u);
        u = fth[u];
        for (int v: g[2][u]) {
            find(find, v);
            if (u == sdm[mn[v]]) {
                idm[v] = u;
            } else {
                idm[v] = mn[v];
            }
        }
        g[2][u].clear();
    }
    for (int i = 1; i < now; ++i) {
        int u = pos[i];
        if (idm[u] != sdm[u]) {
            idm[u] = idm[idm[u]];
        }
    }
    idm[rt] = rt;
    return idm;
}