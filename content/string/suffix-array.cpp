/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-11
 * Description: Suffix Array for non-cyclic string $s = s_0...s_{n - 1}$. 
 *  $rank[i]$ records the rank of the $i$-th suffix $s_i...s_{n - 1}$.
 *  $sa[i]$ records the starting position of the $i$-th smallest suffix.
 *  $h[i]$ (also called height array or lcp array) records the lcp of the $sa[i]$-th suffix and the $sa[i + 1]$-th suffix in $s$.
 * Usage: SA suf(s); // $s$ can be string or vector.
 * Time: O(|s| \log |s|).
 * Status: tested on https://www.luogu.com.cn/record/87444853, https://www.luogu.com.cn/problem/P4094, https://ac.nowcoder.com/acm/contest/33186/B, https://codeforces.com/gym/102994/problem/D, https://ac.nowcoder.com/acm/contest/33195/D, https://www.luogu.com.cn/problem/P8023, https://www.luogu.com.cn/problem/P7769.
 */

struct SA {
    int n;
    vi str, sa, rank, h;

    template<class T>
    SA(const T &s): n(sz(s)), str(n + 1), sa(n + 1), rank(n + 1), h(n - 1) {
        auto vec = s;
        sort(all(vec));
        vec.erase(unique(all(vec)), vec.end());
        rep(i, 0, n - 1) str[i] = rank[i] = lower_bound(all(vec), s[i]) - vec.begin() + 1;
        iota(all(sa), 0);
        n++;
        for (int len = 0; len < n; len = len ? len * 2 : 1) {
            vi cnt(n + 1);
            for (auto v: rank) cnt[v + 1]++;
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
                auto next = [&](int a, int b) { return a + b < n ? a + b : a + b - n; };
                if (~oldp) r += rank[p] != rank[oldp] || rank[next(p, len)] != rank[next(oldp, len)];
                nrank[p] = r;
                oldp = p;
            }
            swap(rank, nrank);
        }
        sa = vi(sa.begin() + 1, sa.end());
        rank.resize(--n);
        rep(i, 0, n - 1) rank[sa[i]] = i;
        // compute height array.
        int len = 0;
        rep(i, 0, n - 1) {
            if (len) len--;
            int rk = rank[i];
            if (rk == n - 1) continue;
            while (str[i + len] == str[sa[rk + 1] + len]) len++;
            h[rk] = len;
        }
    }
};