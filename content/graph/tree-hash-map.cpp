/**
 * Author: Boboge adapted from Heltion
 * Date: 23-02-06
 * Description: return the hash value of every subtree using map. It is always correct but may be too slow.
 * Time: O(N \log N).
 * Status: tested on https://uoj.ac/problem/763
 */
vector<int> tree_hash(vector<vector<int>> &adj, int rt = 0) {
    int n = adj.size();
    vector<int> hash_value(n);
    map<vector<int>, int> mp;
    auto dfs = [&](auto dfs, int u, int fa) -> int {
        vector<int> vec;
        for (int v: adj[u]) {
            if (v == fa) continue;
            vec.push_back(dfs(dfs, v, u));
        }
        sort(vec.begin(), vec.end());
        if (!mp.contains(vec)) mp[vec] = mp.size();    
        return hash_value[u] = mp[vec];
    };
    dfs(dfs, rt, -1);
    return hash_value;
}