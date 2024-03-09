/**
 * Author: Boboge adapted from Yuhao Yao.
 * Date: 23-02-11
 * Description: Intersection of two unweighted linear bases.
 *  $T$ should be of length at least $2d$.
 * Time: O(d^2 \cdot \frac{d}{w}).
 * Status: tested at https://ac.nowcoder.com/acm/contest/884/B.
 */
#include "linear-base.cpp"
template<int d, class T = bitset<d * 2>>
LB<d, T> intersect(LB<d, T> a, const LB<d, T> &b) {
    LB<d, T> res;
    for (int i = 0; i < d; ++i) if (a[i] != 0) a[i][d + i] = 1;
    T msk(string(d, '1'));
    for (int i = 0; i < d; ++i) {
        T x = a.ask_min(b[i]);
        if ((x & msk) != 0) {
            a.insert(x);
        } else {
            T y = 0;
            for (int j = 0; j < d; ++j) if (x[d + j]) y ^= a[j];
            res.insert(y & msk);
        }
    }
    return res;
}