/**
 * Author: Boboge adapted from jiangly and Yuhao Yao
 * Date: 23-09-07
 * Description: Modular integer, $1 < P < 2^{30}$. Division requires prime $P$ and a nonzero divisor.
 *  Comparisons use residues in $[0, P)$. Convert to mint before division or potentially overflowing multiplication.
 * Usage: using Z = mint<998244353>;
 * Status: tested
 */
template<class T>
constexpr T power(T a, i64 b) {
    assert(b >= 0);
    T res = 1;
    for (; b; b >>= 1, a *= a) if (b & 1) res *= a;
    return res;
}
template<int P>
struct mint {
    static_assert(1 < P && P < (1 << 30));
    int x;
    constexpr mint(i64 a = 0) : x(a % P) { if (x < 0) x += P; }
    static constexpr int getMod() { return P; }
    constexpr int norm(int a) const { if (a < 0) a += P; if (a >= P) a -= P; return a; }
    constexpr int val() const { return x; }
    explicit constexpr operator int() const { return x; }
    constexpr mint operator-() const { return mint(-x); }
    constexpr mint pow(i64 b) const { return power(*this, b); }
    constexpr mint inv() const { assert(x != 0); return pow(P - 2); }
    constexpr mint &operator+=(mint b) & { x = norm(x + b.x); return *this; }
    constexpr mint &operator-=(mint b) & { x = norm(x - b.x); return *this; }
    constexpr mint &operator*=(mint b) & { x = 1LL * x * b.x % P; return *this; }
    constexpr mint &operator/=(mint b) & { return *this *= b.inv(); }
    friend constexpr mint operator+(mint a, mint b) { return a += b; }
    friend constexpr mint operator-(mint a, mint b) { return a -= b; }
    friend constexpr mint operator*(mint a, mint b) { return a *= b; }
    friend constexpr mint operator/(mint a, mint b) { return a /= b; }
    friend constexpr bool operator==(mint a, mint b) { return a.x == b.x; }
    friend constexpr bool operator!=(mint a, mint b) { return a.x != b.x; }
    friend constexpr bool operator<(mint a, mint b) { return a.x < b.x; }
    friend constexpr bool operator>(mint a, mint b) { return b < a; }
    friend constexpr bool operator<=(mint a, mint b) { return !(b < a); }
    friend constexpr bool operator>=(mint a, mint b) { return !(a < b); }
    friend ostream &operator<<(ostream &os, mint a) { return os << a.x; }
    friend istream &operator>>(istream &is, mint &a) {
        i64 x;
        if (is >> x) a = mint(x);
        return is;
    }
    friend string to_string(mint a) { return std::to_string(a.x); }
};
template<int P>
constexpr bool isZero(mint<P> a) { return a.val() == 0; }
using Z = mint<998244353>;
