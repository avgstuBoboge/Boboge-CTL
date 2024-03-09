/**
 * Author: Boboge, adapted from ZAwei
 * Date: 23-02-01
 * License: MIT
 * Description: Segment-tree-beats. Interval update a[i] = min(a[i], x), query sum, max, history max.
 * Time: O(\log^2 N). maybe O(\log N)
 * Usage: Min/add to update, ask to ask.
 * Status: tested on https://www.luogu.com.cn/problem/P6242
 */
constexpr int inf = 1e9;

struct segTree {
#define mid ((l + r) >> 1)
#define lson i << 1, l, mid
#define rson i << 1 | 1, mid + 1, r

    struct Tag {
        int add_mx, add_sec, his_mx, his_sec;

        Tag &operator+=(const Tag &k) {
            his_mx = max(his_mx, add_mx + k.his_mx);
            his_sec = max(his_sec, add_sec + k.his_sec);
            add_mx += k.add_mx;
            add_sec += k.add_sec;
            return *this;
        }

        friend Tag operator+(const Tag &l, const Tag &r) {
            Tag res = l;
            return res += r;
        }
    };

    vector<Tag> tag;

    struct Info {
        int mx, sec, mx_cnt;
        i64 sum;
        int his, len, dir; //0-ls 1-rs 2-eq the direction of pushdown add_mx, his_mx
        void applyTag(Tag &k) {
            his = max(his, mx + k.his_mx);
            mx += k.add_mx;
            sec += k.add_sec;
            sum += 1LL * k.add_mx * mx_cnt + 1LL * k.add_sec * (len - mx_cnt);
        }

        friend Info operator+(Info x, Info y) {
            Info ret{};
            if (x.mx > y.mx) ret.dir = 0;
            else if (x.mx < y.mx) ret.dir = 1;
            else if (x.mx == y.mx) ret.dir = 2;
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

    vector<Info> info;

    void pull(int x) {
        info[x] = info[x * 2] + info[x * 2 + 1];
    }

    void applyTag(int x, Tag &k) {
        tag[x] += k;
        info[x].applyTag(k);
    }

    void push(int x) {
        Tag ls = tag[x], rs = tag[x];
        if (info[x].dir == 0) rs.add_mx = rs.add_sec, rs.his_mx = rs.his_sec;
        else if (info[x].dir == 1) ls.add_mx = ls.add_sec, ls.his_mx = ls.his_sec;
        applyTag(x * 2, ls);
        applyTag(x * 2 + 1, rs);
        tag[x] = {};
    }

    void build(int i, int l, int r, const vector<int> &a) {
        tag[i] = {};
        if (l == r) {
            info[i].mx = a[l], info[i].sec = -inf, info[i].mx_cnt = 1, info[i].his = a[l], info[i].sum = a[l], info[i].len = 1;
            return;
        }
        build(lson, a);
        build(rson, a);
        pull(i);
    }

    void updateMin(int i, int l, int r, int ql, int qr, int mx) {
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            if (info[i].mx <= mx) return;
            if (info[i].sec < mx) {
                Tag t{mx - info[i].mx, 0, mx - info[i].mx, 0};
                applyTag(i, t);
                return;
            }
        }
        push(i);
        updateMin(lson, ql, qr, mx);
        updateMin(rson, ql, qr, mx);
        pull(i);
    }

    void updateAdd(int i, int l, int r, int ql, int qr, Tag &k) {
        if (r < ql || l > qr) return;
        if (ql <= l && r <= qr) {
            applyTag(i, k);
            return;
        }
        push(i);
        updateAdd(lson, ql, qr, k);
        updateAdd(rson, ql, qr, k);
        pull(i);
    }

    Info query(int i, int l, int r, int ql, int qr) {
        if (r < ql || l > qr) return {-inf, -inf, 0, 0, -inf, 0};
        if (ql <= l && r <= qr) return info[i];
        push(i);
        return query(lson, ql, qr) + query(rson, ql, qr);
    }

    int n;

    segTree(int n, vector<int> &a) : n(n), tag(n * 4 + 10), info(n * 4 + 10) {
        build(1, 1, n, a);
    }

    void Min(int l, int r, int mx) {
        updateMin(1, 1, n, l, r, mx);
    }

    void Add(int l, int r, int add) {
        Tag t{add, add, add, add};
        updateAdd(1, 1, n, l, r, t);
    }

    auto ask(int l, int r) {
        return query(1, 1, n, l, r);
    }

#undef lson
#undef rson
#undef mid
};
