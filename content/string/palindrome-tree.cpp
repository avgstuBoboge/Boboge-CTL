/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Given string $s = s_0...s_{n - 1}$, build the palindrom tree (automaton) for $s$. Each state of the automaton corresponds to a palindrome substring of $s$.
 *  $t[i].fail$ is the state which is a border of state $i$. Note that $t[i].fail < i$ holds.
 * Usage: Palindrome pt(s); // $s$ can be string or vector.
 * Time: O(|s|).
 * Status: tested on https://www.luogu.com.cn/problem/P3649, https://www.luogu.com.cn/problem/P4762, https://www.luogu.com.cn/problem/P5685, https://www.luogu.com.cn/problem/P5555, https://codeforces.com/gym/100548/problem/G, https://ac.nowcoder.com/acm/contest/884/I, https://ac.nowcoder.com/acm/contest/886/C.
 */

struct PalindromeTree {
    struct node {
        map<int, int> nxt;
        int fail, len;
        int cnt;

        node(int fail, int len) : fail(fail), len(len) {
            cnt = 0;
        }
    };

    vector<node> t;

    template<class T>
    PalindromeTree(const T &s) {
        int n = s.size();
        t.emplace_back(-1, -1); // Odd root -> state 0.
        t.emplace_back(0, 0); // Even root -> state 1.

        int now = 0;
        auto ins = [&](int pos) {
            auto get = [&](int i) {
                while (pos == t[i].len || s[pos - 1 - t[i].len] != s[pos]) i = t[i].fail;
                return i;
            };
            int c = s[pos];
            now = get(now);
            if (t[now].nxt.count(c) == 0) {
                int q = now == 0 ? 1 : t[get(t[now].fail)].nxt[c];
                t.emplace_back(q, t[now].len + 2);
                t[now].nxt[c] = (int) t.size() - 1;
            }
            now = t[now].nxt[c];
            t[now].cnt++;
        };
        for (int i = 0; i < n; ++i) {
            ins(i);
        }
    }
};