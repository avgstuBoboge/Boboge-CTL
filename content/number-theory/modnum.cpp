/**
 * Author: Boboge adapted from jiangly
 * Date: 23-09-07
 * Description: Modular integer with $mod \le 2^{30} - 1$. Note that there are several advantages to use this code:
   1. You do not need to keep writing $\%\, mod$;
   2. It is good to use this struct when doing Gaussian Elimination / Fast Walsh-Hadamard Transform;
   3. Sometimes the input number is greater than $mod$ and this code handles it.
  Do not write things like $mint\{1 / 3\}.pow(10)$ since $1 / 3$ simply equals $0$.
  Do not write things like $mint\{a * b\}$ where $a$ and $b$ are int since you might first have integer overflow.
 * Usage: ...
 * Status: tested on https://ac.nowcoder.com/acm/contest/33191/F.
 */
template<class T>
T power(T a, int b) {
    T res = 1;
    for (; b; b /= 2, a *= a) {
        if (b % 2) {
            res *= a;
        }
    }
    return res;
}

template<int P>
struct mint {
    int x;

    constexpr mint() : x{} {}

    constexpr mint(i64 x) : x{norm(x % getMod())} {}

    static int Mod;

    constexpr static int getMod() {
        if (P > 0) {
            return P;
        } else {
            return Mod;
        }
    }

    constexpr static void setMod(int Mod_) {
        Mod = Mod_;
    }

    constexpr int norm(int x) const {
        if (x < 0) {
            x += getMod();
        }
        if (x >= getMod()) {
            x -= getMod();
        }
        return x;
    }

    constexpr int val() const {
        return x;
    }

    explicit constexpr operator int() const {
        return x;
    }

    constexpr mint operator-() const {
        mint res;
        res.x = norm(getMod() - x);
        return res;
    }

    constexpr mint inv() const {
        assert(x != 0);
        return power(*this, getMod() - 2);
    }

    constexpr mint &operator*=(mint rhs) &{
        x = 1LL * x * rhs.x % getMod();
        return *this;
    }

    constexpr mint &operator+=(mint rhs) &{
        x = norm(x + rhs.x);
        return *this;
    }

    constexpr mint &operator-=(mint rhs) &{
        x = norm(x - rhs.x);
        return *this;
    }

    constexpr mint &operator/=(mint rhs) &{
        return *this *= rhs.inv();
    }

    friend constexpr mint operator*(mint lhs, mint rhs) {
        mint res = lhs;
        res *= rhs;
        return res;
    }

    friend constexpr mint operator+(mint lhs, mint rhs) {
        mint res = lhs;
        res += rhs;
        return res;
    }

    friend constexpr mint operator-(mint lhs, mint rhs) {
        mint res = lhs;
        res -= rhs;
        return res;
    }

    friend constexpr mint operator/(mint lhs, mint rhs) {
        mint res = lhs;
        res /= rhs;
        return res;
    }
};

template<>
int mint<0>::Mod = 998244353;

using Z = mint<0>;