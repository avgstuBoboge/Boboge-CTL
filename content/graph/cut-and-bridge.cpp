/**
 * Author: Boboge, adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: Given an undirected graph $G = (V, E)$, compute all cut vertices and bridges. Cut vertices and bridges are returned in vectors containing indices.
 * Time: O(|V| + |E|).
 * Status: (cut) tested on: https://www.luogu.com.cn/problem/P3388;
 *  (bridge) tested on: https://www.luogu.com.cn/problem/P1656.
 */
auto CutAndBridge(int n, const vector<pair<int, int>> es) {
    vector<vector<int>> g(n);
    for (int i = 0; i < es.size(); ++i) {
        auto [x, y] = es[i];
        g[x].push_back(i);
        g[y].push_back(i);
    }
    vector<int> cut, bridge, dfn(n, -1), low(n), mark(es.size());
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
    for (int i = 0; i < n; ++i) if (dfn[i] == -1) dfs(dfs, i, -1);
    return make_tuple(cut, bridge);
}