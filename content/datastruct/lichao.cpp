/**
 * Author: Boboge
 * Date: 23-02-11
 * Description: Li Chao tree. Given x-coordinates, supports adding segments and computing minimum Y-coordinate at a given input x-coordinate
 * Time: O(\log ^ 2 N).
 * Usage: update(x0, x1, line) to add a segment between [x0, x1], query(x) to get the maximum number
 * Status: tested on https://www.luogu.com.cn/record/101969534.
 */
using T = double;
constexpr T eps = 1e-6;
constexpr T inf = 1e9;

int sgn(const T &a) {
    if (a < -eps) return -1;
    if (a > eps) return 1;
    return 0;
}

int cmp(const T &a, const T &b) {
    return sgn(a - b);
}

struct Line {
    T a, b;

    T eval(int x) const { return a * x + b; }
};

struct LiChao {
#define ls i << 1
#define rs i << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

    vector<int> t;
    vector<Line> lines;
    int n;

    LiChao(int n) : n(n), t(n * 4 + 10), lines{{0, -inf}} {}

    void apply(int u, int i, int l, int r) {
        int &v = t[i];
        if (cmp(lines[u].eval(mid), lines[v].eval(mid)) == 1) swap(u, v);
        int bl = cmp(lines[u].eval(l), lines[v].eval(l));
        int br = cmp(lines[u].eval(r), lines[v].eval(r));
        if (bl == 1 || (bl == 0 && u < v)) {
            apply(u, lson);
        }
        if (br == 1 || (br == 0 && u < v)) {
            apply(u, rson);
        }
    }

    void update(int ql, int qr, Line &line) {
        lines.push_back(line);
        int u = (int) lines.size() - 1;
        auto dfs = [&](auto &dfs, int i, int l, int r) {
            if (qr < l || r < ql) return;
            if (ql <= l && r <= qr) {
                apply(u, i, l, r);
                return;
            }
            dfs(dfs, lson);
            dfs(dfs, rson);
        };
        dfs(dfs, 1, 0, n - 1);
    }

    pair<T, int> query(int x) {
        auto dfs = [&](auto &dfs, int i, int l, int r) {
            auto res = make_pair(lines[t[i]].eval(x), t[i]);
            if (l == r) {
                return res;
            }
            if (x <= mid) {
                auto ret = dfs(dfs, lson);
                int b = cmp(res.first, ret.first);
                if (b == -1 || (b == 0 && ret.second < res.second)) {
                    res = ret;
                }
            } else {
                auto ret = dfs(dfs, rson);
                int b = cmp(res.first, ret.first);
                if (b == -1 || (b == 0 && ret.second < res.second)) {
                    res = ret;
                }
            }
            return res;
        };
        return dfs(dfs, 1, 0, n - 1);
    }

#undef rson
#undef lson
#undef rs
#undef ls
#undef mid
};