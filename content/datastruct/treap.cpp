/**
 * Author: Boboge, adapted from Antti Röyskö
 * Date: 2023-02-03
 * Description: A Treap with lazy tag support. Default behaviour supports join, split, reverse and sum.
 * Time: All updates are O(log N)
 * Usage: Treap::join(treap1, treap2),  auto [x, y] = Treap::split(treap1)
 * Status: tested on https://www.luogu.com.cn/record/101544554
 */

mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());

int rand() { return uniform_int_distribution<int>()(rng); }

struct Treap {
    const int pri;
    Treap *l = nullptr, *r = nullptr;
    i64 val, sum;
    int siz = 1, flip = 0;

    void update() {
        siz = 1 + getSiz(l) + getSiz(r);
        sum = val + getSum(l) + getSum(r);
    }

    void push() {
        if (flip) {
            swap(l, r);
            reverse(l);
            reverse(r);
            flip = 0;
        }
    }

    Treap(i64 v) : val(v), sum(v), pri(rand()) {}

    ~Treap() {
        delete l;
        delete r;
    }

    static int getSiz(Treap *x) { return x ? x->siz : 0; }

    static i64 getSum(Treap *x) { return x ? x->sum : 0; }

    static void reverse(Treap *x) { if (x) x->flip ^= 1; }

    static Treap *join(Treap *a, Treap *b) {
        if (!a || !b) return a ? a : b;
        Treap *res = (a->pri < b->pri ? a : b);
        res->push();
        if (res == a) a->r = join(a->r, b);
        else b->l = join(a, b->l);
        res->update();
        return res;
    }

    // Split the treap into a left and right part, the left of size "le_siz"
    static pair<Treap *, Treap *> split(Treap *x, int le_siz) {
        if (!le_siz || !x) return {0, x};
        x->push();
        Treap *oth;
        int rem = le_siz - getSiz(x->l) - 1;
        if (rem < 0) {
            tie(oth, x->l) = split(x->l, le_siz);
            x->update();
            return {oth, x};
        } else {
            tie(x->r, oth) = split(x->r, rem);
            x->update();
            return {x, oth};
        }
    }
};