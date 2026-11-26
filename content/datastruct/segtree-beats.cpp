/**
 * Author: Boboge, adapted from ZAwei
 * Date: 23-02-01
 * License: MIT
 * Description: Adapt lazy-segtree.cpp for range add/chmin, sum, max and historical max.
 * Usage: Paste the three sections below into a copy of lazy-segtree.cpp as indicated.
 *  vector<Info> init(all(a)); segTree<Info, Tag> seg(init);
 *  Min(l, r, x), Add(l, r, x), ask(l, r).sum / .mx / .his.
 *  Indices are 0-based, all intervals inclusive. This file contains member snippets.
 * Time: Amortized O(\log^2 N) per update.
 * Status: tested
 */
// 1. Define before segTree; keep its apply and pull unchanged.
constexpr int inf = 1e9;
struct Info {
    int mx = -inf, sec = -inf, mx_cnt = 0;
    i64 sum = 0;
    int his = -inf, len = 0, dir = 2; // Maximum in left / right / both children.
    Info() = default;
    Info(int x) : mx(x), mx_cnt(1), sum(x), his(x), len(1) {}
    friend Info operator+(Info x, Info y) {
        if (!x.len) return y;
        if (!y.len) return x;
        Info ret;
        ret.dir = x.mx > y.mx ? 0 : x.mx < y.mx ? 1 : 2;
        if (x.mx < y.mx) swap(x, y);
        ret.mx = x.mx;
        ret.mx_cnt = x.mx_cnt;
        if (x.mx == y.mx) ret.mx_cnt += y.mx_cnt, ret.sec = max(x.sec, y.sec);
        else ret.sec = max(x.sec, y.mx);
        ret.sum = x.sum + y.sum;
        ret.his = max(x.his, y.his);
        ret.len = x.len + y.len;
        return ret;
    }
};
struct Tag {
    // Net addition and maximum prefix addition, for maxima / other elements.
    int add_mx = 0, add_sec = 0, his_mx = 0, his_sec = 0;
};
void infoApply(Info &x, int, int, const Tag &k) {
    x.his = max(x.his, x.mx + k.his_mx);
    x.mx += k.add_mx;
    x.sec += k.add_sec;
    x.sum += 1LL * k.add_mx * x.mx_cnt + 1LL * k.add_sec * (x.len - x.mx_cnt);
}
void tagApply(Tag &t, int, int, const Tag &k) {
    t.his_mx = max(t.his_mx, t.add_mx + k.his_mx);
    t.his_sec = max(t.his_sec, t.add_sec + k.his_sec);
    t.add_mx += k.add_mx;
    t.add_sec += k.add_sec;
}
// 2. Replace private push; dir is recorded by pull, before pending updates.
void push(int i, int l, int r) {
    Tag lt = tag[i], rt = tag[i];
    if (info[i].dir == 0) rt.add_mx = rt.add_sec, rt.his_mx = rt.his_sec;
    else if (info[i].dir == 1) lt.add_mx = lt.add_sec, lt.his_mx = lt.his_sec;
    apply(lson, lt);
    apply(rson, rt);
    tag[i] = {};
}
// 3. Add public members before the #undef lines; reuse rangeApply/rangeAsk.
void Min(int ql, int qr, int x) {
    auto dfs = [&](auto &dfs, int i, int l, int r) {
        if (qr < l || r < ql || info[i].mx <= x) return;
        if (ql <= l && r <= qr && info[i].sec < x) {
            int d = x - info[i].mx;
            apply(i, l, r, Tag{d, 0, d, 0});
            return;
        }
        push(i, l, r);
        dfs(dfs, lson);
        dfs(dfs, rson);
        pull(i);
    };
    dfs(dfs, 1, 0, n - 1);
}
void Add(int l, int r, int x) { rangeApply(l, r, Tag{x, x, x, x}); }
Info ask(int l, int r) { return rangeAsk(l, r); }
