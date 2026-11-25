/**
 * Author: Boboge, adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: Given an undirected graph $G = (V, E)$, compute all cut vertices and bridges. Cut vertices and bridges are returned in vectors containing indices.
 * Time: O(|V| + |E|).
 * Status: tested. (cut) tested on: https://www.luogu.com.cn/problem/P3388;
 *  (bridge) tested on: https://www.luogu.com.cn/problem/P1656.
 */
auto CutAndBridge(int n, const vector<pii> es) {
    vector<vi> g(n);
    rep(i, 0, sz(es) - 1) {
        auto [x, y] = es[i];
        g[x].push_back(i);
        g[y].push_back(i);
    }
    vi cut, bridge, dfn(n, -1), low(n), mark(sz(es));
    int cnt = 0;
    auto dfs = [&](auto &dfs, int now, int fa) -> void {
        dfn[now] = low[now] = cnt++;
        int sons = 0, isCut = 0;
        for (auto ind: g[now])
            if (mark[ind] == 0) {
                mark[ind] = 1;
                auto [x, y] = es[ind];
                int v = now ^ x ^ y;
                if (dfn[v] == -1) {
                    sons++;
                    dfs(dfs, v, now);
                    low[now] = min(low[now], low[v]);
                    if (low[v] == dfn[v]) bridge.push_back(ind);
                    if (low[v] >= dfn[now] && fa != -1) isCut = 1;
                } else low[now] = min(low[now], dfn[v]);
            }
        if (fa == -1 && sons > 1) isCut = 1;
        if (isCut) cut.push_back(now);
    };
    rep(i, 0, n - 1) if (dfn[i] == -1) dfs(dfs, i, -1);
    return make_tuple(cut, bridge);
}