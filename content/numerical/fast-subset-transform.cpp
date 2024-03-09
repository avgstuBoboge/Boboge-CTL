/**
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-11
 * Description: Fast Subtset Transform, which is also known as fast zeta transform. Length of $a$ should be a power of $2$.
 * Subset Convolution of array $a$ and $b$. Resulting array $c$ satisfies $c_z = \sum_{x, y:\, x | y = z, x \& y = 0} a_x \cdot b_y$. Length of $a$ and $b$ should be same and be a power of $2$.
 * Time: 
 * fst, O(N \log N), where $N$ is the length of $a$. 
 * subset-convolution Time: O(N \log^2 N), where $N$ is the length of $a$ and $b$.
 * Status: tested on https://www.luogu.com.cn/problem/P6097.
 */
template<class T>
void fst(vector<T> &a, int is_inv) {
    int n = a.size();
    for (int s = 1; s < n; s <<= 1) {
        for (int i = 0; i < n; ++i) {
            if (i & s) {
                if (is_inv == 0) a[i] += a[i ^ s];
                else a[i] -= a[i ^ s];
            }
        }
    }
}

template<class T>
vector<T> SubsetConv(const vector<T> &as, const vector<T> &bs) {
    int n = as.size();
    assert(n > 0 && bs.size() == n);
    int k = __lg(n);
    vector<vector<T>> ps(k + 1, vector<T>(n)), qs(ps), rs(ps);
    for (int x = 0; x < n; ++x) {
        ps[__builtin_popcount(x)][x] = as[x];
        qs[__builtin_popcount(x)][x] = bs[x];
    }
    for (auto &vec: ps) fst(vec, 0);
    for (auto &vec: qs) fst(vec, 0);
    for (int i = 0; i <= k; ++i) {
        for (int j = 0; j <= k - i; ++j) {
            for (int x = 0; x < n; ++x) {
                rs[i + j][x] += ps[i][x] * qs[j][x];
            }
        }
    }
    for (auto &vec: rs) fst(vec, 1);
    vector<T> cs(n);
    for (int x = 0; x < n; ++x) {
        cs[x] = rs[__builtin_popcount(x)][x];
    }
    return cs;
}
