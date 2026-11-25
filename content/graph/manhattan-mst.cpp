/**
 * Author: Botu Lyu
 * Date: 23.12.09
 * Description: Manhattan MST on 2D plane.
 * Time: O(8|V| \log |V|)
 * Status: tested on https://codeforces.com/gym/104854/problem/A
 */
auto manhattan_mst(vector<pii> ps) {
    int n = sz(ps);
    vector<array<int, 3>> es;
    rep(j, 0, 3) {
        for (auto &[x, y]: ps) {
            if (j & 1) {
                swap(x, y);
            }
            if (j == 2) {
                x = -x;
            }
        }
        vi ord(n);
        iota(all(ord), 0);
        ranges::sort(ord, [&](int i, int j) {
            return ps[i] > ps[j];
        });
        vi val(n);
        rep(i, 0, n - 1) {
            auto [x, y] = ps[i];
            val[i] = x - y;
        }
        auto vec = val;
        ranges::sort(vec);
        vec.erase(unique(all(vec)), vec.end());
        auto get = [&](int v) {
            return (int) (ranges::lower_bound(vec, v) - vec.begin());
        };
        // Min initial: {inf, -1}
        Fenwick<Min> t(sz(vec));
        rep(i, 0, n - 1) {
            int u = ord[i];
            int id = get(val[u]);
            auto [x, y] = ps[u];
            auto [_, v] = t.query(id).x;
            if (v != -1) {
                auto [x1, y1] = ps[v];
                int d = abs(x - x1) + abs(y - y1);
                es.push_back({d, u, v});
            }
            t.update(id, make_pair(x + y, u));
        }
    }
    ranges::sort(es);
    return es;
}