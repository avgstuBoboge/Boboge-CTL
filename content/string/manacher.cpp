/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-08
 * Description: Manacher Algorithm for finding all palindrome subtrings of $s = s_0...s_{n - 1}$. $s$ can actually be string or vector (say vector<int>).
 *  For returned vector $len$, $len[i * 2] = r$ means that $s_{i - r + 1}...s_{i + r - 1}$ is the maximal palindrome centered at position $i$.
 *  $len[i * 2 + 1] = r$ means that $s_{i - r + 1}...s_{i + r}$ is the maximal palindrome centered between position $i$ and $i + 1$.
 * Usage: vi rs = Manacher(s); // $s$ can be string or vector.
 * Time: O(|s|).
 * Status: tested on https://www.luogu.com.cn/problem/P3805, https://qoj.ac/problem/4844, https://www.luogu.com.cn/problem/P6216, https://www.luogu.com.cn/problem/P4555.
 */

template<class T>
vector<int> Manacher(const T &s) {
    int n = s.size(), j = 0;
    vector<int> len(n * 2 - 1, 1);
    for (int i = 1; i < n * 2 - 1; ++i) {
        int p = i / 2, q = i - p, r = (j + 1) / 2 + len[j] - 1;
        len[i] = r < q ? 0 : min(r - q + 1, len[j * 2 - i]);
        while (p > len[i] - 1 && q + len[i] < n && s[p - len[i]] == s[q + len[i]]) len[i]++;
        if (q + len[i] - 1 > r) j = i;
    }
    return len;
}