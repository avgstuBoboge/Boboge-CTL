/**
 * Author: Yuhao Yao
 * Date: 22-09-08
 * Description: Hash struct. $1000000007$ and $1000050131$ are good moduli.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33192/I.
 */
template<int m1, int m2>
struct Hash {
	int x, y;
	Hash(ll a, ll b): x(a % m1), y(b % m2) {
		if (x < 0) x += m1;
		if (y < 0) y += m2;
	}
	Hash(ll a = 0): Hash(a, a) {}
	using H = Hash;
	static int norm(int x, int mod) { return x >= mod ? x - mod : x < 0 ? x + mod : x; }
	friend H operator +(H a, H b) { a.x = norm(a.x + b.x, m1); a.y = norm(a.y + b.y, m2); return a; }
	friend H operator -(H a, H b) { a.x = norm(a.x - b.x, m1); a.y = norm(a.y - b.y, m2); return a; }
	friend H operator *(H a, H b) { return H{1ll * a.x * b.x, 1ll * a.y * b.y}; }
	friend bool operator ==(H a, H b) { return tie(a.x, a.y) == tie(b.x, b.y); }
	friend bool operator !=(H a, H b) { return tie(a.x, a.y) != tie(b.x, b.y); }
	friend bool operator <(H a, H b) { return tie(a.x, a.y) < tie(b.x, b.y); }
};
