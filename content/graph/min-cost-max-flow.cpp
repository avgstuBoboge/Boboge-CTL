/**
 * Author: Boboge adapted from nweeks
 * Date: 23-04-18
 * Description: min-cost-max-flow for graph $G = (V, E)$.
 * Run $compute(src, sink)$ for some $src$ and $sink$ to get the minimum cost and the maximum flow. Can deal with negative costs.
 * Time: not sure. seems fast enough.
 * Status: tested on https://uoj.ac/problem/487
 */
template<class T>
struct MCMF {
    struct Edge {
        int nxt, to;
        T cap, cost;
    };
    vector<Edge> es;
    vector<int> head, fa, fe, mark, cyc;
    vector<T> dual;
    int ti;
    T sum;

    MCMF(int n) : head(n, 0), fa(n), fe(n), dual(n), mark(n), cyc(n) {
        sum = 1, ti = 0;
        es.push_back({0, 0, 0, 0});
        es.push_back({0, 0, 0, 0});
    }

    int addEdge(int u, int v, T cap, T cost) {
        sum += abs(cost);
        int e = (int) es.size();
        es.push_back({head[u], v, cap, cost});
        head[u] = e;
        es.push_back({head[v], u, 0, -cost});
        head[v] = e + 1;
        return e;
    }

    void dfs(int x) {
        mark[x] = 1;
        for (int i = head[x]; i; i = es[i].nxt) {
            int v = es[i].to;
            if (!mark[v] and es[i].cap) {
                fa[v] = x, fe[v] = i;
                dfs(v);
            }
        }
    }

    T phi(int x) {
        if (mark[x] == ti) return dual[x];
        return mark[x] = ti, dual[x] = phi(fa[x]) - es[fe[x]].cost;
    }

    void push(int e, T &cost) {
        int pen = es[e ^ 1].to, lca = es[e].to;
        ti++;
        while (pen) mark[pen] = ti, pen = fa[pen];
        while (mark[lca] != ti) mark[lca] = ti, lca = fa[lca];
        int e2 = 0, path = 2, clen = 0;
        T f = es[e].cap;
        for (int i = es[e ^ 1].to; i != lca; i = fa[i]) {
            cyc[clen++] = fe[i];
            if (es[fe[i]].cap < f) f = es[fe[e2 = i] ^ (path = 0)].cap;
        }
        for (int i = es[e].to; i != lca; i = fa[i]) {
            cyc[clen++] = fe[i] ^ 1;
            if (es[fe[i] ^ 1].cap <= f) f = es[fe[e2 = i] ^ (path = 1)].cap;
        }
        cyc[clen++] = e;
        for (int i = 0; i < clen; ++i) {
            es[cyc[i]].cap -= f, es[cyc[i] ^ 1].cap += f;
            cost += es[cyc[i]].cost * f;
        }
        if (path == 2) return;
        int le = e ^ path, last = es[le].to, cur = es[le ^ 1].to;
        while (last != e2) {
            mark[cur]--;
            le ^= 1;
            swap(le, fe[cur]);
            swap(last, fa[cur]);
            swap(last, cur);
        }
    }

    pair<T, T> compute(int s, int t) {
        T tot = sum;
        int ed = addEdge(t, s, numeric_limits<T>::max(), -tot);
        T cost = 0;
        dfs(0);
        mark[0] = ti = 2;
        fa[0] = 0;
        int nc = (int) es.size() - 1;
        for (int i = 2, pre = nc; i != pre; i = i == nc ? 2 : i + 1) {
            if (es[i].cap && es[i].cost < phi(es[i ^ 1].to) - phi(es[i].to)) push(pre = i, cost);
        }
        T flow = es[ed ^ 1].cap;
        cost += tot * flow;
        return {flow, cost};
    }
};
