/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-12
 * Description: Sparse Table of an array of length $N$.
 * Time: O(N \log N) for construction, O(1) per query.
 * Status: tested on https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M.
 */

template<class T, class F = function<T(const T &, const T &)>>
class ST {
    int n;
    vector<vector<T>> st;
    const F func;
public:
    ST(const vector<T> &init, const F &f) : n(init.size()), func(f) {
        assert(n > 0);
        st.assign(__lg(n) + 1, vector<T>(n));
        st[0] = init;
        for (int j = 1; j < st.size(); ++j) {
            for (int i = 0; i + (1 << j) <= n; ++i) {
                st[j][i] = func(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
            }
        }
    }

    T ask(int l, int r) {
        assert(0 <= l && l <= r && r < n);
        int k = __lg(r - l + 1);
        return func(st[k][l], st[k][r - (1 << k) + 1]);
    }
};