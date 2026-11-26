/**
 * Author: Antti Röyskö
 * Date: 22-08-13
 * Description: Modular integer w/ Montgomery multiplication.
	Multiplications are about 5 times faster than a non-fixed modulo, and about 2.5 times faster than a constant modulo.
	Note that the input number has to be between 0 and P-1!
 * Usage: Declare a global Montgomery as "Montgomery mt" (or "Montgomery mt(MOD)" with a fixed constant modulo MOD)
	and include the line "using Mint = Z<mt>". Set the modulo as "mt = Montgomery(mod)".
 * Status: submitted to a few problems, but needs more testing! In particular, we got a very odd TLE on nowcoder.
 */
#pragma once
struct Montgomery {
	constexpr static ull modPow(ull a, ull b, ull c) {
		ull r = 1;
		for (; b; b /= 2) {
			if (b & 1) r = (r*a) % c;
			a = (a*a) % c;
		}
		return r;
	}
	static constexpr ull R = (ull)1 << 32;
	uint P, P2, RR, MC; // Modulo, 2^64 mod P, x for which xP = -1 mod 2^32
	Montgomery(uint m = (uint)1e9 + 7) : P(m), P2(2*m), RR((R%m)*R % m), MC((R * modPow(R % m, m-2, m) - 1) / m) {}
	uint mult(uint a, uint b) const {
		ull t = (ull)a * b; // < 4P
		ull k = (uint)t * MC; // < 2^32
		return (t + k * P) >> 32; // < 2P, Exact division!
	}
};
template<const Montgomery& mt> struct Z {
	private:
		uint x;
	public:
		/// start-hash
		Z(ll a = 0) : x(mt.mult(a, mt.RR)) { assert(a >= 0); }
		explicit operator int() { uint res = mt.mult(x, 1); return (res < mt.P ? res : res - mt.P); }
		static int getP() { return mt.P; }
		Z& operator +=(Z b) { x += b.x; if (x >= mt.P2) x -= mt.P2; return *this; }
		Z& operator -=(Z b) { if (x < b.x) x += mt.P2; x -= b.x; return *this; }
		Z& operator *=(Z b) { x = mt.mult(x, b.x); return *this; }
		friend Z operator +(Z a, Z b) { return a += b; }
		friend Z operator -(Z a, Z b) { return a -= b; }
		friend Z operator *(Z a, Z b) { return a *= b; }
		bool operator ==(Z b) const { return (x > mt.P ? x - mt.P : x) == (b.x > mt.P ? b.x - mt.P : b.x); }
		/// end-hash
		// the following are needed for fft and polynomial operations.
		/// start-hash
		Z pow(ll k) const {
			Z res = 1, a = *this;
			for (; k; k >>= 1, a = a * a) if (k & 1) res = res * a;
			return res;
		}
		Z& operator /=(Z b) {
			assert(b.x != 0);
			*this = *this * b.pow(mt.P - 2);
			return *this;
		}
		friend Z operator /(Z a, Z b) { return a /= b; }
		/// end-hash
		friend string to_string(Z a) { return to_string((int)a); }
};
