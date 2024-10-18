/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-06
 * Description: Heavy Light Decomposition for a rooted tree $T$. The root is set as $0$ by default. It can be modified easily for forest.
 *  $g$ should be the adjacent list of the tree $T$.
 *  $chainApply(u, v, func, val)$ and $chainAsk(u, v, func)$ are used for apply / query on the simple path from $u$ to $v$ on tree $T$. $func$ is the function you want to use to apply / query on a interval. (Say rangeApply / rangeAsk of Segment tree.)
 *  you can use lambda as the func arg.
 * Time: O(|T|) for building. O(\log |T|) for lca. O(\log |T| \cdot A) for chainApply / chainAsk, where $A$ is the running time of $func$ in chainApply / chainAsk.
 * Status: tested on https://codeforces.com/contest/487/problem/E.
 */
struct HLD {
    int n; /// start-hash
    vector<int> fa, hson, L, R, dep, top;

    HLD(vector <vector<int>> &g, int rt = 0) : n(g.size()), fa(n, -1), hson(n, -1), L(n), R(n), dep(n, 0), top(n) {
        vector<int> siz(n);
        auto dfs = [&](auto &dfs, int now) -> void {
            siz[now] = 1;
            int mx = 0;
            for (auto v: g[now])
                if (v != fa[now]) {
                    dep[v] = dep[now] + 1;
                    fa[v] = now;
                    dfs(dfs, v);
                    siz[now] += siz[v];
                    if (mx < siz[v]) {
                        mx = siz[v];
                        hson[now] = v;
                    }
                }
        };
        dfs(dfs, rt);
        int cnt = 0;
        auto getdfn = [&](auto &dfs, int now, int sp) -> void {
            top[now] = sp;
            L[now] = cnt++;
            if (hson[now] != -1) {
                dfs(dfs, hson[now], sp);
            }
            for (auto v: g[now]) {
                if (v != hson[now] && v != fa[now]) dfs(dfs, v, v);
            }
            R[now] = cnt - 1;
        };
        getdfn(getdfn, rt, rt);
    } /// end-hash

    int lca(int u, int v) { /// start-hash
        while (top[u] != top[v]) {
            if (dep[top[u]] < dep[top[v]]) swap(u, v);
            u = fa[top[u]];
        }
        if (dep[u] < dep[v]) return u;
        else return v;
    } /// end-hash

    auto getChain(int u, int v) { /// start-hash
        vector<pair<int, int>> ps;
        int f1 = top[u], f2 = top[v];
        while (f1 != f2) {
            if (dep[f1] < dep[f2]) swap(f1, f2), swap(u, v);
            ps.emplace_back(L[f1], L[u]);
            u = fa[f1];
            f1 = top[u];
        }
        if (dep[u] < dep[v]) swap(u, v);
        ps.emplace_back(L[v], L[u]);
        // change here if you want the info on edges.
        // if (L[v] < L[u]) ps.emplace_back(L[v] + 1, L[u]);
        return ps;
    } /// end-hash
};