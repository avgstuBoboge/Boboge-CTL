/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Aho Corasick Automaton of strings $s_0, ..., s_{n - 1}$. Call $build()$ after you insert all strings $s_0, ..., s_{n - 1}$.
 * Usage: AhoCorasick<'a', 26> ac; // for strings consisting of lowercase letters.
 *  ac.insert("abc"); // insert string "abc".
 *  ac.insert("acc"); // insert string "acc".
 *  ac.build();
 *  ac.query(s); returns a vector, records the match times of each state in s.
 * Time: O(\sum_{i = 0}^{n - 1} |s_i|).
 * Status: tested on http://ejudge.opencup.org/~ejudge/team.cgi?contest_id=2744 (problem M), https://www.luogu.com.cn/problem/P6125.
 */
template<char st, int C>
struct AhoCorasick {
    struct node {
        array<int, C> nxt;
        int fail;
        int cnt;

        node() {
            nxt.fill(-1);
            fail = -1;
            cnt = 0;
        }
    };

    vector<node> t;

    AhoCorasick() : t(1) {}

    int insert(const string &s) {
        int now = 0;
        for (auto ch: s) {
            int c = ch - st;
            if (t[now].nxt[c] == -1) {
                t.emplace_back();
                t[now].nxt[c] = sz(t) - 1;
            }
            now = t[now].nxt[c];
        }
        t[now].cnt++;
        return now;
    }

    void build() {
        vi que{0};
        rep(ind, 0, sz(que) - 1) {
            int now = que[ind], fa = t[now].fail;
            rep(c, 0, C - 1) {
                int &v = t[now].nxt[c];
                int u = fa == -1 ? 0 : t[fa].nxt[c];
                if (v == -1) v = u;
                else t[v].fail = u, que.push_back(v);
            }
            if (fa != -1) t[now].cnt += t[fa].cnt;
        }
    }

    vi query(const string &s) {
        vi ind(sz(t));
        vector<vi> adj(sz(t));
        vi que;
        rep(i, 0, sz(t) - 1) {
            if (t[i].fail != -1) {
                ind[i]++;
                adj[t[i].fail].push_back(i);
            }
        }
        rep(i, 0, sz(t) - 1) {
            if (ind[i] == 0) que.push_back(i);
        }
        vi top;
        rep(i, 0, sz(que) - 1) {
            int u = que[i];
            top.push_back(u);
            for (int v: adj[u]) {
                if (--ind[v] == 0) que.push_back(v);
            }
        }
        reverse(all(top));
        vi dp(sz(t));
        int now = 0;
        for (auto ch: s) {
            int c = ch - st;
            now = t[now].nxt[c];
            dp[now]++;
        }
        for (int u: top) {
            int fa = t[u].fail;
            if (fa == -1) continue;
            dp[fa] += dp[u];
        }
        return dp;
    }
};