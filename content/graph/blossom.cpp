/**
 * Author: Boboge adapted from Yuhdao Yao
 * Date: 22-10-23
 * Description: Maximum matching of a \textbf{general} graph $G = (V, E)$. Edges $E$ should be described as pairs such that pair $(u, v)$ means that there is an edge between vertex $u$ and vertex $v$.
 * Time: O(|V||E|).
 * Status: tested on https://www.luogu.com.cn/problem/P6113， https://uoj.ac/problem/79, https://codeforces.com/gym/103260/problem/E, https://ac.nowcoder.com/acm/contest/5666/I.
 **/
vector<int> Blossom(int n, const vector<pair<int, int>> &es) {
    vector<vector<int>> g(n);
    for (auto [x, y]: es) {
        g[x].push_back(y);
        g[y].push_back(x);
    }
    vector<int> match(n, -1);
    auto aug = [&](int st) {
        vector<int> fa(n), clr(n, -1), pre(n, -1), tag(n);
        iota(fa.begin(), fa.end(), 0);
        int tot = 0;
        vector<int> que{st};
        clr[st] = 0;
        function<int(int)> getfa = [&](int x) {
            return fa[x] == x ? x : fa[x] = getfa(fa[x]);
        };
        auto lca = [&](int x, int y) {
            tot++;
            x = getfa(x);
            y = getfa(y);
            while (1) {
                if (x != -1) {
                    if (tag[x] == tot) return x;
                    tag[x] = tot;
                    if (match[x] != -1) x = getfa(pre[match[x]]);
                    else x = -1;
                }
                swap(x, y);
            }
        };
        auto shrink = [&](int x, int y, int f) {
            while (getfa(x) != f) {
                pre[x] = y;
                y = match[x];
                if (clr[y] == 1) {
                    clr[y] = 0;
                    que.push_back(y);
                }
                if (getfa(x) == x) fa[x] = f;
                if (getfa(y) == y) fa[y] = f;
                x = pre[y];
            }
        };
        for (int ind = 0; ind < que.size(); ++ind) {
            int now = que[ind];
            for (auto v: g[now]) {
                if (getfa(now) == getfa(v) || clr[v] == 1) continue;
                if (clr[v] == -1) {
                    clr[v] = 1;
                    pre[v] = now;
                    if (match[v] == -1) {
                        while (now != -1) {
                            int last = match[now];
                            match[now] = v;
                            match[v] = now;
                            if (last != -1) {
                                v = last;
                                now = pre[v];
                            } else break;
                        }
                        return;
                    }
                    clr[match[v]] = 0;
                    que.push_back(match[v]);
                } else if (clr[v] == 0) {
                    assert(getfa(now) != getfa(v));
                    int l = lca(now, v);
                    shrink(now, v, l);
                    shrink(v, now, l);
                }
            }
        }
    };
    for (int i = 0; i < n; ++i) {
        if (match[i] == -1) aug(i);
    }
    return match;
}