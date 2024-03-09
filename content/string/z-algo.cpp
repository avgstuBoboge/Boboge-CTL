/**
 * Author: Boboge
 * Date: 23-02-07
 * Description: Given string $s = s_0...s_{n - 1}$, compute array $z$ where $z[i]$ is the lcp of $s_0...s_{n - 1}$ and $s_{i}...s_{n - 1}$.
 *  Use function $cal(t)$ (where $|t| = m$) to calculate the lcp of of $s_0...s_{n - 1}$ and $t_{i}...t_{m - 1}$ for each $i$.
 * Usage: z_function z_s(s); // $s$ can be string or vector.
 * Time: O(|s|) for precalculation and O(|t|) for matching.
 * Status: tested on https://www.codechef.com/submit/SSTRPREF2, https://www.luogu.com.cn/problem/P5410.
 */
template<class T>
struct z_function {
    const T s; /// start-hash
    int n;
    vector<int> z;

    z_function(const T &s) : s(s), n(s.size()), z(n) {
        z[0] = n;
        int l = 0, r = 0;
        for (int i = 1; i < n; ++i) {
            z[i] = max(0, min(z[i - l], r - i));
            while (i + z[i] < n && s[z[i]] == s[i + z[i]]) z[i]++;
            if (i + z[i] > r) {
                l = i;
                r = i + z[i];
            }
        }
    } /// end-hash

    vector<int> cal(const T &t) { /// start-hash
        int m = t.size();
        vector<int> res(m);
        int l = 0, r = 0;
        for (int i = 0; i < m; ++i) {
            res[i] = max(0, min(i - l < n ? z[i - l] : 0, r - i));
            while (i + res[i] < m && s[res[i]] == t[i + res[i]]) res[i]++;
            if (i + res[i] > r) {
                l = i;
                r = i + res[i];
            }
        }
        return res;
    } /// end-hash
};