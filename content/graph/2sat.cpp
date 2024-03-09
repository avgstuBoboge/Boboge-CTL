/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: 2SAT solver, returns if a 2SAT system of $V$ variables and $C$ constraints is satisfiable. If yes, it also gives an assignment.
 *  Call $addClause$ to add clauses. For example, if you want to add clause $\neg x \lor y$, just call $addClause(x, 0, y, 1)$.
 * Time: O(|V| + |C|).
 * Status: tested on https://codeforces.com/gym/103260/problem/E, https://www.luogu.com.cn/problem/P4782.
 */
struct TwoSat {
    int n;
    vector<vector<int>> e;
    vector<int> ans;

    TwoSat(int n) : n(n), e(n * 2), ans(n) {}

    void addClause(int x, bool f, int y, bool g) {
        e[x * 2 + !f].push_back(y * 2 + g);
        e[y * 2 + !g].push_back(x * 2 + f);
    }

    bool satisfiable() {
        vector<int> id(n * 2, -1), dfn(n * 2, -1), low(n * 2, -1), sta;
        int cnt = 0, scc = 0;
        function<void(int)> dfs = [&](int now) {
            dfn[now] = low[now] = cnt++;
            sta.push_back(now);
            for (auto v: e[now]) {
                if (dfn[v] == -1) {
                    dfs(v);
                    low[now] = min(low[now], low[v]);
                } else if (id[v] == -1) low[now] = min(low[now], dfn[v]);
            }
            if (low[now] == dfn[now]) {
                while (sta.back() != now) {
                    id[sta.back()] = scc;
                    sta.pop_back();
                }
                id[sta.back()] = scc;
                sta.pop_back();
                scc++;
            }
        };
        for (int i = 0; i < n * 2; ++i) {
            if (dfn[i] == -1) dfs(i);
        }
        for (int i = 0; i < n; ++i) {
            if (id[i * 2] == id[i * 2 + 1]) return false;
            ans[i] = id[i * 2] > id[i * 2 + 1];
        }
        return true;
    }

    vector<int> getAss() { return ans; }
};