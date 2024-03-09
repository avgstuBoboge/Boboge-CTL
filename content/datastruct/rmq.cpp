/**
 * Author: Boboge adapted from Antti Roeyskoe
 * Date: 22-06-15
 * License: MIT
 * Source: self
 * Description: range minimum query data structure with low memory and fast queries
 * Time: O(N) preprocessing, O(1) query.
 * Usage: RMQ rmq(vec); rmq.get(l, r);
 * Status: tested on https://www.luogu.com.cn/record/101544572, not really sure it is O(n) preprocessing or not
 */

int firstBit(u64 x) { return __builtin_ctzll(x); }

int lastBit(u64 x) { return 63 - __builtin_clzll(x); }

// O(n) preprocessing, O(1) RMQ data structure.
template<class T>
class RMQ {
private:
    const int H = 6; // Block size is 2^H
    const int B = 1 << H;
    vector<T> vec; // Original values
    vector<u64> mins; // Min bits
    vector<int> tbl; // sparse table
    int n, m;

    // Get index with minimum value in range [a, a + len) for 0 <= len <= B
    int getShort(int a, int len) const {
        return a + lastBit(mins[a] & (-1ULL >> (64 - len)));
    }

    int minInd(int ia, int ib) const {
        return vec[ia] < vec[ib] ? ia : ib;
    }

public:
    RMQ(const vector<T> &vec_) : vec(vec_), mins(vec_.size()) {
        n = vec.size();
        m = (n + B - 1) >> H;

        // Build sparse table
        int h = lastBit(m) + 1;
        tbl.resize(h * m);
        for (int j = 0; j < m; ++j) tbl[j] = j << H;
        for (int i = 0; i < n; ++i) tbl[i >> H] = minInd(tbl[i >> H], i);
        for (int j = 1; j < h; ++j) {
            for (int i = j * m; i < (j + 1) * m; ++i) {
                int i2 = min(i + (1 << (j - 1)), (j + 1) * m - 1);
                tbl[i] = minInd(tbl[i - m], tbl[i2 - m]);
            }
        }
        // Build min bits
        u64 cur = 0;
        for (int i = n - 1; i >= 0; --i) {
            for (cur <<= 1; cur > 0; cur ^= cur & -cur) {
                if (vec[i + firstBit(cur)] < vec[i]) break;
            }
            cur |= 1;
            mins[i] = cur;
        }
    }

    int argmin(int a, int b) const {
        ++b; // to make the range inclusive
        int len = min(b - a, B);
        int ind1 = minInd(getShort(a, len), getShort(b - len, len));

        int ax = (a >> H) + 1;
        int bx = (b >> H);
        if (ax >= bx) return ind1;
        else {
            int h = lastBit(bx - ax);
            int ind2 = minInd(tbl[h * m + ax], tbl[h * m + bx - (1 << h)]);
            return minInd(ind1, ind2);
        }
    }

    int get(int a, int b) const { return vec[argmin(a, b)]; }
};