/**
 * Author: Boboge
 * Date: 23-02-08
 * Description: Double Hash of a string.
 * Usage: StringHash ha(s), index start from 0;
 * Time: O(|s|) preprocessing, O(1) query.
 * Status: tested on https://www.luogu.com.cn/problem/P3370.
 */
using pii = pair<int, int>;

constexpr pii mod = {1000000007, 1000050131};
constexpr pii base = {73, 131};

pii operator*(const pii &a, const pii &b) {
    return {1ll * a.first * b.first % mod.first, 1ll * a.second * b.second % mod.second};
}

pii operator+(const pii &a, const pii &b) {
    return {(a.first + b.first) % mod.first, (a.second + b.second) % mod.second};
}

pii operator-(const pii &a, const pii &b) {
    return {(mod.first + a.first - b.first) % mod.first, (mod.second + a.second - b.second) % mod.second};
}

struct StringHash {
    int n;
    vector<pii> hs, pw;

    StringHash(const string &s) : n(s.size()), hs(n + 1), pw(n + 1) {
        pw[0] = {1, 1};
        for (int i = 1; i <= n; ++i) pw[i] = pw[i - 1] * base;
        for (int i = 0; i < n; ++i) hs[i + 1] = hs[i] * base + pii(s[i], s[i]);
    }

    pii get(int l, int r) { return hs[r + 1] - hs[l] * pw[r + 1 - l]; }
};