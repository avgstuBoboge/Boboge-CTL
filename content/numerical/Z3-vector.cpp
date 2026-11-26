/**
 * Author: Yuhao Yao.
 * Date: 22-10-25
 * Description: vector in $\mathbb{Z}_3$.
 * Time: O(d / w) for +, -, * and /.
 * Status: tested on https://codeforces.com/gym/102394/problem/G.
 */
template<int d>
struct v3 {
	bitset<d> a[3]; /// start-hash
	v3() { a[0].set(); }
	void set(int pos, int x) {
		rep(i, 0, 2) a[i][pos] = (i == x);
	}
	int operator [](int i) const {
		if (a[0][i]) return 0;
		else if (a[1][i]) return 1;
		else return 2;
	}
	v3 operator +(const v3 &rhs) const {
		v3 res;
		res.a[0] = (a[0] & rhs.a[0]) | (a[1] & rhs.a[2]) | (a[2] & rhs.a[1]);
		res.a[1] = (a[0] & rhs.a[1]) | (a[1] & rhs.a[0]) | (a[2] & rhs.a[2]);
		res.a[2] = (~res.a[0] & ~res.a[1]);
		return res;
	}
	v3 operator -(const v3 &rhs) const {
		v3 tmp = rhs;
		swap(tmp.a[1], tmp.a[2]);
		return *this + tmp;
	}
	v3 operator *(int rhs) const {
		if (rhs % 3 == 0) return v3{};
		else {
			auto res = *this;
			if (rhs % 3 == 2) swap(res.a[1], res.a[2]);
			return res;
		}
	}
	v3 operator /(int rhs) const {
		assert(rhs % 3 != 0); 
		return *this * rhs;
	} /// end-hash
	friend string to_string(const v3 &a) {
		string s;
		rep(i, 0, d - 1) s.push_back('0' + a[i]);
		return s;
	}
};
