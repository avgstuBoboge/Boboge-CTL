/**
 * Author: Yuhao Yao
 * Date: 23-03-29
 * Description: Number Theoretic Transform. 
 *  class $T$ should have static function $getMod()$ to provide the $mod$. We usually just use $modnum$ as the template parameter.
 *  To keep the code short we just set the primitive root as $3$. However, it might be wrong when $mod \ne 998244353$. Here are some commonly used $mod$s and the corresponding primitive root.\\
 *  $g \to  mod~(\max \log(n))$:\\
 *  3 $\to$ 104857601 (22), 167772161 (25), 469762049 (26), 998244353 (23), 1004535809 (21);\\
 *  10 $\to$ 786433 (18);\\
 *  31 $\to$ 2013265921 (27).
 * Usage: const int mod = 998244353;
 *  using Mint = Z<mod>; // Z is modnum struct.
 *  ...
 *  FFT<Mint> ntt(3); // use 3 as primitive root.
 *  vector<Mint> as = ntt.conv(vector<Mint>{1, 2, 3}, vector<Mint>{2, 3, 4});
 * Time: O(N \log N).
 * Status: tested on https://ac.nowcoder.com/acm/contest/33186/H, https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence.
 */
template<class mint = Z>
struct FFT {
    static void dft(std::vector<mint> &as, int is_inv) { // is_inv == 1 -> idft.
        static int mod = mint::getMod();
        static mint root = 0;
        if (root == 0) {
            root = 2;
            while (root.pow((mod - 1) / 2) == 1)
                root += 1; // it is not necessarily a primitive root but lowbit(mod - 1) divides its order.
        }

        int n = as.size();
        assert(__builtin_popcount(n) == 1);
        static std::vector<int> r;
        if (r.size() != n) {
            r.resize(n);
            for (int i = 1; i < n; ++i) {
                r[i] = (r[i >> 1] >> 1) | ((i & 1) << (__builtin_ctz(n) - 1));
            }
        }

        for (int i = 1; i < n; ++i) if (r[i] > i) std::swap(as[i], as[r[i]]);
        for (int step = 1; step < n; step <<= 1) {
            mint zeta = root.pow((mod - 1) / (step << 1));
            if (is_inv) zeta = mint{1} / zeta;
            std::vector<mint> ws(step);
            ws[0] = 1;
            for (int i = 1; i < step; ++i) ws[i] = ws[i - 1] * zeta;
            for (int i = 0; i < n; i += step << 1) {
                for (int j = 0; j < step; ++j) {
                    auto x = as[i + j], y = as[i + j + step] * ws[j];
                    as[i + j] = x + y;
                    as[i + j + step] = x - y;
                }
            }
        }

        if (is_inv == 1) {
            auto inv = mint{1} / n;
            for (auto &x: as) x *= inv;
        }
    }

    static std::vector<mint> conv(const std::vector<mint> &as, const std::vector<mint> &bs) {
        if (std::min(as.size(), bs.size()) <= 128) {
            std::vector<ll> cs(as.size() + bs.size() - 1);
            for (int i = 0; i < as.size(); ++i)
                for (int j = 0; j < bs.size(); ++j)
                    cs[i + j] += (int) (as[i] * bs[j]);
            return {cs.begin(), cs.end()};
        } else {
            int n = as.size() + bs.size() - 1, n2 = 1 << std::__lg(n * 2 - 1);
            auto xs = as, ys = bs;
            xs.resize(n2, 0);
            ys.resize(n2, 0);
            dft(xs, 0);
            if (as == bs) ys = xs;
            else dft(ys, 0);
            for (int i = 0; i < n2; ++i) xs[i] *= ys[i];
            dft(xs, 1);
            xs.resize(n);
            return xs;
        }
    }
};