/**
 * Author: MAOoo
 * Date: 23-02-08
 * Description: a fast gcd algo based on bit operations.
 * Time: O(\log n).
 * Status: tested.
*/
template<class T>
constexpr int ctz(T x) { return sizeof(T) & 8 ? __builtin_ctzll(x) : __builtin_ctz(x); }

template<class T>
constexpr T gcd(T x, T y) {
    if (!x || !y) return x ^ y;
    int kx = ctz(x);
    x >>= kx;
    int ky = ctz(y);
    y >>= ky;
    for (;; y >>= ctz(y)) {
        if (x > y) swap(x, y);
        y -= x;
        if (!y) return x << min(kx, ky);
    }
}