mt19937_64 mt(chrono::steady_clock::now().time_since_epoch().count());
template<class T>
T rand(T a, T b) { return uniform_int_distribution<T>(a, b)(mt); }
template<class T>
T rand() { return uniform_int_distribution<T>()(mt); }
// shuffle(perm.begin(), perm.end(), mt);