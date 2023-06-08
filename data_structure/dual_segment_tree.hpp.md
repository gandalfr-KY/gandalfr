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
    - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627473#1
    - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627486#1
  bundledCode: "#line 1 \"data_structure/dual_segment_tree.hpp\"\n\n\n#include <vector>\n\
    #include <functional>\n#include <assert.h>\n#include <iostream>\n#include <optional>\n\
    \n/*\n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627486#1\n\
    \ */\ntemplate<class T>\nclass dual_segment_tree{\n  private:\n    int n, vec_size;\n\
    \    const T e;\n    const std::function< T(T, T) > op;\n    std::vector<T> v;\n\
    \n  public:\n    // \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\u5316\
    \n    dual_segment_tree(const std::vector<T> &vec, const std::function< T(T, T)\
    \ > &f, T _e) : vec_size(vec.size()), op(f), e(_e) {\n        int siz = vec.size();\n\
    \        n = 1;\n        while(n < siz) n *= 2;\n        v.resize(2 * n - 1, e);\n\
    \        for(int i = 0; i < siz; i++) v[i + n - 1] = vec[i];\n    }\n\n    //\
    \ \u9577\u3055 siz \u306E\u5358\u4F4D\u5143\u306E\u914D\u5217\u3067\u521D\u671F\
    \u5316\n    dual_segment_tree(int siz, const std::function< T(T, T) > &f, T _e)\
    \ : vec_size(siz), op(f), e(_e) {\n        n = 1;\n        while(n < siz) n *=\
    \ 2;\n        v.resize(2 * n - 1, e);\n    }\n\n    // pos \u756A\u76EE\u306E\u5024\
    \u3092\u5F97\u308B\n    T get(int pos){\n        pos += n - 1;\n        T ret\
    \ = v[pos];\n        while(pos > 0){\n            pos = (pos - 1) / 2;\n     \
    \       ret = op(ret, v[pos]);\n        }\n        return ret;\n    }\n\n    //\
    \ [l, r) \u306B action \u3092\u4F5C\u7528\u3059\u308B \n    void act(int l, int\
    \ r, T action){\n        assert(0 <= l && l <= r && r <= vec_size);\n        if(l\
    \ == r) return;\n        act(l, r, 0, 0, n, action);\n    }\n\n    void print(){\n\
    \        for(int i = 0; i < vec_size; i++){\n            std::cout << get(i) <<\
    \ (i == vec_size - 1 ? \"\" : \" \");\n        }\n        std::cout << std::endl;\n\
    \    }\n\n  private:\n    void act(int a, int b, int k, int l, int r, T action){\n\
    \        if(r <= a || b <= l) return;\n        if(a <= l && r <= b){\n       \
    \     v[k] = op(v[k], action);\n            return;\n        }\n        act(a,\
    \ b, 2 * k + 1, l, (l + r) / 2, action);\n        act(a, b, 2 * k + 2, (l + r)\
    \ / 2, r, action);\n    }\n};\n\ntemplate<class T>\nstruct RAQ_dual_segment_tree\
    \ : public dual_segment_tree<T>{\n    RAQ_dual_segment_tree(int size) : RAQ_dual_segment_tree<T>::dual_segment_tree(size,\
    \ [](T a, T b){ return a + b; }, 0) {};\n    RAQ_dual_segment_tree(const std::vector<T>\
    \ &vec) : RAQ_dual_segment_tree<T>::dual_segment_tree(vec, [](T a, T b){ return\
    \ a + b; }, 0) {};\n};\n\n/* \n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627473#1\n\
    \ */\ntemplate<class T>\nclass RUQ_dual_segment_tree{\n  private:\n    int n,\
    \ tm = 0, vec_size;\n    std::vector<std::pair<int, T>> v;\n\n  public:\n    //\
    \ \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\u5316\n    RUQ_dual_segment_tree(const\
    \ std::vector<T> &vec) : vec_size(vec.size()) {\n        int siz = vec.size();\n\
    \        n = 1;\n        while(n < siz) n *= 2;\n        v.resize(2 * n - 1);\n\
    \        for(auto &x : v) x.first = -1;\n        for(int i = 0; i < siz; i++)\
    \ v[i + n - 1].second = vec[i];\n    }\n\n    // \u9577\u3055 siz \u306E\u5358\
    \u4F4D\u5143\u306E\u914D\u5217\u3067\u521D\u671F\u5316\n    RUQ_dual_segment_tree(int\
    \ siz) : vec_size(siz) {\n        n = 1;\n        while(n < siz) n *= 2;\n   \
    \     v.resize(2 * n - 1);\n        for(auto &x : v) x.first = -1;\n    }\n\n\
    \    // pos \u756A\u76EE\u306E\u5024\u3092\u5F97\u308B\n    T get(int pos){\n\
    \        pos += n - 1;\n        std::pair<int, T> ret = v[pos];\n        while(pos\
    \ > 0){\n            pos = (pos - 1) / 2;\n            ret = std::max(ret, v[pos]);\n\
    \        }\n        return ret.second;\n    }\n\n    // [l, r) \u306B action \u3092\
    \u4F5C\u7528\u3059\u308B \n    void act(int l, int r, T action){\n        assert(0\
    \ <= l && l <= r && r <= vec_size);\n        if(l == r) return;\n        act(l,\
    \ r, 0, 0, n, {tm, action});\n        tm++;\n    }\n\n    void print(){\n    \
    \    for(int i = 0; i < vec_size; i++){\n            std::cout << get(i) << (i\
    \ == vec_size - 1 ? \"\" : \" \");\n        }\n        std::cout << std::endl;\n\
    \    }\n\n  private:\n    void act(int a, int b, int k, int l, int r, std::pair<int,\
    \ T> action){\n        if(r <= a || b <= l) return;\n        if(a <= l && r <=\
    \ b){\n            v[k] = std::max(v[k], action);\n            return;\n     \
    \   }\n        act(a, b, 2 * k + 1, l, (l + r) / 2, action);\n        act(a, b,\
    \ 2 * k + 2, (l + r) / 2, r, action);\n    }\n};\n\n\n\n\n\n"
  code: "#ifndef DUAL_SEGMENT_TREE\n#define DUAL_SEGMENT_TREE\n#include <vector>\n\
    #include <functional>\n#include <assert.h>\n#include <iostream>\n#include <optional>\n\
    \n/*\n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627486#1\n\
    \ */\ntemplate<class T>\nclass dual_segment_tree{\n  private:\n    int n, vec_size;\n\
    \    const T e;\n    const std::function< T(T, T) > op;\n    std::vector<T> v;\n\
    \n  public:\n    // \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\u5316\
    \n    dual_segment_tree(const std::vector<T> &vec, const std::function< T(T, T)\
    \ > &f, T _e) : vec_size(vec.size()), op(f), e(_e) {\n        int siz = vec.size();\n\
    \        n = 1;\n        while(n < siz) n *= 2;\n        v.resize(2 * n - 1, e);\n\
    \        for(int i = 0; i < siz; i++) v[i + n - 1] = vec[i];\n    }\n\n    //\
    \ \u9577\u3055 siz \u306E\u5358\u4F4D\u5143\u306E\u914D\u5217\u3067\u521D\u671F\
    \u5316\n    dual_segment_tree(int siz, const std::function< T(T, T) > &f, T _e)\
    \ : vec_size(siz), op(f), e(_e) {\n        n = 1;\n        while(n < siz) n *=\
    \ 2;\n        v.resize(2 * n - 1, e);\n    }\n\n    // pos \u756A\u76EE\u306E\u5024\
    \u3092\u5F97\u308B\n    T get(int pos){\n        pos += n - 1;\n        T ret\
    \ = v[pos];\n        while(pos > 0){\n            pos = (pos - 1) / 2;\n     \
    \       ret = op(ret, v[pos]);\n        }\n        return ret;\n    }\n\n    //\
    \ [l, r) \u306B action \u3092\u4F5C\u7528\u3059\u308B \n    void act(int l, int\
    \ r, T action){\n        assert(0 <= l && l <= r && r <= vec_size);\n        if(l\
    \ == r) return;\n        act(l, r, 0, 0, n, action);\n    }\n\n    void print(){\n\
    \        for(int i = 0; i < vec_size; i++){\n            std::cout << get(i) <<\
    \ (i == vec_size - 1 ? \"\" : \" \");\n        }\n        std::cout << std::endl;\n\
    \    }\n\n  private:\n    void act(int a, int b, int k, int l, int r, T action){\n\
    \        if(r <= a || b <= l) return;\n        if(a <= l && r <= b){\n       \
    \     v[k] = op(v[k], action);\n            return;\n        }\n        act(a,\
    \ b, 2 * k + 1, l, (l + r) / 2, action);\n        act(a, b, 2 * k + 2, (l + r)\
    \ / 2, r, action);\n    }\n};\n\ntemplate<class T>\nstruct RAQ_dual_segment_tree\
    \ : public dual_segment_tree<T>{\n    RAQ_dual_segment_tree(int size) : RAQ_dual_segment_tree<T>::dual_segment_tree(size,\
    \ [](T a, T b){ return a + b; }, 0) {};\n    RAQ_dual_segment_tree(const std::vector<T>\
    \ &vec) : RAQ_dual_segment_tree<T>::dual_segment_tree(vec, [](T a, T b){ return\
    \ a + b; }, 0) {};\n};\n\n/* \n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7627473#1\n\
    \ */\ntemplate<class T>\nclass RUQ_dual_segment_tree{\n  private:\n    int n,\
    \ tm = 0, vec_size;\n    std::vector<std::pair<int, T>> v;\n\n  public:\n    //\
    \ \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\u5316\n    RUQ_dual_segment_tree(const\
    \ std::vector<T> &vec) : vec_size(vec.size()) {\n        int siz = vec.size();\n\
    \        n = 1;\n        while(n < siz) n *= 2;\n        v.resize(2 * n - 1);\n\
    \        for(auto &x : v) x.first = -1;\n        for(int i = 0; i < siz; i++)\
    \ v[i + n - 1].second = vec[i];\n    }\n\n    // \u9577\u3055 siz \u306E\u5358\
    \u4F4D\u5143\u306E\u914D\u5217\u3067\u521D\u671F\u5316\n    RUQ_dual_segment_tree(int\
    \ siz) : vec_size(siz) {\n        n = 1;\n        while(n < siz) n *= 2;\n   \
    \     v.resize(2 * n - 1);\n        for(auto &x : v) x.first = -1;\n    }\n\n\
    \    // pos \u756A\u76EE\u306E\u5024\u3092\u5F97\u308B\n    T get(int pos){\n\
    \        pos += n - 1;\n        std::pair<int, T> ret = v[pos];\n        while(pos\
    \ > 0){\n            pos = (pos - 1) / 2;\n            ret = std::max(ret, v[pos]);\n\
    \        }\n        return ret.second;\n    }\n\n    // [l, r) \u306B action \u3092\
    \u4F5C\u7528\u3059\u308B \n    void act(int l, int r, T action){\n        assert(0\
    \ <= l && l <= r && r <= vec_size);\n        if(l == r) return;\n        act(l,\
    \ r, 0, 0, n, {tm, action});\n        tm++;\n    }\n\n    void print(){\n    \
    \    for(int i = 0; i < vec_size; i++){\n            std::cout << get(i) << (i\
    \ == vec_size - 1 ? \"\" : \" \");\n        }\n        std::cout << std::endl;\n\
    \    }\n\n  private:\n    void act(int a, int b, int k, int l, int r, std::pair<int,\
    \ T> action){\n        if(r <= a || b <= l) return;\n        if(a <= l && r <=\
    \ b){\n            v[k] = std::max(v[k], action);\n            return;\n     \
    \   }\n        act(a, b, 2 * k + 1, l, (l + r) / 2, action);\n        act(a, b,\
    \ 2 * k + 2, (l + r) / 2, r, action);\n    }\n};\n\n\n\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/dual_segment_tree.hpp
  requiredBy: []
  timestamp: '2023-04-03 23:41:42+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/dual_segment_tree.hpp
layout: document
redirect_from:
- /library/data_structure/dual_segment_tree.hpp
- /library/data_structure/dual_segment_tree.hpp.html
title: data_structure/dual_segment_tree.hpp
---
