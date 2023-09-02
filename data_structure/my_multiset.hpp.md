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
  bundledCode: "#line 2 \"data_structure/my_multiset.hpp\"\n\n#include <iostream>\n\
    #include <set>\n\ntemplate <typename _Key, typename _Compare = std ::less<_Key>,\n\
    \          typename _Alloc = std ::allocator<_Key>>\nclass my_multiset : public\
    \ std::multiset<_Key, _Compare, _Alloc> {\n  public:\n    using std::multiset<_Key,\
    \ _Compare, _Alloc>::multiset;\n    bool erase_one(const _Key &__x) {\n      \
    \  auto it = this->find(__x);\n        if (it == this->end()) {\n            return\
    \ false;\n        } else {\n            this->erase(it);\n            return true;\n\
    \        }\n    }\n    int erase_all(const _Key &__x) {\n        int ret = this->count(__x);\n\
    \        if (ret == 0) {\n            return 0;\n        } else {\n          \
    \  this->erase(__x);\n            return ret;\n        }\n    }\n    const _Key\
    \ &front() const { return *this->begin(); }\n    const _Key &back() const { return\
    \ *--this->end(); }\n    friend std::ostream &operator<<(std::ostream &os, const\
    \ my_multiset &ms) {\n        if (ms.empty())\n            return os;\n      \
    \  auto it = ms.begin();\n        os << *it;\n        for (++it; it != ms.end();\
    \ ++it) {\n            os << ' ' << *it;\n        }\n        return os;\n    }\n\
    };\n\ntemplate <typename _Key, typename _Compare = std ::less<_Key>,\n       \
    \   typename _Alloc = std ::allocator<_Key>>\nclass my_set : public std::set<_Key,\
    \ _Compare, _Alloc> {\n  public:\n    using std::set<_Key, _Compare, _Alloc>::set;\n\
    \    const _Key &front() const { return *this->begin(); }\n    const _Key &back()\
    \ const { return *--this->end(); }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const my_set &ms) {\n        if (ms.empty())\n            return os;\n\
    \        auto it = ms.begin();\n        os << *it;\n        for (++it; it != ms.end();\
    \ ++it) {\n            os << ' ' << *it;\n        }\n        return os;\n    }\n\
    };\n"
  code: "#pragma once\n\n#include <iostream>\n#include <set>\n\ntemplate <typename\
    \ _Key, typename _Compare = std ::less<_Key>,\n          typename _Alloc = std\
    \ ::allocator<_Key>>\nclass my_multiset : public std::multiset<_Key, _Compare,\
    \ _Alloc> {\n  public:\n    using std::multiset<_Key, _Compare, _Alloc>::multiset;\n\
    \    bool erase_one(const _Key &__x) {\n        auto it = this->find(__x);\n \
    \       if (it == this->end()) {\n            return false;\n        } else {\n\
    \            this->erase(it);\n            return true;\n        }\n    }\n  \
    \  int erase_all(const _Key &__x) {\n        int ret = this->count(__x);\n   \
    \     if (ret == 0) {\n            return 0;\n        } else {\n            this->erase(__x);\n\
    \            return ret;\n        }\n    }\n    const _Key &front() const { return\
    \ *this->begin(); }\n    const _Key &back() const { return *--this->end(); }\n\
    \    friend std::ostream &operator<<(std::ostream &os, const my_multiset &ms)\
    \ {\n        if (ms.empty())\n            return os;\n        auto it = ms.begin();\n\
    \        os << *it;\n        for (++it; it != ms.end(); ++it) {\n            os\
    \ << ' ' << *it;\n        }\n        return os;\n    }\n};\n\ntemplate <typename\
    \ _Key, typename _Compare = std ::less<_Key>,\n          typename _Alloc = std\
    \ ::allocator<_Key>>\nclass my_set : public std::set<_Key, _Compare, _Alloc> {\n\
    \  public:\n    using std::set<_Key, _Compare, _Alloc>::set;\n    const _Key &front()\
    \ const { return *this->begin(); }\n    const _Key &back() const { return *--this->end();\
    \ }\n    friend std::ostream &operator<<(std::ostream &os, const my_set &ms) {\n\
    \        if (ms.empty())\n            return os;\n        auto it = ms.begin();\n\
    \        os << *it;\n        for (++it; it != ms.end(); ++it) {\n            os\
    \ << ' ' << *it;\n        }\n        return os;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/my_multiset.hpp
  requiredBy: []
  timestamp: '2023-09-02 19:34:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/my_multiset.hpp
layout: document
redirect_from:
- /library/data_structure/my_multiset.hpp
- /library/data_structure/my_multiset.hpp.html
title: data_structure/my_multiset.hpp
---
