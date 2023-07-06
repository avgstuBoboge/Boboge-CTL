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
    std::vector<T> t;

    Fenwick(int n) : n(n + 1), t(n + 2) {};

    void update(int x, T v) {
        x++;
        for (; x <= n; x += x & -x) t[x] += v;    
    }

    T query(int x) {
        x++;
        T ret{};
        for (; x; x -= x & -x) ret += t[x];
        return ret;
    }

    T query(int l, int r) {
        return query(r) - query(l - 1);
    }
};