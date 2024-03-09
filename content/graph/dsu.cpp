/**
 * Author: Boboge
 * Date: 23-02-03
 * Description: Disjoint set union. $merge(x, y)$ merges components which $x$ and $y$ are in respectively and returns $1$ if $x$ and $y$ are in different components.
 * Time: amortized O(\alpha(M, N)) where $M$ is the number of operations. Almost constant in competitive programming.
 */

struct DSU {
    vector<int> f;

    DSU(int n) : f(n + 1, -1) {};

    int find(int x) {
        return f[x] < 0 ? x : f[x] = find(f[x]);
    }

    bool merge(int x, int y) {
        x = find(x);
        y = find(y);
        if (x == y) return false;
        if (f[x] > f[y]) swap(x, y);
        f[x] += f[y];
        f[y] = x;
        return true;
    }

    int siz(int x) {
        return -f[find(x)];
    }
};
