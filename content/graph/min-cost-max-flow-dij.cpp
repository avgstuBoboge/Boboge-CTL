/**
 * Author: Boboge adapted from zawei
 * Date: 23-02-06
 * Description: min-cost-max-flow for graph $G = (V, E)$. Using dijkstra.
 * Run $compute(src, sink)$ for some $src$ and $sink$ to get the minimum cost and the maximum flow. Can \textbf{NOT} deal with negative costs.
 * Time: ???
 * Status: tested
 */
template<class T>
struct Minimum_Cost_Flow_Dijkstra {
#define N 5050
    using P = pair<T, int>;
    struct edge {
        int to;
        T cap, cost, rev;
    };
    T flow, res, dist[N], h[N];
    vector<edge> G[N];
    int preV[N], preE[N], n;

    inline void init(int x) {
        n = x;
        for (int i = 0; i <= n; i++) {
            G[i].clear();
        }
    }

    inline void addEdge(int from, int to, T cap, T cost) {
        G[from].push_back((edge) {to, cap, cost, (int) G[to].size()});
        G[to].push_back((edge) {from, 0, -cost, (int) G[from].size() - 1});
    }

    inline void min_cost_flow(int s, int t, T f) {
        fill(h + 1, h + 1 + n, 0);
        flow = res = 0;
        while (f > 0) {
            priority_queue<P, vector<P>, greater<P>> D;
            memset(dist, INF, sizeof dist);
            dist[s] = 0;
            D.push(P(0, s));
            while (!D.empty()) {
                P now = D.top();
                D.pop();
                if (dist[now.second] < now.first) continue;

                int v = now.second;
                for (int i = 0; i < (int) G[v].size(); ++i) {
                    edge &e = G[v][i];
                    if (e.cap > 0 &&
                        dist[e.to] > dist[v] + e.cost + h[v] - h[e.to]) {
                        dist[e.to] = dist[v] + e.cost + h[v] - h[e.to];
                        preV[e.to] = v;
                        preE[e.to] = i;
                        D.push(P(dist[e.to], e.to));
                    }
                }
            }
            if (dist[t] == INF) break;
            for (int i = 1; i <= n; ++i) {
                h[i] += dist[i];
            }
            T d = f;
            for (int v = t; v != s; v = preV[v]) {
                d = min(d, G[preV[v]][preE[v]].cap);
            }
            f -= d;
            flow += d;
            res += d * h[t];
            for (int v = t; v != s; v = preV[v]) {
                edge &e = G[preV[v]][preE[v]];
                e.cap -= d;
                G[v][e.rev].cap += d;
            }
        }
    }

#undef N
};