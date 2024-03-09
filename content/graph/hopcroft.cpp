/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Fast bipartite matching for \textbf{bipartite} graph $G = (L \cup R, E)$. Edges $E$ should be described as pairs such that pair $(x, y)$ means that there is an edge between the $x$-th vertex in $L$ and the $y$-th vertex in $R$. You can also get a vertex cover of a bipartite graph easily. 
 * Time: O(|E| \sqrt{|L| + |R|}).
 * Status: vertex cover correctness is tested on https://ac.nowcoder.com/acm/contest/885/F.
 */
struct Hopcroft {
    int L, R; /// start-hash
    vector<int> lm, rm; // record the matched vertex for each vertex on both sides.
    vector<int> ldis, rdis; // put it here so you can get vertex cover easily.

    Hopcroft(int L, int R, const vector<pair<int, int>> &es) : L(L), R(R), lm(L, -1), rm(R, -1) {
        vector<vector<int>> g(L);
        for (auto [x, y]: es) g[x].push_back(y);
        while (1) {
            ldis.assign(L, -1);
            rdis.assign(R, -1);
            bool ok = 0;
            vector<int> que;
            for (int i = 0; i < L; ++i) {
                if (lm[i] == -1) {
                    que.push_back(i);
                    ldis[i] = 0;
                }
            }
            for (int ind = 0; ind < que.size(); ++ind) {
                int i = que[ind];
                for (auto j: g[i])
                    if (rdis[j] == -1) {
                        rdis[j] = ldis[i] + 1;
                        if (rm[j] != -1) {
                            ldis[rm[j]] = rdis[j] + 1;
                            que.push_back(rm[j]);
                        } else ok = 1;
                    }
            }
            if (ok == 0) break;
            vector<int> vis(R); // changing to static does not speed up.
            auto find = [&](auto &dfs, int i) -> int {
                for (auto j: g[i])
                    if (vis[j] == 0 && rdis[j] == ldis[i] + 1) {
                        vis[j] = 1;
                        if (rm[j] == -1 || dfs(dfs, rm[j])) {
                            lm[i] = j;
                            rm[j] = i;
                            return 1;
                        }
                    }
                return 0;
            };
            for (int i = 0; i < L; ++i) {
                if (lm[i] == -1) find(find, i);
            }
        }
    } /// end-hash

    vector<int> getMatch() { return lm; } // returns lm.

    pair<vector<int>, vector<int>> vertex_cover() { /// start-hash
        vector<int> lvc, rvc;
        for (int i = 0; i < L; ++i) {
            if (ldis[i] == -1) lvc.push_back(i);
        }
        for (int j = 0; j < R; ++j) {
            if (rdis[j] != -1) rvc.push_back(j);
        }
        return {lvc, rvc};
    } /// end-hash
};