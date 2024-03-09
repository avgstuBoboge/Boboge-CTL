/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-06
 * Description: Dinic algorithm for flow graph $G = (V, E)$. You can get a minimum $src-sink$ cut easily. To get such minimum cut, first run $MaxFlow(src, sink)$. Then you can run $getMinCut()$ to obtain a Minimum Cut (vertices in the same part as $src$ are returned).
 * Time: O(|V|^2 |E|) for arbitrary networks. O(|E| \sqrt{|V|}) for bipartite/unit network. O(min{|V|^{2/3}, |E|^{1/2}} |E|) for networks with only unit capacities.
 * Status: tested on https://codeforces.com/gym/103861/problem/H. Seems to be fast enough now.
 *  getDirFlow() and getUndirFlow() are not tested yet.
 */

template<class Cap = int, Cap Cap_MAX = numeric_limits<Cap>::max()>
struct Dinic {
    int n; /// start-hash
    struct E {
        int to;
        Cap a;
    }; // Endpoint & Admissible flow.
    vector<E> es;
    vector<vector<int>> g;
    vector<int> dis; // Put it here to get the minimum cut easily.

    Dinic(int n) : n(n), g(n) {}

    void addEdge(int u, int v, Cap c, bool dir = 1) {
        g[u].push_back(es.size());
        es.push_back({v, c});
        g[v].push_back(es.size());
        es.push_back({u, dir ? 0 : c});
    }

    Cap MaxFlow(int src, int sink) {
        auto revbfs = [&]() {
            dis.assign(n, -1);
            dis[sink] = 0;
            vector<int> que{sink};
            for (int ind = 0; ind < que.size(); ++ind) {
                int now = que[ind];
                for (auto i: g[now]) {
                    int v = es[i].to;
                    if (es[i ^ 1].a > 0 && dis[v] == -1) {
                        dis[v] = dis[now] + 1;
                        que.push_back(v);
                        if (v == src) return 1;
                    }
                }
            }
            return 0;
        };
        vector<int> cur;
        auto dfs = [&](auto &dfs, int now, Cap flow) {
            if (now == sink) return flow;
            Cap res = 0;
            for (int &ind = cur[now]; ind < g[now].size(); ind++) {
                int i = g[now][ind];
                auto [v, c] = es[i];
                if (c > 0 && dis[v] == dis[now] - 1) {
                    Cap x = dfs(dfs, v, min(flow - res, c));
                    res += x;
                    es[i].a -= x;
                    es[i ^ 1].a += x;
                }
                if (res == flow) break;
            }
            return res;
        };

        Cap ans = 0;
        while (revbfs()) {
            cur.assign(n, 0);
            ans += dfs(dfs, src, Cap_MAX);
        }
        return ans;
    } /// end-hash

    // Returns a min-cut containing the src.
    vector<int> getMinCut() { /// start-hash
        vector<int> res;
        for (int i = 0; i < n; ++i)
            if (dis[i] == -1) res.push_back(i);
        return res;
    } /// end-hash

    // Gives flow on edge assuming it is directed/undirected. Undirected flow is signed.
    Cap getDirFlow(int i) { return es[i * 2 + 1].a; }

    Cap getUndirFlow(int i) { return (es[i * 2 + 1].a - es[i * 2].a) / 2; }
};