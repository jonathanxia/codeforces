#include <ext/pb_ds/assoc_container.hpp>
#include <lib/macros.h>

// Fast umap and fast uset (fumap and fuset)
template <typename K, typename V>
using fumap = __gnu_pbds::gp_hash_table<K, V, custom_hash>;

template <typename K>
using fuset = __gnu_pbds::gp_hash_table<K, __gnu_pbds::null_type, custom_hash>;