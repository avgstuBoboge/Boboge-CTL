#include<ext/pb_ds/assoc_container.hpp>
#include<ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using Oset = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; // if null_type does not work, then use null_mapped_type instead.
// order_of_key(x) returns the number of elements which are smaller than x. (quite like lower_bound.)
// find_by_order(x) returns the x-th smallest element.
// Change to less_equal<T> if you want multiset. Write ms.erase(prev(ms.lower_bound(key))) to erase an element. Be careful to use this.
