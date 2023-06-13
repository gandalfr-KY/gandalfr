---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://yukicoder.me/submissions/856775
  bundledCode: "#line 1 \"data_structure/Kth_hold_multiset.hpp\"\n\n\n#include <set>\n\
    #include <assert.h>\n#include <iostream>\n\n/*\n * verify : https://yukicoder.me/submissions/856775\n\
    \ */\ntemplate<class T>\nclass Kth_hold_multiset{\n  private:\n    std::multiset<T>\
    \ low, high;// low \u306E\u30B5\u30A4\u30BA\u3092 K \u306B\u4FDD\u3064\n    const\
    \ int k;\n    void refill(){\n        while((int)low.size() > k) {\n         \
    \   auto it = prev(low.end());\n            high.insert(*it);\n            low.erase(it);\n\
    \        }\n        while(!high.empty() && (int)low.size() < k) {\n          \
    \  auto it = high.begin();\n            low.insert(*it);\n            high.erase(it);\n\
    \        }\n    }\n\n    class Iterator {\n      public:\n        Iterator(typename\
    \ std::multiset<T>::iterator it, std::multiset<T>& low, std::multiset<T>& high)\n\
    \            : it_(it), low_(low), high_(high) {}\n\n        bool operator==(const\
    \ Iterator& other) const { return it_ == other.it_; }\n        bool operator!=(const\
    \ Iterator& other) const { return it_ != other.it_; }\n\n        const T& operator*()\
    \ const { return *it_; }\n\n        Iterator& operator++() {\n            ++it_;\n\
    \            if(it_ == low_.end()) it_ = high_.begin();\n            return *this;\n\
    \        }\n\n        Iterator operator++(int) {\n            Iterator tmp = *this;\n\
    \            ++(*this);\n            return tmp;\n        }\n\n      private:\n\
    \        typename std::multiset<T>::iterator it_;\n        std::multiset<T>& low_;\n\
    \        std::multiset<T>& high_;\n    };\n\n\n  public:\n    Kth_hold_multiset(int\
    \ K) : k(K) { assert(K > 0); }\n\n    void insert(T x){\n        if((int)low.size()\
    \ < k) {\n            low.insert(x);\n            return;\n        }\n       \
    \ \n        T Kth = *prev(low.end());\n        if(x >= Kth) high.insert(x);\n\
    \        else low.insert(x);\n        refill();\n    }\n\n    void erase_a_element(T\
    \ x){\n        if(high.empty()) {\n            auto low_it = low.find(x); \n \
    \           if(low_it != low.end()) low.erase(low_it);\n            return;\n\
    \        }\n\n        auto high_it = high.find(x); \n        auto low_it = low.find(x);\
    \ \n        if(high_it != high.end()) high.erase(high_it);\n        else if(low_it\
    \ != low.end()) low.erase(low_it);\n        refill();\n    }\n\n    void erase_all_element(T\
    \ x){\n        low.erase(x);\n        high.erase(x);\n        refill();\n    }\n\
    \n    Iterator find(T x){\n        auto low_it = low.find(x);\n        if(low_it\
    \ != low.end()) return Iterator(low_it, low, high);\n        else return Iterator(high.find(x),\
    \ low, high);\n    }\n\n    int size(){\n        return low.size() + high.size();\n\
    \    }\n\n    T get_Kth_value(){\n        return *prev(low.end());\n    }\n\n\
    \    int count(T x){\n        return low.count(x) + high.count(x);\n    }\n  \
    \  \n    void dump(){\n        int loop = low.size() + high.size();\n        for(auto\
    \ x : *this){\n            loop--;\n            std::cout << x << (loop ? \" \"\
    \ : \"\");\n        }\n    }\n\n    Iterator begin() {\n        return low.empty()\
    \ ? Iterator(high.end(), low, high) : Iterator(low.begin(), low, high);\n    }\n\
    \    Iterator end() {\n        return Iterator(high.end(), low, high);\n    }\n\
    \n};\n\n\n"
  code: "#ifndef KTH_HOLD_MULTISET\n#define KTH_HOLD_MULTISET\n#include <set>\n#include\
    \ <assert.h>\n#include <iostream>\n\n/*\n * verify : https://yukicoder.me/submissions/856775\n\
    \ */\ntemplate<class T>\nclass Kth_hold_multiset{\n  private:\n    std::multiset<T>\
    \ low, high;// low \u306E\u30B5\u30A4\u30BA\u3092 K \u306B\u4FDD\u3064\n    const\
    \ int k;\n    void refill(){\n        while((int)low.size() > k) {\n         \
    \   auto it = prev(low.end());\n            high.insert(*it);\n            low.erase(it);\n\
    \        }\n        while(!high.empty() && (int)low.size() < k) {\n          \
    \  auto it = high.begin();\n            low.insert(*it);\n            high.erase(it);\n\
    \        }\n    }\n\n    class Iterator {\n      public:\n        Iterator(typename\
    \ std::multiset<T>::iterator it, std::multiset<T>& low, std::multiset<T>& high)\n\
    \            : it_(it), low_(low), high_(high) {}\n\n        bool operator==(const\
    \ Iterator& other) const { return it_ == other.it_; }\n        bool operator!=(const\
    \ Iterator& other) const { return it_ != other.it_; }\n\n        const T& operator*()\
    \ const { return *it_; }\n\n        Iterator& operator++() {\n            ++it_;\n\
    \            if(it_ == low_.end()) it_ = high_.begin();\n            return *this;\n\
    \        }\n\n        Iterator operator++(int) {\n            Iterator tmp = *this;\n\
    \            ++(*this);\n            return tmp;\n        }\n\n      private:\n\
    \        typename std::multiset<T>::iterator it_;\n        std::multiset<T>& low_;\n\
    \        std::multiset<T>& high_;\n    };\n\n\n  public:\n    Kth_hold_multiset(int\
    \ K) : k(K) { assert(K > 0); }\n\n    void insert(T x){\n        if((int)low.size()\
    \ < k) {\n            low.insert(x);\n            return;\n        }\n       \
    \ \n        T Kth = *prev(low.end());\n        if(x >= Kth) high.insert(x);\n\
    \        else low.insert(x);\n        refill();\n    }\n\n    void erase_a_element(T\
    \ x){\n        if(high.empty()) {\n            auto low_it = low.find(x); \n \
    \           if(low_it != low.end()) low.erase(low_it);\n            return;\n\
    \        }\n\n        auto high_it = high.find(x); \n        auto low_it = low.find(x);\
    \ \n        if(high_it != high.end()) high.erase(high_it);\n        else if(low_it\
    \ != low.end()) low.erase(low_it);\n        refill();\n    }\n\n    void erase_all_element(T\
    \ x){\n        low.erase(x);\n        high.erase(x);\n        refill();\n    }\n\
    \n    Iterator find(T x){\n        auto low_it = low.find(x);\n        if(low_it\
    \ != low.end()) return Iterator(low_it, low, high);\n        else return Iterator(high.find(x),\
    \ low, high);\n    }\n\n    int size(){\n        return low.size() + high.size();\n\
    \    }\n\n    T get_Kth_value(){\n        return *prev(low.end());\n    }\n\n\
    \    int count(T x){\n        return low.count(x) + high.count(x);\n    }\n  \
    \  \n    void dump(){\n        int loop = low.size() + high.size();\n        for(auto\
    \ x : *this){\n            loop--;\n            std::cout << x << (loop ? \" \"\
    \ : \"\");\n        }\n    }\n\n    Iterator begin() {\n        return low.empty()\
    \ ? Iterator(high.end(), low, high) : Iterator(low.begin(), low, high);\n    }\n\
    \    Iterator end() {\n        return Iterator(high.end(), low, high);\n    }\n\
    \n};\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/Kth_hold_multiset.hpp
  requiredBy: []
  timestamp: '2023-04-12 00:32:33+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/Kth_hold_multiset.hpp
layout: document
redirect_from:
- /library/data_structure/Kth_hold_multiset.hpp
- /library/data_structure/Kth_hold_multiset.hpp.html
title: data_structure/Kth_hold_multiset.hpp
---