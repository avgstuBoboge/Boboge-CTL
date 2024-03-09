/**
 * Author: Yuhao Yao
 * Date: 22-10-24
 * Description: Matrix struct. 
 *  $Gaussian(C)$ eliminates the first $C$ columns and returns the rank of matrix induced by first $C$ columns.
 *  $inverse()$ gives the inverse of the matrix.
 *  $SolveLinear(A, b)$ solves linear system $A x =  b$ for matrix $A$ and vector $b$.
 *  Besides, you need function $isZero$ for your template $T$.
 * Usage: For SolveLinear():
 *  bool isZero(double x) { return abs(x) <= 1e-9; } // global
 *  Matrix<double> A(3, 4);
 *  vector<double> b(3);
 *  ... // set values for A and b.
 *  vector<double> xs = SolveLinear(A, b);
 * Time: O(n m \min\{n, m\}) for Gaussian, inverse and SolveLinear.
 * Status: inverse() tested on https://ac.nowcoder.com/acm/contest/33187/J; 
 *  SolveLinear() tested on https://www.luogu.com.cn/problem/P6125.
 */
template<class T>
struct Matrix {
    using Mat = Matrix; /// start-hash
    using Vec = vector<T>;

    vector<Vec> a;

    Matrix(int n, int m) {
        assert(n > 0 && m > 0);
        a.assign(n, Vec(m));
    }

    Matrix(const vector<Vec> &a) : a(a) {
        assert(!a.empty() && !a[0].empty());
    }

    Vec &operator[](int i) const { return (Vec &) a[i]; }
    /// end-hash

    Mat operator+(const Mat &b) const {
        int n = a.size(), m = a[0].size();
        Mat c(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                c[i][j] = a[i][j] + b[i][j];
            }
        }
        return c;
    }

    Mat operator-(const Mat &b) const {
        int n = a.size(), m = a[0].size();
        Mat c(n, m);
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                c[i][j] = a[i][j] - b[i][j];
            }
        }
        return c;
    }

    Mat operator*(const Mat &b) const {
        int n = a.size(), m = a[0].size(), l = b[0].size();
        assert(m == b.a.size());
        Mat c(n, l);
        for (int i = 0; i < n; ++i) {
            for (int k = 0; k < m; ++k) {
                for (int j = 0; j < l; ++j) {
                    c[i][j] += a[i][k] * b[k][j];
                }
            }
        }
        return c;
    }

    Mat tran() const {
        int n = a.size(), m = a[0].size();
        Mat res(m, n);
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                res[j][i] = a[i][j];
        return res;
    }

    // Eliminate the first C columns, return the rank of matrix induced by first C columns.
    int Gaussian(int C) { /// start-hash
        int n = a.size(), m = a[0].size(), rk = 0;
        assert(C <= m);
        for (int c = 0; c < C; ++c) {
            int id = rk;
            while (id < n && ::isZero(a[id][c])) id++;
            if (id == n) continue;
            if (id != rk) swap(a[id], a[rk]);
            T tmp = a[rk][c];
            for (auto &x: a[rk]) x /= tmp;
            for (int i = 0; i < n; ++i) {
                if (i != rk) {
                    T fac = a[i][c];
                    for (int j = 0; j < m; ++j) {
                        a[i][j] -= fac * a[rk][j];
                    }
                }
            }
            rk++;
        }
        return rk;
    } /// end-hash

    Mat inverse() const { /// start-hash
        int n = a.size(), m = a[0].size();
        assert(n == m);
        auto b = *this;
        for (int i = 0; i < n; ++i)
            b[i].resize(n * 2, 0), b[i][n + i] = 1;
        assert(b.Gaussian(n) == n);
        for (auto &row: b.a) row.erase(row.begin(), row.begin() + n);
        return b;
    } /// end-hash

    //return [true, solution] if there's any solution, if the solution is not unique, rk < n
    friend pair<bool, Vec> SolveLinear(Mat A, const Vec &b) { /// start-hash
        int n = A.a.size(), m = A[0].size();
        assert(b.size() == n);
        for (int i = 0; i < n; ++i) {
            A[i].push_back(b[i]);
        }
        int rk = A.Gaussian(m);
        for (int i = rk; i < n; ++i) {
            if (::isZero(A[i].back()) == 0) {
                return {0, Vec{}};
            }
        }
        Vec res(m);
        for (int i = rk - 1; i >= 0; --i) {
            T x = A[i][m];
            int last = -1;
            for (int j = m - 1; j >= 0; --j) {
                if (::isZero(A[i][j]) == 0) {
                    x -= A[i][j] * res[j];
                    last = j;
                }
            }
            if (last != -1) res[last] = x;
        }
        return {1, res};
    } /// end-hash
};