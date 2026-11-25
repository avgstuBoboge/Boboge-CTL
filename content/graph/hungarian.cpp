/**
 * Author: Yuhao Yao
 * Date: 23-02-03
 * Description: Given a complete bipartite graph $G = (L \cup R, E)$, where $|L| \le |R|$, Finds minimum weighted perfect matching of $L$. Returns the matching (a vector of pair<int, int>).
 *  $ws[i][j]$ is the weight of the edge from $i$-th vertex in $L$ to $j$-th vertex in $R$.
 *  Not sure how to choose safe $T$ since I can not give a bound on values in $lp$ and $rp$. Seems safe to always use \textbf{long long}.
 * Time: O(|L|^2 |R|).
 * Status: tested. Seems to be fast enough. Tested on https://www.luogu.com.cn/problem/P6577, https://codeforces.com/gym/101635/problem/G, https://codeforces.com/gym/101194/problem/J.
 */
template<class T = i64, T INF = numeric_limits<T>::max()>
vector<pii> Hungarian(const vector<vector<T>> &ws) {
    int L = sz(ws), R = L == 0 ? 0 : sz(ws[0]);
    vector<T> lp(L), rp(R); // left & right potential
    vi lm(L, -1), rm(R, -1); // left & right match
    rep(i, 0, L - 1)
        lp[i] = *min_element(all(ws[i]));
    auto step = [&](int src) {
        vi que{src}, pre(R, -1); // bfs que & back pointers
        vector<T> sa(R, INF); // slack array; min slack from node in que
        auto extend = [&](int j) {
            if (sa[j] == 0) {
                if (rm[j] == -1) {
                    while (j != -1) { // Augment the path
                        int i = pre[j];
                        rm[j] = i;
                        swap(lm[i], j);
                    }
                    return 1;
                } else que.push_back(rm[j]);
            }
            return 0;
        };
        rep(ind, 0, L - 1) { // BFS to new nodes
            int i = que[ind];
            rep(j, 0, R - 1) {
                if (j == lm[i]) continue;
                T off = ws[i][j] - lp[i] - rp[j]; // Slack in edge
                if (sa[j] > off) {
                    sa[j] = off;
                    pre[j] = i;
                    if (extend(j)) return;
                }
            }
            if (ind == sz(que) - 1) { // Update potentials
                T d = INF;
                rep(j, 0, R - 1)
                    if (sa[j]) d = min(d, sa[j]);
                bool found = false;
                for (auto j: que) lp[j] += d;
                rep(j, 0, R - 1) {
                    if (sa[j]) {
                        sa[j] -= d;
                        if (!found) found |= extend(j);
                    } else rp[j] -= d;
                }
                if (found) return;
            }
        }
    };
    rep(i, 0, L - 1) step(i);
    vector<pii> res;
    rep(i, 0, L - 1) res.emplace_back(i, lm[i]);
    return res;
}
