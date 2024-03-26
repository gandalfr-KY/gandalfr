#pragma once

#include <ext/pb_ds/assoc_container.hpp>
#include <functional>

namespace gandalfr {

template <typename Key, typename Value, typename Hash = std::hash<Key>,
          typename Eq = std::equal_to<Key>>
using HashMap = __gnu_pbds::gp_hash_table<Key, Value, Hash, Eq>;

}
