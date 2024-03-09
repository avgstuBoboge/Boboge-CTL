/**
 * Author: Boboge
 * Description: calculate binom(n, m) % p
 *  It is used when $p$ is not large but $n, m$ are large.
 *  Usually we use $Z$ as template parameter.
 * Time: O(p) for preprosessing and O(\log_p n) for one query.
 * Status: tested on https://www.luogu.com.cn/problem/P3807.
 */
 Z binom(i64 n, i64 m) {
     Z ret = 1;
     while (n || m) {
         i64 a = n % mod, b = m % mod;
         if (a < b) return 0;
         ret *= fact.fac[a] * fact.inv[b] * fact.inv[a - b];
         n /= mod;
         m /= mod;
     }
     return ret;
 }
