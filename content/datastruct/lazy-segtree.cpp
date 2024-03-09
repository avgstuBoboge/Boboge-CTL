/**
 * Author: Yuhao Yao
 * Date: 23-02-06
 * Description: Segment tree with lazy propogation.
 * Usage: Always define global apply functions (for both Info and Tag) to tell segment tree how you apply modification.
 *  Combine is set as plus so if you just let T be numerical type then you have range sum in the info and as range query result. To have something different, say rangeMin, define a struct with constructer and + operation.
 *  Define in Global: infoApply(\&info, l, r, Tag), tagApply(\&tag, l, r, val)
 * Time: O(\log N) per operation.
 * Status: tested on https://www.luogu.com.cn/problem/P3384
 */
template<class Info, class Tag>
class segTree {
#define ls i << 1
#define rs i << 1 | 1
#define mid ((l + r) >> 1)
#define lson ls, l, mid
#define rson rs, mid + 1, r

    int n;
    vector<Info> info;
    vector<Tag> tag;
public:
    segTree(const vector<Info> &init) : n(init.size()) {
        assert(n > 0);
        info.resize(4 << __lg(n));
        tag.resize(4 << __lg(n));
        auto build = [&](auto dfs, int i, int l, int r) {
            if (l == r) {
                info[i] = init[l];
                return;
            }
            dfs(dfs, lson);
            dfs(dfs, rson);
            pull(i);
        };
        build(build, 1, 0, n - 1);
    }

private:
    void pull(int i) { info[i] = info[ls] + info[rs]; }

    template<class... T>
    void apply(int i, int l, int r, const T &... val) {
        ::infoApply(info[i], l, r, val...);
        ::tagApply(tag[i], l, r, val...);
    }

    void push(int i, int l, int r) {
        if (tag[i] == Tag{}) return;
        apply(lson, tag[i]);
        apply(rson, tag[i]);
        tag[i] = {};
    }

public:
    template<class... T>
    void rangeApply(int ql, int qr, const T &... val) {
        auto dfs = [&](auto dfs, int i, int l, int r) {
            if (qr < l || r < ql) return;
            if (ql <= l && r <= qr) {
                apply(i, l, r, val...);
                return;
            }
            push(i, l, r);
            dfs(dfs, lson);
            dfs(dfs, rson);
            pull(i);
        };
        dfs(dfs, 1, 0, n - 1);
    }

    Info rangeAsk(int ql, int qr) {
        Info res{};
        auto dfs = [&](auto dfs, int i, int l, int r) {
            if (qr < l || r < ql) return;
            if (ql <= l && r <= qr) {
                res = res + info[i];
                return;
            }
            push(i, l, r);
            dfs(dfs, lson);
            dfs(dfs, rson);
        };
        dfs(dfs, 1, 0, n - 1);
        return res;
    }

#undef rson
#undef lson
#undef mid
#undef rs
#undef ls
};