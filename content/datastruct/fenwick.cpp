/**
 * Author: Boboge
 * Date: 23-02-01
 * License: MIT
 * Description: Fenwick tree with built in binary search. Can be used as a indexed set. 
 * Fenwick<int> t(n), index $\in$ [0, n]
 * Time: O(\log N).
 * Usage: ??
 * Status: tested
 */

template<typename T>
struct Fenwick {
    int n;
    vector<T> t;

    Fenwick(int n) : n(n), t(n + 1) {};

    void update(int x, T v) {
        for (++x; x <= n; x += x & -x) t[x] += v;
    }

    T query(int x) {
        T ret{};
        for (++x; x; x -= x & -x) ret += t[x];
        return ret;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }

    // Assuming prefix sums are non-decreasing, finds last i s.t. get(i) <= v
    int search(T v) {
        int res = 0;
        for (int h = 1 << 30; h; h >>= 1) {
            if ((res | h) < t.size() && t[res | h] <= v) {
                res |= h;
                v -= t[res];
            }
        }
        return res - 1;
    }
};
