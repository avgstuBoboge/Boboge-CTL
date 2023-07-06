/**
 * Author: Boboge
 * Date: 23-02-08
 * Description: get $\varphi(n)$: the number of $i$ that $i < n, gcd(i, n) = 1$
 * Time: O(\sqrt{n}).
 * Status: from oi-wiki.
*/
template<class T>
T euler_phi(T n) {
    T phi = n;
    for (T i = 2; i * i <= n; ++i) {
        if (n % i == 0) {
            phi = phi / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    }
    if (n > 1) phi = phi / n * (n - 1);
    return phi;
}
