/**
 * Author: Yuhao Yao
 * Date: 22-10-30
 * Description: Suffix Automaton of a given string $s$. (Using map to store sons makes it 2$\sim$3 times slower but it should be fine in most cases.)
 *  $len$ is the length of the longest substring corresponding to the state. 
 *  $fa$ is the father in the prefix tree. Note that fa[i] < i doesn't hold.
 *  $occ$ is $0/1$, indicating if the state contains a prefix of the string $s$. One can do a dfs/bfs to compute for each substring, how many times it occurs in the whole string $s$. (See function $calOccurrence$ for bfs implementation.)
 *  root is set as 0.
 * Usage: SAM sam(s); // $s$ can be string or vector<int>.
 * Time: O(|s|).
 * Status: tested on https://ac.nowcoder.com/acm/contest/884/I, https://ac.nowcoder.com/acm/contest/33188/H, https://codeforces.com/gym/101194/problem/F, https://nanti.jisuanke.com/t/A2018, https://darkbzoj.cc/problem/3238, https://nanti.jisuanke.com/t/A1623, https://www.spoj.com/problems/NSUBSTR/en/, https://codeforces.com/contest/235/problem/C.
 */

template<class T>
struct SAM {
    struct node { /// start-hash
        map<int, int> nxt; // change this if it is slow.
        int fa, len;
        int occ, pos; // # of occurrence (as prefix) & endpos.
        node(int fa = -1, int len = 0) : fa(fa), len(len) {
            occ = pos = 0;
        }
    };

    T s;
    int n;
    vector<node> t;
    vector<int> at; // at[i] = the state at which the i-th prefix of s is.

    SAM(const T &s) : s(s), n(s.size()), at(n) {
        t.emplace_back();
        int last = 0; // create root.
        auto ins = [&](int i, int c) {
            int now = last;
            t.emplace_back(-1, t[now].len + 1);
            last = (int) t.size() - 1;
            t[last].occ = 1;
            t[last].pos = i;
            at[i] = last;
            while (now != -1 && t[now].nxt.count(c) == 0) {
                t[now].nxt[c] = last;
                now = t[now].fa;
            }
            if (now == -1) t[last].fa = 0; // root is 0.
            else {
                int p = t[now].nxt[c];
                if (t[p].len == t[now].len + 1) t[last].fa = p;
                else {
                    auto tmp = t[p];
                    tmp.len = t[now].len + 1;
                    tmp.occ = 0; // do not copy occ.
                    t.push_back(tmp);
                    int np = (int) t.size() - 1;

                    t[last].fa = t[p].fa = np;
                    while (now != -1 && t[now].nxt.count(c) && t[now].nxt[c] == p) {
                        t[now].nxt[c] = np;
                        now = t[now].fa;
                    }
                }
            }
        };
        for (int i = 0; i < n; ++i) {
            ins(i, s[i]);
        }
    } /// end-hash

    void calOccurrence() { /// start-hash
        vector<int> sum(n + 1), que(t.size());
        for (auto &it: t) sum[it.len]++;
        for (int i = 1; i < n; ++i)
            sum[i] += sum[i - 1];
        for (int i = 0; i < t.size(); ++i)
            que[--sum[t[i].len]] = i;
        reverse(que.begin(), que.end());
        for (auto now: que) if (now != 0) t[t[now].fa].occ += t[now].occ;
    } /// end-hash

    vector<vector<int>> ReversedPrefixTree() { /// start-hash
        vector<vector<int>> g(t.size());
        for (int now = 1; now < t.size(); ++now)
            g[t[now].fa].push_back(now);
        for (int now = 0; now < t.size(); ++now) {
            sort(g[now].begin(), g[now].end(), [&](int i, int j) {
                return s[t[i].pos - t[now].len] < s[t[j].pos - t[now].len];
            });
        }
        return g;
    } /// end-hash
};