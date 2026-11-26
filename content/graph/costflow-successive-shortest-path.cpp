/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Successive Shortest Path for flow graph $G = (V, E)$. 
 *  Run $mincostflow(src, sink)$ for some $src$ and $sink$ to get the minimum cost and the maximum flow. For negative costs, Bellman-Ford is necessary.
 * Time: O(|F| |E|\log{|E|}) for non-negative costs, where $|F|$ is the size of maximum flow. O(|V| |E| + |F| |E|\log{|E|}) for arbitrary costs.
 * Status: tested on https://qoj.ac/contest/503/problem/1269, https://codingcompetitions.withgoogle.com/codejam/round/0000000000436142/0000000000813e1a, https://codeforces.com/gym/103371/problem/L, https://codeforces.com/gym/102759/problem/F.
 */
template<class Cap, class Cost, Cap Cap_MAX = numeric_limits<Cap>::max(), Cost Cost_MAX = numeric_limits<Cost>::max() / 4>
struct SuccessiveShortestPath {
	int n;
	struct E { int to; Cap a; Cost w; };
	vector<E> es;
	vector<vi> g;
	vector<Cost> h;
	SuccessiveShortestPath(int n): n(n), g(n), h(n) {}
	void addEdge(int u, int v, Cap c, Cost w) {
		g[u].push_back(sz(es)); es.push_back({v, c, w});
		g[v].push_back(sz(es)); es.push_back({u, 0, -w});
	}
	pair<Cost, Cap> mincostflow(int src, int sink, Cap mx_flow = Cap_MAX) {
		// Run Bellman-Ford first if necessary.
		h.assign(n, Cost_MAX);
		h[src] = 0;
		rep(rd, 1, n) rep(now, 0, n - 1) for (auto i: g[now]) {
			auto [v, c, w] = es[i];
			if (c > 0) h[v] = min(h[v], h[now] + w);
		}
		// Bellman-Ford stops here.
		Cost cost = 0;
		Cap flow = 0;
		while (mx_flow) {
			priority_queue<pair<Cost, int>> pq;
			vector<Cost> dis(n, Cost_MAX);
			dis[src] = 0; pq.emplace(0, src);
			vi pre(n, -1), mark(n, 0);
			while (sz(pq)) {
				auto [d, now] = pq.top(); pq.pop();
				// Using mark[] is safer than compare -d and dis[now] when the Cost = double.
				if (mark[now]) continue;
				mark[now] = 1;
				for (auto i: g[now]) {
					auto [v, c, w] = es[i];
					Cost off = dis[now] + w + h[now] - h[v];
					if (c > 0 && dis[v] > off) {
						dis[v] = off;
						pq.emplace(-dis[v], v);
						pre[v] = i;
					}
				}
			}
			if (pre[sink] == -1) break;
			rep(i, 0, n - 1) if (dis[i] != Cost_MAX) h[i] += dis[i];
			Cap aug = mx_flow;
			for (int i = pre[sink]; ~i; i = pre[es[i ^ 1].to]) aug = min(aug, es[i].a);
			for (int i = pre[sink]; ~i; i = pre[es[i ^ 1].to]) es[i].a -= aug, es[i ^ 1].a += aug;
			mx_flow -= aug;
			flow += aug;
			cost += aug * h[sink];
		}
		return {cost, flow};
	}
};
