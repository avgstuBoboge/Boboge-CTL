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
        std::array<int, C> nxt;
        int fail;
        int cnt;

        node() {
            nxt.fill(-1);
            fail = -1;
            cnt = 0;
        }
    };

    std::vector<node> t;

    AhoCorasick() : t(1) {}

    int insert(const std::string &s) {
        int now = 0;
        for (auto ch: s) {
            int c = ch - st;
            if (t[now].nxt[c] == -1) {
                t.emplace_back();
                t[now].nxt[c] = (int) t.size() - 1;
            }
            now = t[now].nxt[c];
        }
        t[now].cnt++;
        return now;
    }

    void build() {
        std::vector<int> que{0};
        for (int ind = 0; ind < que.size(); ++ind) {
            int now = que[ind], fa = t[now].fail;
            for (int c = 0; c < C; ++c) {
                int &v = t[now].nxt[c];
                int u = fa == -1 ? 0 : t[fa].nxt[c];
                if (v == -1) v = u;
                else t[v].fail = u, que.push_back(v);
            }
            if (fa != -1) t[now].cnt += t[fa].cnt;
        }
    }

    std::vector<int> query(const std::string &s) {
        std::vector<int> ind(t.size());
        std::vector<std::vector<int>> adj(t.size());
        std::vector<int> que;
        for (int i = 0; i < t.size(); ++i) {
            if (t[i].fail != -1) {
                ind[i]++;
                adj[t[i].fail].push_back(i);
            }
        }
        for (int i = 0; i < t.size(); ++i) {
            if (ind[i] == 0) que.push_back(i);
        }
        std::vector<int> top;
        for (int i = 0; i < que.size(); ++i) {
            int u = que[i];
            top.push_back(u);
            for (int v: adj[u]) {
                if (--ind[v] == 0) que.push_back(v);
            }
        }
        std::reverse(top.begin(), top.end());
        std::vector<int> dp(t.size());
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