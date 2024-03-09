/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Persistent Segment Tree of range $[0, N]$. Point apply and thus no lazy propogation.
 *  Always define a global $apply$ function to tell segment tree how you apply modification.
 *  Combine is set as + operation. If you use your own struct, then please define constructor and + operation.
 *  In constructor, $q$ is the number of $pointApply$ you will use.
 *  Usage: Point Add and Range Sum. Range $k$-th.
 *  void apply(int \&a, int b) { a += b; } // global
 *  ...
 *  PersistSegtree<int> pseg(10, 1); // len = 10 and 1 update.
 *  int rt = 0; // empty node.
 *  int new_rt = pseg.pointApply(rt, 9, 1); // add 1 to last position (position 9).
 *  int sum = pseg.rangeAsk(new_rt, 7, 9); // ask the sum between position 7 and 9, wrt version new_rt.
 * Time: O(\log N) per operation.
 * Status: tested on https://codeforces.com/contest/1479/problem/D, https://www.luogu.com.cn/problem/P7361, https://www.luogu.com.cn/problem/P4094.
 */

void apply(int &a, int b) { a += b; }

template<class Info>
struct persistSegTree {
#define mid ((l + r) >> 1)
    struct node {
        Info info;
        int ls{}, rs{};
    };
    vector<node> t;
    int n;

    persistSegTree(int n, int q) : n(n), t(1) {
        assert(n >= 0);
        t.reserve(q * (__lg(n + 1) + 2) + 10);
    }

    void up(int x) {
        int ls = t[x].ls;
        int rs = t[x].rs;
        t[x].info = t[ls].info + t[rs].info;
    }

    template<class... T>
    int update(int rt, int pos, const T &... val) {
        function<void(int &, int, int)> dfs = [&](int &id, int l, int r) {
            t.push_back(t[id]);
            id = (int) t.size() - 1;
            if (l == r) {
                ::apply(t[id].info, val...);
                return;
            }
            if (pos <= mid) dfs(t[id].ls, l, mid);
            else dfs(t[id].rs, mid + 1, r);
            up(id);
        };
        dfs(rt, 0, n);
        return rt;
    }

    //on a single version
    Info rangeAsk(int rt, int ql, int qr) {
        Info res{};
        function<void(int, int, int)> dfs = [&](int id, int l, int r) {
            if (id == 0 || qr < l || r < ql) return;
            if (ql <= l && r <= qr) {
                res = res + t[id].info;
                return;
            }
            dfs(t[id].ls, l, mid);
            dfs(t[id].rs, mid + 1, r);
        };
        dfs(rt, 0, n);
        return res;
    }

    // lower_bound on prefix sums of difference between two versions.
    int lower_bound(int rt_l, int rt_r, Info k) {
        Info sum{};
        function<int(int, int, int, int)> dfs = [&](int x, int y, int l, int r) {
            if (l == r) {
                return sum + t[y].info - t[x].info >= k ? l : l + 1;
            }
            int lx = t[x].ls, rx = t[x].rs;
            int ly = t[y].ls, ry = t[y].rs;
            Info s = t[ly].info - t[lx].info;
            if (sum + s >= k) {
                return dfs(lx, ly, l, mid);
            } else {
                sum = sum + s;
                return dfs(rx, ry, mid + 1, r);
            }
        };
        return dfs(rt_l, rt_r, 0, n);
    }

#undef mid
};