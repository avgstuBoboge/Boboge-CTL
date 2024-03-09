/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-11
 * Description: For an edge set $E$ such that each vertex has an even degree, compute Euler tour for each connected component. $dir$ indicates edges are directed or not (undirected by default). For undirected graph, $ori[i]$ records the orientation of the $i$-th edge $es[i] = (x, y)$, where $ori[i] = 1$ means $x \to y$ and $ori[i] = -1$ means $y \to x$.
 *  Note that this is a non-recursive implementation, which avoids stack size issue on some OJ and also saves memory (roughly saves 2/3 of memory) due to that.
 * Time: $O(|V| + |E|)$.
 * Status: tested on https://acm.hdu.edu.cn/showproblem.php?pid=7261, https://ac.nowcoder.com/acm/contest/4010/H.
 */
struct EulerTour {
    int n;
    vector<vector<int>> tours;
    vector<int> ori;

    EulerTour(int n, const vector<pair<int, int>> &es, int dir = 0) : n(n), ori(es.size()) {
        vector<vector<int>> g(n);
        int m = es.size();
        for (int i = 0; i < m; ++i) {
            auto [x, y] = es[i];
            g[x].push_back(i);
            if (dir == 0) g[y].push_back(i);
        }
        vector<int> path, cur(n);
        vector<pair<int, int>> sta;
        auto solve = [&](int st) {
            sta.emplace_back(st, -1);
            while (!sta.empty()) {
                auto [now, pre] = sta.back();
                int fin = 1;
                for (int &i = cur[now]; i < g[now].size();) {
                    auto ind = g[now][i++];
                    if (ori[ind]) continue;
                    auto [x, y] = es[ind];
                    ori[ind] = x == now ? 1 : -1;
                    int v = now ^ x ^ y;
                    sta.emplace_back(v, ind);
                    fin = 0;
                    break;
                }
                if (fin) {
                    if (pre != -1) path.push_back(pre);
                    sta.pop_back();
                }
            }
        };

        for (int i = 0; i < n; ++i) {
            path.clear();
            solve(i);
            if (!path.empty()) {
                reverse(path.begin(), path.end());
                tours.push_back(path);
            }
        }
    }

    vector<vector<int>> getTours() { return tours; }

    vector<int> getOrient() { return ori; }
};