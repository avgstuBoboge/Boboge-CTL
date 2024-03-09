/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Undoable Disjoint Union Set for set ${0, ..., N - 1}$. 
 *  Fill in struct $T$, function $join$ as well as choosing proper type $Z$ for $glob$ and remember to initialize it.
 *  Use $top = top()$ to get a save point; use $undo(top)$ to go back to the save point.
 * Usage: 
 *  UndoDSU dsu(n);
 *  ...
 *  int top = dsu.top(); // get a save point.
 *  ... // do merging and other calculating here.
 *  dsu.undo(top); // get back to the save point.
 * Time: Amortized O(\log N).
 * Status: tested on https://ac.nowcoder.com/acm/contest/33193/I.
 */

struct UndoDSU {
    using Z = int; // choose some proper type (Z) for global variable glob.
    struct T {
        int siz;

        // add things you want to maintain here.
        T(int ind = 0) : siz(1) {
            // initialize what you add here.
        }
    };

    Z glob;
private:
    void join(T &a, const T &b) {
        a.siz += b.siz;
        // maintain the things you added to struct T.
        // also remember to maintain glob here.
    }

    vector<int> fa;
    vector<T> ts;
    vector<tuple<int, int, T, Z>> sta;
public:
    UndoDSU(int n) : fa(n), ts(n) {
        iota(fa.begin(), fa.end(), 0);
        iota(ts.begin(), ts.end(), 0);
        // remember initializing glob here.
    }

    int getcomp(int x) {
        while (x != fa[x]) x = fa[x];
        return x;
    }

    bool merge(int x, int y) {
        int fx = getcomp(x), fy = getcomp(y);
        if (fx == fy) return 0;
        if (ts[fx].siz < ts[fy].siz) swap(fx, fy);
        sta.emplace_back(fx, fy, ts[fx], glob);
        fa[fy] = fx;
        join(ts[fx], ts[fy]);
        return 1;
    }

    int top() { return sta.size(); }

    void undo(int top) {
        while (sta.size() > top) {
            auto &[x, y, dat, g] = sta.back();
            fa[y] = y;
            ts[x] = dat;
            glob = g;
            sta.pop_back();
        }
    }
};