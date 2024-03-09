/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: Compute the Vertex-BiConnected Components of a graph $G = (V, E)$ (not necessarily connected). 
 *  Multiple edges and self loops are allowed.
 *  $id[i]$ records the index of bcc the $i$-th edge is in.
 *  $top[u]$ records the second highest vertex (which is unique) in the bcc which vertex $u$ is in. (Just for checking if two vertices are in the same bcc.)
 *  This code also builds the block forest: $bf$ records the edges in the block forest, where the $i$-th bcc corresponds to the $(n + i)$-th node. Call $getBlockForest()$ to get the adjacency list.
 *  One vertex may belong to multi Components.
 *  MINDS the isolated vertex!!! (forest[i] is empty)
 * Time: O(|V| + |E|).
 * Status: tested on https://codeforces.com/gym/102900/problem/K, https://www.luogu.com.cn/problem/P4630, https://codeforces.com/contest/487/problem/E, https://www.luogu.com.cn/problem/P4606.
 */
struct VertexBCC {
    int n, bcc; /// start-hash
    vector<int> id, top, fa;
    vector<pair<int, int>> bf; // edges of the block-forest.

    VertexBCC(int n, const vector<pair<int, int>> &es) : n(n), bcc(0), id(es.size()), top(n), fa(n, -1) {
        vector<vector<int>> g(n);
        for (int i = 0; i < es.size(); ++i) {
            auto [x, y] = es[i];
            g[x].push_back(i);
            g[y].push_back(i);
        }
        int cnt = 0;
        vector<int> dfn(n, -1), low(n), mark(es.size()), vsta, esta;
        auto dfs = [&](auto dfs, int now) -> void {
            low[now] = dfn[now] = cnt++;
            vsta.push_back(now);
            for (auto ind: g[now])
                if (mark[ind] == 0) {
                    mark[ind] = 1;
                    esta.push_back(ind);
                    auto [x, y] = es[ind];
                    int v = now ^ x ^ y;
                    if (dfn[v] == -1) {
                        dfs(dfs, v);
                        fa[v] = now;
                        low[now] = min(low[now], low[v]);
                        if (low[v] >= dfn[now]) {
                            bf.emplace_back(n + bcc, now);
                            while (1) {
                                int z = vsta.back();
                                vsta.pop_back();
                                top[z] = v;
                                bf.emplace_back(n + bcc, z);
                                if (z == v) break;
                            }
                            while (1) {
                                int z = esta.back();
                                esta.pop_back();
                                id[z] = bcc;
                                if (z == ind) break;
                            }
                            bcc++;
                        }
                    } else {
                        low[now] = min(low[now], dfn[v]);
                    }
                }
        };
        for (int i = 0; i < n; ++i) {
            if (dfn[i] == -1) {
                dfs(dfs, i);
                top[i] = i;
            }
        }
    } /// end-hash

    bool SameBcc(int x, int y) { /// start-hash
        if (x == fa[top[y]] || y == fa[top[x]]) return 1;
        else return top[x] == top[y];
    } /// end-hash

    vector<vector<int>> getBlockForest() { /// start-hash
        vector<vector<int>> g(n + bcc);
        for (auto [x, y]: bf) {
            g[x].push_back(y);
            g[y].push_back(x);
        }
        return g;
    } /// end-hash
};