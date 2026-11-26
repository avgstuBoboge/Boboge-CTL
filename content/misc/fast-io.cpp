/**
 * Author: Yuhao Yao
 * Date: 22-10-25
 * Description: Fast Read for int / long long.
 * Status: tested on https://ac.nowcoder.com/acm/contest/33187/J.
 */
namespace fastIO  {
	const int BUF_SIZE = 1 << 15;
	char buf[BUF_SIZE], *s = buf, *t = buf;
	inline char fetch() {
		if (s == t) {
			t = (s = buf) + fread(buf, 1, BUF_SIZE, stdin);
			if (s == t) return EOF;
		}
		return *s++;
	}
	template<class T> inline void read(T &x) {
		bool sgn = 1;
		T a = 0;
		char c = fetch();
		while (!isdigit(c)) sgn ^= (c == '-'), c = fetch();
		while (isdigit(c)) a = a * 10 + (c - '0'), c = fetch();
		x = sgn ? a : -a;
	}
}
