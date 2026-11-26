/**
 * Author: Yuhao Yao
 * Date: 22-07-24
 * Description: This is for cyclic suffices. You can push a zero to the back of the string and then call SA to get suffix array for non-cyclic suffices.
 * Usage: SA sa(s + string(1, 0)) for non-cyclic suffices.
 * Time: O(|s| \log |s|).
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/B, https://codeforces.com/gym/102994/problem/D, https://ac.nowcoder.com/acm/contest/33195/D.
 */
struct SA {
	int n;
	vi str, sa, rank, h;
	template<class T> SA(const T &s): n(sz(s)), str(n), sa(n), rank(n), h(n - 1) {
		auto vec = s;
		sort(all(vec)); vec.erase(unique(all(vec)), vec.end());
		rep(i, 0, n - 1) str[i] = rank[i] = lower_bound(all(vec), s[i]) - vec.begin();
		iota(all(sa), 0);
		auto next = [&](int a, int b) { return a + b < n ? a + b : a + b - n; };
		for (int len = 0; len < n; len = (len ? len * 2 : 1)) {
			vi cnt(n + 1);
			for (auto v : rank) cnt[v + 1]++;
			rep(i, 1, n - 1) cnt[i] += cnt[i - 1];
			vi nsa(n), nrank(n);
			for (auto pos: sa) {
				pos -= len;
				if (pos < 0) pos += n;
				nsa[cnt[rank[pos]]++] = pos;
			}
			swap(sa, nsa);
			int r = 0, oldp = -1;
			for (auto p: sa) {
				if (~oldp) r += (rank[p] != rank[oldp]) || (rank[next(p, len)] != rank[next(oldp, len)]);
				nrank[p] = r;
				oldp = p;
			}
			swap(rank, nrank);
		}
		rep(i, 0, n - 1) rank[sa[i]] = i;
		// compute height array.
		for (int i = 0, len = 0; i < n; ++i) {
			if (len) len--;
			int rk = rank[i];
			if (rk == n - 1) continue;
			while (len < n && str[next(i, len)] == str[next(sa[rk + 1], len)]) len++;
			h[rk] = len;
		}
	}
};