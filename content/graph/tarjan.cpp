/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: Tarjan algorithm for directed graph $G = (V, E)$. 
 * Status: tested on http://ejudge.opencup.org/~ejudge/team.cgi?contest_id=2745 problem J. https://www.luogu.com.cn/problem/P3387
 */
auto tarjan(const vector<vector<int>> &g) {
    int n = (int) g.size();
    vector<int> id(n, -1), dfn(n, -1), low(n, -1), sta;
    int cnt = 0, scc = 0;

    auto dfs = [&](auto &dfs, int now) -> void {
        dfn[now] = low[now] = cnt++;
        sta.push_back(now);
        for (auto v: g[now]) {
            if (dfn[v] == -1) {
                dfs(dfs, v);
                low[now] = min(low[now], low[v]);
            } else if (id[v] == -1) low[now] = min(low[now], dfn[v]);
        }
        if (low[now] == dfn[now]) {
            while (1) {
                int z = sta.back();
                sta.pop_back();
                id[z] = scc;
                if (z == now) break;
            }
            scc++;
        }
    };
    for (int i = 0; i < n; ++i) if (dfn[i] == -1) dfs(dfs, i);
    return make_tuple(scc, id);
}