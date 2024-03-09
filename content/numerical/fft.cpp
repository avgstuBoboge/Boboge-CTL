/**
 * DO NOT USE THIS IF YOU CAN USE NTT :)
 * Author: Boboge adapted from Yuhao Yao
 * Date: 23-02-10
 * Description: Fast Fourier Transform. $T$ can be \textbf{double} or \textbf{long double}.
 * Usage: FFT<double> fft;
 *  auto cs = fft.conv(vector<double>{1, 2, 3}, vector<double>{3, 4, 5});
 *  vector<int> ds = fft.conv(vector<int>{1, 2, 3}, vector<int>{3, 4, 5}, 1000000007); // convolution of integers wrt arbitrary $mod \le 2^{31} - 1$. 
 * Time: O(N \log N).
 * Status: tested on https://official.contest.yandex.com/mw2020prefinals/contest/18053/problems/H/, https://judge.yosupo.jp/problem/convolution_mod_1000000007.
 */
const T pi = acos(-1);
template<class T>
struct FFT {
    using cp = complex<T>; /// start-hash
    vector<int> r;
    int n2;

    void dft(vector<cp> &a, int is_inv) { // is_inv == 1 -> idft.
        for (int i = 1; i < n2; ++i)if (r[i] > i) swap(a[i], a[r[i]]);
        for (int step = 1; step < n2; step <<= 1) {
            vector<cp> w(step);
            for (int j = 0; j < step; ++j) { // this has higher precision, compared to using the power of zeta.
                T theta = pi * j / step;
                if (is_inv) theta = -theta;
                w[j] = cp{cos(theta), sin(theta)};
            }
            for (int i = 0; i < n2; i += step << 1) {
                for (int j = 0; j < step; ++j) {
                    cp tmp = w[j] * a[i + j + step];
                    a[i + j + step] = a[i + j] - tmp;
                    a[i + j] += tmp;
                }
            }
        }
        if (is_inv) {
            for (auto &x: a) x /= n2;
        }
    }

    void pre(int n) { // set n2, r;
        int len = 0;
        for (n2 = 1; n2 < n; n2 <<= 1) len++;
        r.resize(n2);
        for (int i = 1; i < n2; ++i) r[i] = (r[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }

    template<class Z>
    vector<Z> conv(const vector<Z> &A, const vector<Z> &B) {
        int n = A.size() + B.size() - 1;
        pre(n);
        vector<cp> a(n2, 0), b(n2, 0);;
        for (int i = 0; i < A.size(); ++i) a[i] = A[i];
        for (int i = 0; i < B.size(); ++i) b[i] = B[i];
        dft(a, 0);
        dft(b, 0);
        for (int i = 0; i < n2; ++i) a[i] *= b[i];
        dft(a, 1);
        vector<Z> res(n);
        T eps = T{0.5} * (static_cast<Z>(1e-9) == 0);
        for (int i = 0; i < n; ++i) res[i] = a[i].real() + eps;
        return res;
    } /// end-hash

    vector<int> conv(const vector<int> &A, const vector<int> &B, int mod) { /// start-hash
        int M = sqrt(mod) + 0.5;
        int n = A.size() + B.size() - 1;
        pre(n);
        vector<cp> a(n2, 0), b(n2, 0), c(n2, 0), d(n2, 0);
        for (int i = 0; i < A.size(); ++i) a[i] = A[i] / M, b[i] = A[i] % M;
        for (int i = 0; i < B.size(); ++i) c[i] = B[i] / M, d[i] = B[i] % M;
        dft(a, 0);
        dft(b, 0);
        dft(c, 0);
        dft(d, 0);
        vector<int> res(n);
        auto work = [&](vector<cp> &a, vector<cp> &b, int w, int mod) {
            vector<cp> tmp(n2);
            for (int i = 0; i < n2; ++i) tmp[i] = a[i] * b[i];
            dft(tmp, 1);
            for (int i = 0; i < n; ++i) res[i] = (res[i] + (i64) (tmp[i].real() + 0.5) % mod * w) % mod;
        };
        work(a, c, 1LL * M * M % mod, mod);
        work(b, d, 1, mod);
        work(a, d, M, mod);
        work(b, c, M, mod);
        return res;
    } /// end-hash
};