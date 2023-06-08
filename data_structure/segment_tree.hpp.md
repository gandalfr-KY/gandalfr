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
  bundledCode: "#line 1 \"data_structure/segment_tree.hpp\"\n\n\n#include <vector>\n\
    #include <functional>\n#include <assert.h>\n#include <iostream>\n#include <numeric>\n\
    \ntemplate<class T>\nclass segment_tree{\n  private:\n    int n, vec_size;\n \
    \   const T e;\n    const std::function< T(T, T) > op;\n    std::vector<T> v;\n\
    \n  public:\n    // \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\u5316\
    \n    segment_tree(const std::vector<T> &vec, const std::function< T(T, T) > &f,\
    \ T _e) : vec_size(vec.size()), op(f), e(_e) {\n        int siz = vec.size();\n\
    \        n = 1;\n        while(n < siz) n <<= 1;\n        v.resize(2 * n - 1,\
    \ e);\n        \n        for(int i = 0; i < siz; i++) v[i + n - 1] = vec[i];\n\
    \        for(int i = n - 2; i >= 0; i--) v[i] = op(v[2 * i + 1], v[2 * i + 2]);\n\
    \    }\n\n    // \u9577\u3055 siz \u306E\u5358\u4F4D\u5143\u306E\u914D\u5217\u3067\
    \u521D\u671F\u5316\n    segment_tree(int siz, const std::function< T(T, T) > &f,\
    \ T _e) : vec_size(siz), op(f), e(_e) {\n        n = 1;\n        while(n < siz)\
    \ n *= 2;\n        v.resize(2 * n - 1, e);\n    }\n\n    // pos \u756A\u76EE\u306E\
    \u5024\u3092 val \u306B\u66F4\u65B0\n    void update(int pos, T val){\n      \
    \  pos += n - 1;\n        v[pos] = val;\n        while(pos > 0){\n           \
    \ pos = (pos - 1) / 2;\n            v[pos] = op(v[2 * pos + 1], v[2 * pos + 2]);\n\
    \        }\n    }\n\n    // [l, r) \u306E\u6F14\u7B97\u7D50\u679C\u3092\u5F97\u308B\
    \ \n    // l == r \u306E\u3068\u304D e \u3092\u8FD4\u3059\n    T get(int l, int\
    \ r){\n        assert(0 <= l && l <= r && r <= vec_size);\n        T vl = e, vr\
    \ = e;\n        for(l += n, r += n; l < r; l >>= 1, r >>= 1){\n            if(l\
    \ & 1) vl = op(vl, v[l - 1]), l++;\n            if(r & 1) r--, vr = op(v[r - 1],\
    \ vr);\n        }\n        return op(vl, vr);\n    }\n\n    // pos \u756A\u76EE\
    \u306E\u5024\u3092\u5F97\u308B \n    T get(int pos){\n        assert(0 <= pos\
    \ && pos < vec_size);\n        return v[pos + n - 1];\n    }\n\n    void print(){\n\
    \        int prv = 0;\n        for(int sz = 1; ; sz *= 2){\n            for(int\
    \ i = 0; i < sz; i++){\n                std::cout << v[i + prv] << \" \";\n  \
    \          }\n            std::cout << std::endl;\n            prv += sz;\n  \
    \          if(prv >= 2 * n - 1) break;\n        }\n    }\n\n};\n\n\ntemplate<class\
    \ T>\nstruct RSQ_segment_tree : public segment_tree<T>{\n    RSQ_segment_tree(int\
    \ size) : RSQ_segment_tree<T>::segment_tree(size, [](T a, T b){ return a + b;\
    \ }, 0) {};\n    RSQ_segment_tree(const std::vector<T> &vec) : RSQ_segment_tree<T>::segment_tree(vec,\
    \ [](T a, T b){ return a + b; }, 0) {};\n};\n\ntemplate<class T>\nstruct RmQ_segment_tree\
    \ : public segment_tree<T>{\n    RmQ_segment_tree(int size) : RmQ_segment_tree<T>::segment_tree(size,\
    \ [](T a, T b){ return (a < b ? a : b); }, std::numeric_limits<T>::max()) {};\n\
    \    RmQ_segment_tree(const std::vector<T> &vec) : RmQ_segment_tree<T>::segment_tree(vec,\
    \ [](T a, T b){ return (a < b ? a : b); }, std::numeric_limits<T>::max()) {};\n\
    };\n\ntemplate<class T>\nstruct RMQ_segment_tree : public segment_tree<T>{\n \
    \   RMQ_segment_tree(int size) : RMQ_segment_tree<T>::segment_tree(size, [](T\
    \ a, T b){ return (a > b ? a : b); }, std::numeric_limits<T>::lowest()) {};\n\
    \    RMQ_segment_tree(const std::vector<T> &vec) : RMQ_segment_tree<T>::segment_tree(vec,\
    \ [](T a, T b){ return (a > b ? a : b); }, std::numeric_limits<T>::lowest()) {};\n\
    };\n\n\n"
  code: "#ifndef SEGMENT_TREE\n#define SEGMENT_TREE\n#include <vector>\n#include <functional>\n\
    #include <assert.h>\n#include <iostream>\n#include <numeric>\n\ntemplate<class\
    \ T>\nclass segment_tree{\n  private:\n    int n, vec_size;\n    const T e;\n\
    \    const std::function< T(T, T) > op;\n    std::vector<T> v;\n\n  public:\n\
    \    // \u8981\u7D20\u306E\u914D\u5217 vec \u3067\u521D\u671F\u5316\n    segment_tree(const\
    \ std::vector<T> &vec, const std::function< T(T, T) > &f, T _e) : vec_size(vec.size()),\
    \ op(f), e(_e) {\n        int siz = vec.size();\n        n = 1;\n        while(n\
    \ < siz) n <<= 1;\n        v.resize(2 * n - 1, e);\n        \n        for(int\
    \ i = 0; i < siz; i++) v[i + n - 1] = vec[i];\n        for(int i = n - 2; i >=\
    \ 0; i--) v[i] = op(v[2 * i + 1], v[2 * i + 2]);\n    }\n\n    // \u9577\u3055\
    \ siz \u306E\u5358\u4F4D\u5143\u306E\u914D\u5217\u3067\u521D\u671F\u5316\n   \
    \ segment_tree(int siz, const std::function< T(T, T) > &f, T _e) : vec_size(siz),\
    \ op(f), e(_e) {\n        n = 1;\n        while(n < siz) n *= 2;\n        v.resize(2\
    \ * n - 1, e);\n    }\n\n    // pos \u756A\u76EE\u306E\u5024\u3092 val \u306B\u66F4\
    \u65B0\n    void update(int pos, T val){\n        pos += n - 1;\n        v[pos]\
    \ = val;\n        while(pos > 0){\n            pos = (pos - 1) / 2;\n        \
    \    v[pos] = op(v[2 * pos + 1], v[2 * pos + 2]);\n        }\n    }\n\n    //\
    \ [l, r) \u306E\u6F14\u7B97\u7D50\u679C\u3092\u5F97\u308B \n    // l == r \u306E\
    \u3068\u304D e \u3092\u8FD4\u3059\n    T get(int l, int r){\n        assert(0\
    \ <= l && l <= r && r <= vec_size);\n        T vl = e, vr = e;\n        for(l\
    \ += n, r += n; l < r; l >>= 1, r >>= 1){\n            if(l & 1) vl = op(vl, v[l\
    \ - 1]), l++;\n            if(r & 1) r--, vr = op(v[r - 1], vr);\n        }\n\
    \        return op(vl, vr);\n    }\n\n    // pos \u756A\u76EE\u306E\u5024\u3092\
    \u5F97\u308B \n    T get(int pos){\n        assert(0 <= pos && pos < vec_size);\n\
    \        return v[pos + n - 1];\n    }\n\n    void print(){\n        int prv =\
    \ 0;\n        for(int sz = 1; ; sz *= 2){\n            for(int i = 0; i < sz;\
    \ i++){\n                std::cout << v[i + prv] << \" \";\n            }\n  \
    \          std::cout << std::endl;\n            prv += sz;\n            if(prv\
    \ >= 2 * n - 1) break;\n        }\n    }\n\n};\n\n\ntemplate<class T>\nstruct\
    \ RSQ_segment_tree : public segment_tree<T>{\n    RSQ_segment_tree(int size) :\
    \ RSQ_segment_tree<T>::segment_tree(size, [](T a, T b){ return a + b; }, 0) {};\n\
    \    RSQ_segment_tree(const std::vector<T> &vec) : RSQ_segment_tree<T>::segment_tree(vec,\
    \ [](T a, T b){ return a + b; }, 0) {};\n};\n\ntemplate<class T>\nstruct RmQ_segment_tree\
    \ : public segment_tree<T>{\n    RmQ_segment_tree(int size) : RmQ_segment_tree<T>::segment_tree(size,\
    \ [](T a, T b){ return (a < b ? a : b); }, std::numeric_limits<T>::max()) {};\n\
    \    RmQ_segment_tree(const std::vector<T> &vec) : RmQ_segment_tree<T>::segment_tree(vec,\
    \ [](T a, T b){ return (a < b ? a : b); }, std::numeric_limits<T>::max()) {};\n\
    };\n\ntemplate<class T>\nstruct RMQ_segment_tree : public segment_tree<T>{\n \
    \   RMQ_segment_tree(int size) : RMQ_segment_tree<T>::segment_tree(size, [](T\
    \ a, T b){ return (a > b ? a : b); }, std::numeric_limits<T>::lowest()) {};\n\
    \    RMQ_segment_tree(const std::vector<T> &vec) : RMQ_segment_tree<T>::segment_tree(vec,\
    \ [](T a, T b){ return (a > b ? a : b); }, std::numeric_limits<T>::lowest()) {};\n\
    };\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: data_structure/segment_tree.hpp
  requiredBy: []
  timestamp: '2023-05-09 10:06:27+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: data_structure/segment_tree.hpp
layout: document
redirect_from:
- /library/data_structure/segment_tree.hpp
- /library/data_structure/segment_tree.hpp.html
title: data_structure/segment_tree.hpp
---
