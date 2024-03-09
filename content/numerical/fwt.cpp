/**
 * Author: Boboge
 * Date: 23-02-11
 * Description: Fast Walsh-Hadamard Transform of array $a$.
 * One can use it to do or/and/xor-convolution. Length of $a$ should be a power of $2$.
 * Time: O(N \log N), where $N$ is the length of $a$.
 * Status: tested on https://www.luogu.com.cn/problem/P4717.
 */

//fwt_or[i] = \sum a[j], j & i = j(j is the subset of i).
template<class T>
void fwt_or(vector<T> &a, int is_inv = 0) {
    int n = a.size();
    for (int s = 1; s < n; s <<= 1) {
        for (int i = 0; i < n; i += s << 1) {
            for (int j = 0; j < s; j++) {
                if (is_inv) a[i + j + s] -= a[i + j];
                else a[i + j + s] += a[i + j];
            }
        }
    }
}

//fwt_and[i] = \sum a[j], j & i = i(j is the superset of i)
template<class T>
void fwt_and(vector<T> &a, int is_inv = 0) {
    int n = a.size();
    for (int s = 1; s < n; s <<= 1) {
        for (int i = 0; i < n; i += s << 1) {
            for (int j = 0; j < s; j++) {
                if (is_inv) a[i + j] -= a[i + j + s];
                else a[i + j] += a[i + j + s];
            }
        }
    }
}

//don't know how it works
template<class T>
void fwt_xor(vector<T> &a, int is_inv = 0) {
    int n = a.size();
    for (int s = 1; s < n; s <<= 1) {
        for (int i = 0; i < n; i += s << 1) {
            for (int j = 0; j < s; ++j) {
                T x = a[i + j], y = a[i + j + s];
                a[i + j] = x + y;
                a[i + j + s] = x - y;
            }
        }
    }
    if (is_inv) {
        for (auto &x: a) x = x / n;
    }
}