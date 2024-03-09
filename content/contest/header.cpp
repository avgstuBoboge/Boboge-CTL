#include <bits/stdc++.h>

using namespace std;

#define dbg(x...) \
    do { \
        cout << #x << " -> "; \
        err(x); \
    } while (0)

void err() {
    cout << endl;
}

template<class T, class... Ts>
void err(T arg, Ts &... args) {
    cout << arg << ' ';
    err(args...);
}

using ll = long long;
using ld = long double;
using ull = unsigned long long;
using i128 = __int128;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(nullptr);
	return 0;
}
