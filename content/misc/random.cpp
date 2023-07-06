std::mt19937 rng(std::chrono::steady_clock::now().time_since_epoch().count());
template<class T>
T rand(T a, T b) { return uniform_int_distribution<T>(a, b)(rng); }
template<class T>
T rand() { return uniform_int_distribution<T>()(rng); }
// std::shuffle(perm.begin(), perm.end(), rng);