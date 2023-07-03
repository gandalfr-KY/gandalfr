---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 2 \"data_structure/LRU_cache.hpp\"\n\n#include <unordered_map>\n\
    #include <list>\n\ntemplate <typename KeyType, typename ValueType>\nclass lru_cache\
    \ {\nprivate:\n    using Item = std::pair<KeyType, ValueType>;\n    using ItemList\
    \ = std::list<Item>;\n    using ItemMap = std::unordered_map<KeyType, typename\
    \ ItemList::iterator>;\n\n    ItemList item_list;\n    ItemMap item_map;\n   \
    \ size_t capacity;\n\npublic:\n    using iterator = typename ItemList::iterator;\n\
    \n    lru_cache(size_t size) : capacity(size) {}\n\n    void put(const KeyType&\
    \ key, const ValueType& value) {\n        auto found = item_map.find(key);\n \
    \       if (found != item_map.end()) {\n            item_list.erase(found->second);\n\
    \            item_map.erase(found);\n        }\n        if (item_list.size() ==\
    \ capacity) {\n            item_map.erase(item_list.front().first);\n        \
    \    item_list.pop_front();\n        }\n        item_list.push_back(std::make_pair(key,\
    \ value));\n        item_map[key] = std::prev(item_list.end());\n    }\n\n   \
    \ iterator get(const KeyType& key) {\n        auto found = item_map.find(key);\n\
    \        if (found == item_map.end()) {\n            return end();\n        }\n\
    \        item_list.splice(item_list.end(), item_list, found->second);\n      \
    \  return found->second;\n    }\n\n    iterator begin() { return item_list.begin();\
    \ }\n    iterator end() { return item_list.end(); }\n    iterator find(const KeyType&\
    \ key) {\n        auto found = item_map.find(key);\n        return found != item_map.end()\
    \ ? found->second : item_list.end();\n    }\n};\n"
  code: "#pragma once\n\n#include <unordered_map>\n#include <list>\n\ntemplate <typename\
    \ KeyType, typename ValueType>\nclass lru_cache {\nprivate:\n    using Item =\
    \ std::pair<KeyType, ValueType>;\n    using ItemList = std::list<Item>;\n    using\
    \ ItemMap = std::unordered_map<KeyType, typename ItemList::iterator>;\n\n    ItemList\
    \ item_list;\n    ItemMap item_map;\n    size_t capacity;\n\npublic:\n    using\
    \ iterator = typename ItemList::iterator;\n\n    lru_cache(size_t size) : capacity(size)\
    \ {}\n\n    void put(const KeyType& key, const ValueType& value) {\n        auto\
    \ found = item_map.find(key);\n        if (found != item_map.end()) {\n      \
    \      item_list.erase(found->second);\n            item_map.erase(found);\n \
    \       }\n        if (item_list.size() == capacity) {\n            item_map.erase(item_list.front().first);\n\
    \            item_list.pop_front();\n        }\n        item_list.push_back(std::make_pair(key,\
    \ value));\n        item_map[key] = std::prev(item_list.end());\n    }\n\n   \
    \ iterator get(const KeyType& key) {\n        auto found = item_map.find(key);\n\
    \        if (found == item_map.end()) {\n            return end();\n        }\n\
    \        item_list.splice(item_list.end(), item_list, found->second);\n      \
    \  return found->second;\n    }\n\n    iterator begin() { return item_list.begin();\
    \ }\n    iterator end() { return item_list.end(); }\n    iterator find(const KeyType&\
    \ key) {\n        auto found = item_map.find(key);\n        return found != item_map.end()\
    \ ? found->second : item_list.end();\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/LRU_cache.hpp
  requiredBy: []
  timestamp: '2023-07-03 16:57:02+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/LRU_cache.hpp
layout: document
redirect_from:
- /library/data_structure/LRU_cache.hpp
- /library/data_structure/LRU_cache.hpp.html
title: data_structure/LRU_cache.hpp
---
