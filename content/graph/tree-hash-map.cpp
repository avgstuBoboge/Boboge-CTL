/**
 * Author: Boboge adapted from Heltion
 * Date: 23-02-06
 * Description: return the hash value of every subtree using map. It is always correct but may be too slow.
 * Time: O(N \log N).
 * Status: tested on https://uoj.ac/problem/763
 */
vi tree_hash(vector<vi> &g, int rt = 0) {
    int n = sz(g);
    vi hash_value(n);
    map<vi, int> mp;
    auto dfs = [&](auto dfs, int u, int fa) -> int {
        vi vec;
        for (int v: g[u]) {
            if (v == fa) continue;
            vec.push_back(dfs(dfs, v, u));
        }
        sort(all(vec));
        if (!mp.contains(vec)) mp[vec] = sz(mp);
        return hash_value[u] = mp[vec];
    };
    dfs(dfs, rt, -1);
    return hash_value;
}