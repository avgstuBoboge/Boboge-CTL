/**
 * Author: Boboge adapted from peehs_moorhsum
 * Date: 23-02-06
 * Description: return the hash value of every subtree.
 * Time: O(N).
 * Status: tested on https://uoj.ac/problem/763
 */
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

struct treeHash {
    using u64 = unsigned long long;
    u64 bas = rnd();

    u64 H(ull x) {
        return x * x * x * 114514 + 19260817;
    }

    u64 F(ull x) {
        return H(x & ((1ll << 32) - 1)) + H(x >> 32);
    }

    vector<ull> h;

    treeHash(vector<vector<int>> &adj, int rt = 0) : h(adj.size()) {
        auto dfs = [&](auto dfs, int u, int fa) -> void {
            h[u] = bas;
            for (int v: adj[u]) {
                if (v == fa) continue;
                dfs(dfs, v, u);
                h[u] += F(h[v]);
            }
        };
        dfs(dfs, rt, -1);
    }
};