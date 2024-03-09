/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-11
 * Description: Suffix Array with sparse table answering lcp of suffices.
 * Usage: SA suf(s); // $s$ can be string or vector.
 * Time: O(|s| \log |s|) for construction. O(1) per query.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/B, https://codeforces.com/gym/102994/problem/D, https://ac.nowcoder.com/acm/contest/33195/D, https://www.luogu.com.cn/problem/P4094, https://www.luogu.com.cn/problem/P7769.
 */

#include "suffix-array.cpp"

struct SA_lcp : SA {
    vector<vector<int>> st;

    template<class T>
    SA_lcp(const T &s): SA(s) {
        assert(n > 0);
        int k = __lg(n);
        st.assign(k + 1, vector<int>(n));
        st[0] = h;
        st[0].push_back(0); // just to make st[0] of size n.
        for (int i = 1; i <= k; ++i) {
            for (int j = 0; j + (1 << i) <= n; ++j) {
                st[i][j] = min(st[i - 1][j], st[i - 1][j + (1 << (i - 1))]);
            }
        }
    }

    // return lcp(suff_i, suff_j) for i != j.
    int lcp(int i, int j) {
        if (i == n || j == n) return 0;
        assert(i != j);
        int l = rank[i], r = rank[j];
        if (l > r) swap(l, r);
        int k = __lg(r - l);
        return min(st[k][l], st[k][r - (1 << k)]);
    }
};