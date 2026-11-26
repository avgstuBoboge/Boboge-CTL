/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Given a ground set $E$ and two matroid $M_1 = (E, I_1)$ and $M_2 = (E, I_2)$, compute a largest independent set in their intersection $M = (E, I_1 \cap I_2)$, i.e. an element in $I_1 \cap I_2$ of largest size.
 * Denote by $as$ the ground set. $rebuild(A)$ rebuilds the data structure using elements in $A$. Then $check1(x)$ returns if $A \cup \{x\} \in I_1$ and $check2$ returns if $A \cup \{x\} \in I_2$ using the data structure just built before.
 * Time: O(r^2 |E|), where $r = min(r(E, I_1), r(E, I_2))$.
 * Status: tested on https://codeforces.com/gym/102156/problem/D, https://codeforces.com/gym/101561/problem/B, https://official.contest.yandex.com/opencupXXII/contest/37753/problems/B/.
 */
template<class T>
vector<T> MatroidIntersection(const vector<T> &as, function<void(const vector<T>&)> rebuild, function<bool(const T&)> check1, function<bool(const T&)> check2) {
	int n = sz(as); 
	vi used(n);
	vector<vi> g;
	vector<T> A;
	auto augment = [&]() {
		int tot = n, s = tot++, t = tot++;
		g.assign(tot, {});
		A.clear();
		rep(i, 0, n - 1) if (used[i]) A.push_back(as[i]);
		rebuild(A);
		rep(y, 0, n - 1) if (used[y] == 0) {
			int cnt = 0;
			if (check1(as[y])) g[s].push_back(y), cnt++;
			if (check2(as[y])) g[y].push_back(t), cnt++;
			if (cnt == 2) { // if we have s -> y -> t, then we could just augment via this path!
				used[y] = 1;
				return 1;
			}
		}
		rep(x, 0, n - 1) if (used[x]) {
			A.clear();
			rep(i, 0, n - 1) if (used[i] && i != x) A.push_back(as[i]);
			rebuild(A);
			rep(y, 0, n - 1) if (used[y] == 0) {
				if (check1(as[y])) g[x].push_back(y);
				if (check2(as[y])) g[y].push_back(x);
			}
		}
		vi dis(tot, -1), pre(tot);
		vi que{s}; 
		dis[s] = 0;
		rep(ind, 0, sz(que) - 1) {
			int now = que[ind];
			for (auto v: g[now]) if (dis[v] == -1) {
				dis[v] = dis[now] + 1;
				que.push_back(v);
				pre[v] = now;
			}
		}
		if (dis[t] == -1) return 0;
		int now = pre[t];
		while (now != s) {
			used[now] ^= 1;
			now = pre[now];
		}
		return 1;
	};
	while (augment());
	vector<T> res;
	rep(i, 0, n - 1) if (used[i]) res.push_back(as[i]);
	return res;
};
