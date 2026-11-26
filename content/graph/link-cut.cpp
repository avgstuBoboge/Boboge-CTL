/**
 * Author: Boboge, adapted from Antti Roeyskoe and the supplied pointer-based LCT
 * Description: Link-Cut tree. Vertices are 0-based; link/cut return false for invalid edges.
 *  Customize Node::update/push/reverse for path aggregates and lazy tags.
 *  For noncommutative aggregates, reverse must also reverse the aggregate.
 * Usage: LinkCutTree<Node> t; rep(i, 0, n - 1) t.emplace();
 *  t.link(u, v); t.cut(u, v); t.connected(u, v);
 *  t.expose(u, v) returns the auxiliary root for path u to v; requires connectivity.
 * Time: Amortized O(\log N) per operation.
 * Status: tested
 */
struct Node {
    Node *p = nullptr, *ch[2] = {};
    bool flip = false;
    // Add node values, path aggregates and lazy tags here.
    void reverse() {
        swap(ch[0], ch[1]);
        flip ^= 1;
        // Swap forward/backward aggregates here, if needed.
    }
    void push() {
        if (flip) {
            if (ch[0]) ch[0]->reverse();
            if (ch[1]) ch[1]->reverse();
            flip = false;
        }
        // Push other lazy tags here.
    }
    void update() {} // Pull aggregates; children may still have lazy tags.
};
template<class T>
class LinkCutTree {
    deque<T> nodes; // emplace preserves pointers to existing nodes.
    static bool isRoot(T *a) {
        return !a->p || (a->p->ch[0] != a && a->p->ch[1] != a);
    }
    static bool pos(T *a) { return a->p->ch[1] == a; }
    static void rotate(T *a) {
        T *b = a->p;
        bool d = pos(a);
        b->ch[d] = a->ch[!d];
        if (a->ch[!d]) a->ch[!d]->p = b;
        a->p = b->p;
        if (!isRoot(b)) b->p->ch[pos(b)] = a;
        a->ch[!d] = b;
        b->p = a;
        b->update();
    }
    static void splay(T *a) {
        static vector<T *> st;
        st.clear();
        for (T *b = a;; b = b->p) {
            st.push_back(b);
            if (isRoot(b)) break;
        }
        while (!st.empty()) st.back()->push(), st.pop_back();
        while (!isRoot(a)) {
            if (!isRoot(a->p)) {
                if (pos(a) == pos(a->p)) rotate(a->p);
                else rotate(a);
            }
            rotate(a);
        }
        a->update();
    }
    static void access(T *a) {
        for (T *b = a, *c = nullptr; b; c = b, b = b->p) {
            splay(b);
            b->ch[1] = c;
            b->update();
        }
        splay(a);
    }
    static void makeRoot(T *a) { access(a); a->reverse(); }
    static T *findRoot(T *a) {
        access(a);
        a->push();
        while (a->ch[0]) a = a->ch[0], a->push();
        splay(a);
        return a;
    }
public:
    template<class... Args>
    int emplace(Args&&... args) {
        nodes.emplace_back(forward<Args>(args)...);
        return sz(nodes) - 1;
    }
    T &expose(int u, int v) {
        makeRoot(&nodes[u]);
        access(&nodes[v]);
        return nodes[v];
    }
    bool connected(int u, int v) {
        if (u == v) return true;
        makeRoot(&nodes[u]);
        return findRoot(&nodes[v]) == &nodes[u];
    }
    bool link(int u, int v) {
        if (connected(u, v)) return false;
        nodes[u].p = &nodes[v];
        return true;
    }
    bool cut(int u, int v) {
        if (u == v) return false;
        T *a = &nodes[u], *b = &expose(u, v);
        if (b->ch[0] != a || a->ch[1]) return false;
        a->p = b->ch[0] = nullptr;
        b->update();
        return true;
    }
};
