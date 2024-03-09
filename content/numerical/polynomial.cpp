/**
 * Author: Yuhao Yao
 * Date: 23-03-28
 * Description: Basic polynomial struct. Usually we use $modnum$ as template parameter. $inv(k)$ gives the inverse of the polynomial $mod~ x^k$ (by default $k$ is the highest power plus one).
 * Status: 
 *  inv() tested on https://www.luogu.com.cn/problem/P4238, https://judge.yosupo.jp/problem/kth_term_of_linearly_recurrent_sequence.
 *  ln() tested on https://www.luogu.com.cn/problem/P4725.
 *  exp() tested on https://www.luogu.com.cn/problem/P4726, https://judge.yosupo.jp/problem/exp_of_formal_power_series.
 */
template<class T = Z, class FFT = FFT<T>>
struct Poly : vector<T> {
    using poly = Poly;
    using vector<T>::vector;

    Poly(const vector<T> &vec) : vector<T>(vec) {}

    friend poly &operator+=(poly &as, const poly &bs) { /// start-hash
        if (as.size() < bs.size()) as.resize(bs.size(), 0);
        for (int i = 0; i < bs.size(); ++i) as[i] += bs[i];
        return as;
    }

    friend poly operator+(const poly &as, const poly &bs) {
        auto cs = as;
        return cs += bs;
    }

    friend poly &operator-=(poly &as, const poly &bs) {
        if (as.size() < bs.size()) as.resize(bs.size(), 0);
        for (int i = 0; i < bs.size(); ++i) as[i] -= bs[i];
        return as;
    }

    friend poly operator-(const poly &as, const poly &bs) {
        auto cs = as;
        return cs -= bs;
    }

    friend poly &operator*=(poly &as, const poly &bs) {
        as = FFT::conv(as, bs);
        return as;
    }

    friend poly operator*(const poly &as, const poly &bs) {
        auto cs = as;
        return cs *= bs;
    }

    friend poly &operator*=(poly &as, const T &b) {
        for (auto &x: as) x *= b;
        return as;
    }

    friend poly operator*(const poly &as, const T &b) {
        auto cs = as;
        return cs *= b;
    }

    friend poly operator*(const T &a, const poly &bs) {
        auto cs = bs;
        return cs *= a;
    }

    /// end-hash
    poly modxk(int k) const {
        return poly(this->begin(), this->begin() + min((int) this->size(), k));
    }

    poly derivative() const {
        assert(!this->empty());
        auto as = poly(this->begin() + 1, this->end());
        for (int i = 0; i < as.size(); ++i) as[i] *= i + 1;
        if (as.empty()) as = poly{0};
        return as;
    }

    poly integral() const {
        poly as(this->size() + 1);
        for (int i = 1; i < as.size(); ++i) as[i] = (*this)[i - 1] / i;
        return as;
    }

    poly inv(int k = 0) const { /// start-hash
        const poly &as = *this;
        assert(!as.empty());
        if (k == 0) k = as.size();
        poly res{T{1} / as[0]};
        for (int m = 2; m < k * 2; m <<= 1) {
            res = res * 2 - (res * res * as.modxk(m)).modxk(m);
        }
        res.resize(k);
        return res;
    } /// end-hash

    poly ln(int k = 0) const {
        poly as = *this;
        if (k > 0) as.resize(k);
        assert(!as.empty() && as[0] == T{1}); // be cautious when T is float or double.
        return (as.derivative() * as.inv()).modxk(as.size() - 1).integral();
    }

    poly exp(int k = 0) const {
        const poly &as = *this;
        if (k == 0) k = as.size();
        assert(k > 0 && (as.empty() || as[0] == T{0})); // be cautious when T is float or double.
        poly res{1};
        for (int m = 2; m < k * 2; m <<= 1) {
            res = res - (res * (res.ln(m) - as.modxk(m))).modxk(m);
        }
        res.resize(k);
        return res;
    }

    poly pow(int k) const {
        int d = 0;
        while ((*this)[d] == 0) d++;
        T co = (*this)[d];
        poly f = Poly(this->begin() + d, this->end());
        f *= 1 / co;
        poly fk = (k * f.ln()).exp();
        fk *= power(co, k);
        int rem_siz = this->size();
        if (1LL * d * k >= rem_siz) return Poly(rem_siz, 0);
        reverse(fk.begin(), fk.end());
        for (int i = 0; i < d * k; ++i) fk.emplace_back(0);
        reverse(fk.begin(), fk.end());
        fk.modxk(rem_siz);
        return fk;
    }
};