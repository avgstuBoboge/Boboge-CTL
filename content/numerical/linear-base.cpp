/**
 * Author: Boboge adapted from Yuhao Yao.
 * Date: 23-12-03
 * Description: Maximum weighted of Linear Base of vector space $\mathbb{Z}_2^{d}$.
 *  $T$ is the type of vectors and $Z$ is the type of weights.
 *  $w[i]$ is the non-negative weight of a[i]. Keep $w[]$ zero to use unweighted Linear Base.
 * Time: O(d \cdot \frac{d}{w}) for $insert$; O(d^2 \cdot \frac{d}{w}) for union; O(d \cdot \frac{d}{w}) for $kth()$.
 * Status: tested on https://codeforces.com/contest/1100/problem/F, https://ac.nowcoder.com/acm/contest/11194/E, https://codeforces.com/gym/102156/problem/D, https://ac.nowcoder.com/acm/contest/884/B.
 */
template<int d, class T = bitset<d>, class Z = int>
struct LB {
    vector<T> a; /// start-hash
    vector<Z> w;

    T &operator[](int i) const { return (T &) a[i]; }

    LB() : a(d), w(d) {}

    // insert x. return 1 if the base is expanded.
    int insert(T x, Z val = 0) {
        for (int i = d - 1; i >= 0; --i) {
            if (x[i]) {
                if (a[i] == 0) {
                    a[i] = x;
                    w[i] = val;
                    return 1;
                } else if (val > w[i]) {
                    swap(a[i], x);
                    swap(w[i], val);
                }
                x ^= a[i];
            }
        }
        return 0;
    } /// end-hash

    // View vectors as binary numbers. Then calculate the minimum number we can get if we add vectors from linear base (with weight at least $val$) to $x$.
    T ask_min(T x, Z val = 0) { /// start-hash
        for (int i = d - 1; i >= 0; --i) {
            if (x[i] && w[i] >= val) x ^= a[i]; // change x[i] to x[i] == 0 to ask maximum value we can get.
        }
        return x;
    } /// end-hash

    // Compute the union of two bases.
    friend LB operator+(LB l, const LB &r) { /// start-hash
        for (int i = d - 1; i >=0; --i) {
            l.insert(r[i], r.w[i]);
        }
        return l;
    } /// end-hash

    // Returns the k-th smallest number spanned by vectors of weight at least $val$. k starts from 0.
    T kth(unsigned long long k, Z val = 0) { /// start-hash
        int N = 0;
        for (int i = 0; i < d; ++i) {
            N += (a[i] != 0 && w[i] >= val);
        }
        if (k >= (1ull << N)) return -1; // return -1 if k is too large.
        T res = 0;
        for (int i = d - 1; i >= 0; --i) {
            if (a[i] != 0 && w[i] >= val) {
                --N;
                auto bit = k >> N & 1;
                if (res[i] != bit) res ^= a[i];
            }
        }
        return res;
    } /// end-hash
};