/**
 * Author: Yuhao Yao
 * Date: 22-10-26
 * Description: Check if $n$ has a primitive root. Only $2$, $4$, $p^k$ and $2p^k$ have primitive roots (where $p$ is some odd prime).
 * Time: O(\log n).
 * Status: tested on https://www.luogu.com.cn/problem/P6091.
 */
bool hasPrimitiveRoot(i64 n) {
    assert(n > 1);
    if (n % 4 == 0) return n == 4;
    if (n % 2 == 0) n /= 2;
    vector<i64> ps;
    for (i64 i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            ps.push_back(i);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) ps.push_back(n);
    return ps.size() < 2;
}
