/**
 * Author: Yuhao Yao
 * Date: 22-10-23
 * Description: Cartesian Tree of array $as$ (of distinct values) of length $N$. Node with smaller depth has smaller value. Set $gr = 1$ to have top with the greatest value. Returns the root of Cartesian Tree, left sons of nodes and right sons of nodes. ($-1$ means no left son / right son.)
 * Time: O(N) for construction.
 * Status: Tested on https://qoj.ac/contest/695/problem/1857, https://codeforces.com/gym/103371/problem/M, https://codeforces.com/contest/1718/problem/D.
 */

 template<class T>
 auto CartesianTree(const vector<T> &as, int gr = 0) {
     int n = (int) as.size();
     vector<int> ls(n, -1), rs(n, -1), stk;
     for (int i = 0; i < n; ++i) {
         while (!stk.empty() && ((as[i] < as[stk.back()]) ^ gr)) {
             ls[i] = stk.back();
             stk.pop_back();
         }
         if (!stk.empty()) rs[stk.back()] = i;
         stk.push_back(i);
     }
     return make_tuple(stk[0], ls, rs);
 }
