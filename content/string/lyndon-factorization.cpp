/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-07
 * Description: Lyndon factorization of string $s$. Return a vector of pairs $(l, r)$, representing substring $s_l...s_r$.
 * To use Lyndon solve minimal-string problem, find some $[l, r]$ that $l \le n - 1 and r \ge n - 1$
 * Time: O(|s|).
 * Status: tested on https://www.luogu.com.cn/problem/P6114, https://www.luogu.com.cn/problem/P1368.
 */
vector<pair<int, int>> duval(const string &s) {
    int n = s.size(), i = 0;
    vector<pair<int, int>> res;
    while (i < n) {
        int j = i + 1, k = i;
        while (j < n && s[k] <= s[j]) {
            if (s[k] < s[j]) k = i;
            else k++;
            j++;
        }
        while (i <= k) {
            res.emplace_back(i, i + j - k - 1);
            i += j - k;
        }
    }
    return res;
}