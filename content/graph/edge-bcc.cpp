/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: Compute the Edge-BiConnected Components of graph. Multiple edges and self loops are allowed. Return the size of BCCs and the index of the component each vertex belongs to.
 * Time: O(|V| + |E|).
 * Status: tested on https://www.luogu.com.cn/problem/P8436
 */
auto EdgeBCC(int n, const vector<pair<int, int>> &es) {
    vector<int> dfn(n, -1), low(n), id(n), mark(es.size(), 0), sta;
    int cnt = 0, bcc = 0;
    vector<vector<int>> g(n);
    for (int i = 0; i < es.size(); ++i) {
        auto [x, y] = es[i];
        g[x].push_back(i);
        g[y].push_back(i);
    }
    auto dfs = [&](auto dfs, int now) -> void {
        low[now] = dfn[now] = cnt++;
        sta.push_back(now);
        for (auto ind: g[now])
            if (mark[ind] == 0) {
                mark[ind] = 1;
                auto [x, y] = es[ind];
                int v = now ^ x ^ y;
                if (dfn[v] == -1) {
                    dfs(dfs, v);
                    low[now] = min(low[now], low[v]);
                } else low[now] = min(low[now], dfn[v]);
            }
        if (low[now] == dfn[now]) {
            while (1) {
                int x = sta.back();
                id[x] = bcc;
                sta.pop_back();
                if (x == now) break;
            }
            bcc++;
        }
    };
    for (int i = 0; i < n; ++i) {
        if (dfn[i] == -1) {
            dfs(dfs, i);
        }
    }
    return make_tuple(bcc, id);
}