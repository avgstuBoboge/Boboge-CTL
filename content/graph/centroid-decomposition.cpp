/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-06
 * Description: Centroid Decomposition of tree $T$. Here, $anc[i]$ is the list of ancestors of vertex $i$ and the distances to the corresponding ancestor in centroid tree, including itself. Note that the distances are not monotone. Note that the top centroid is in the front of the vector.
 * Time: O(|T| \log |T|).
 * Status: tested on https://codeforces.com/gym/101981/problem/C, https://codeforces.com/contest/1260/problem/F.
 */
struct CentroidDecomposition {
    int n;
    vector<vector<pair<int, int>>> ancs;

    CentroidDecomposition(vector<vector<int>> &g) : n(g.size()), ancs(n) {
        vector<int> siz(n), vis(n);
        auto solve = [&](auto &solve, int st, int tot) -> void {
            int mn = 0x3f3f3f3f, cent = -1;
            auto getcent = [&](auto &dfs, int u, int fa) -> void {
                siz[u] = 1;
                int mx = 0;
                for (auto v: g[u]) {
                    if (v != fa && vis[v] == 0) {
                        dfs(dfs, v, u);
                        siz[u] += siz[v];
                        mx = max(mx, siz[v]);
                    }
                }
                mx = max(mx, tot - siz[u]);
                if (mn > mx) mn = mx, cent = u;
            };
            getcent(getcent, st, -1);
            vis[cent] = 1;
            auto dfs = [&](auto &dfs, int u, int fa, int dep) -> void {
                ancs[u].emplace_back(cent, dep);
                for (auto v: g[u]) {
                    if (v != fa && vis[v] == 0) {
                        dfs(dfs, v, u, dep + 1);
                    }
                }
            };
            dfs(dfs, cent, -1, 0);
            // start your work here or inside the function dfs.
            for (auto v: g[cent]) {
                if (vis[v]) continue;
                solve(solve, v, siz[v] < siz[cent] ? siz[v] : tot - siz[cent]);
            }
        };
        solve(solve, 0, n);
    }
};
