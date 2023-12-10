/**
 * Author: Botu Lyu
 * Date: 23.12.09
 * Description: Manhattan MST on 2D plane.
 * Time: O(8|V| \log |V|)
 * Status: tested on https://codeforces.com/gym/104854/problem/A
 */
auto manhattan_mst(std::vector<std::pair<int, int>> ps) {
    int n = ps.size();
    std::vector<std::array<int, 3>> es;
    for (int j = 0; j < 4; ++j) {
        for (auto &[x, y]: ps) {
            if (j & 1) {
                std::swap(x, y);
            }
            if (j == 2) {
                x = -x;
            }
        }
        std::vector<int> ord(n);
        std::iota(ord.begin(), ord.end(), 0);
        std::ranges::sort(ord, [&](int i, int j) {
            return ps[i] > ps[j];
        });
        std::vector<int> val(n);
        for (int i = 0; i < n; ++i) {
            auto [x, y] = ps[i];
            val[i] = x - y;
        }
        auto vec = val;
        std::ranges::sort(vec);
        vec.erase(std::unique(vec.begin(), vec.end()), vec.end());
        auto get = [&](int v) {
            return (int) (std::ranges::lower_bound(vec, v) - vec.begin());
        };
        // Min initial: {inf, -1}
        Fenwick<Min> t((int) vec.size());
        for (int i = 0; i < n; ++i) {
            int u = ord[i];
            int id = get(val[u]);
            auto [x, y] = ps[u];
            auto [_, v] = t.query(id).x;
            if (v != -1) {
                auto [x1, y1] = ps[v];
                int d = std::abs(x - x1) + std::abs(y - y1);
                es.push_back({d, u, v});
            }
            t.update(id, std::make_pair(x + y, u));
        }
    }
    std::ranges::sort(es);
    return es;
}