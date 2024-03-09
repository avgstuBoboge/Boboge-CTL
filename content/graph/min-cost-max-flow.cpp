/**
 * Author: Boboge adapted from nweeks
 * Date: 23-04-18
 * Description: min-cost-max-flow for graph $G = (V, E)$.
 * Run $compute(src, sink)$ for some $src$ and $sink$ to get the minimum cost and the maximum flow. Can deal with negative costs.
 * Time: not sure. seems fast enough.
 * Status: tested on https://uoj.ac/problem/487 and luogu(same problem)
 */
struct MCMF {
    struct Edge {
        ll nxt, to;
        ll cap, cost;
    };
    vector<Edge> edges;
    vector<ll> head, fa, fe, dual, mark, cyc;
    ll ti{}, sum{};

    MCMF(ll n) : head(n, 0), fa(n), fe(n), dual(n), mark(n), cyc(n + 1) {
        edges.push_back({0, 0, 0, 0});
        edges.push_back({0, 0, 0, 0});
    }

    ll addEdge(ll u, ll v, ll cap, ll cost) {
        sum += abs(cost);
        assert(edges.size() % 2 == 0);
        ll e = edges.size();
        edges.push_back({head[u], v, cap, cost});
        head[u] = e;
        edges.push_back({head[v], u, 0, -cost});
        head[v] = e + 1;
        return e;
    }

    void initTree(ll x) {
        mark[x] = 1;
        for (ll i = head[x]; i; i = edges[i].nxt) {
            ll v = edges[i].to;
            if (!mark[v] and edges[i].cap) {
                fa[v] = x, fe[v] = i;
                initTree(v);
            }
        }
    }

    ll phi(ll x) {
        if (mark[x] == ti) return dual[x];
        return mark[x] = ti, dual[x] = phi(fa[x]) - edges[fe[x]].cost;
    }

    void pushFlow(ll e, ll &cost) {
        ll pen = edges[e ^ 1].to, lca = edges[e].to;
        ti++;
        while (pen) mark[pen] = ti, pen = fa[pen];
        while (mark[lca] != ti) mark[lca] = ti, lca = fa[lca];
        ll e2 = 0, path = 2, clen = 0;
        ll f = edges[e].cap;
        for (ll i = edges[e ^ 1].to; i != lca; i = fa[i]) {
            cyc[++clen] = fe[i];
            if (edges[fe[i]].cap < f) f = edges[fe[e2 = i] ^ (path = 0)].cap;
        }
        for (ll i = edges[e].to; i != lca; i = fa[i]) {
            cyc[++clen] = fe[i] ^ 1;
            if (edges[fe[i] ^ 1].cap <= f) f = edges[fe[e2 = i] ^ (path = 1)].cap;
        }
        cyc[++clen] = e;
        for (ll i = 1; i <= clen; ++i) {
            edges[cyc[i]].cap -= f, edges[cyc[i] ^ 1].cap += f;
            cost += edges[cyc[i]].cost * f;
        }
        if (path == 2) return;
        ll laste = e ^ path, last = edges[laste].to, cur = edges[laste ^ 1].to;
        while (last != e2) {
            mark[cur]--;
            laste ^= 1;
            swap(laste, fe[cur]);
            swap(last, fa[cur]);
            swap(last, cur);
        }
    }

    pair<ll, ll> compute(ll s, ll t) {
        ll tot = sum;
        ll ed = addEdge(t, s, 1e18, -tot);
        ll cost = 0;
        initTree(0);
        mark[0] = ti = 2;
        fa[0] = cost = 0;
        ll ncnt = (ll) edges.size() - 1;
        for (ll i = 2, pre = ncnt; i != pre; i = i == ncnt ? 2 : i + 1) {
            if (edges[i].cap && edges[i].cost < phi(edges[i ^ 1].to) - phi(edges[i].to)) pushFlow(pre = i, cost);
        }
        ll flow = edges[ed ^ 1].cap;
        cost += tot * flow;
        return {cost, flow};
    }
};