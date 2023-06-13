---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/factorize.hpp
    title: "\u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B"
  - icon: ':heavy_check_mark:'
    path: math/prime_number_list.hpp
    title: math/prime_number_list.hpp
  - icon: ':warning:'
    path: math/totient.hpp
    title: math/totient.hpp
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ntl-1-a.test.cpp
    title: test/ntl-1-a.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/prime_number_utility.hpp\"\n\n\n#include <vector>\n\
    #include <math.h>\n\n/* is_prime::judge(n) := |n|\u304C\u7D20\u6570\u304B\u3069\
    \u3046\u304B\n * \u5224\u5B9A\u8868\u3092\u306A\u3089\u3057\u6642\u9593 O(NloglogN)\
    \ \u3067\u69CB\u6210\u3057\u3066\u5224\u5B9A\n */\nclass prime_number_utility{\n\
    \  protected:\n    static bool has_table_made;\n    static std::vector<bool> sieve;\n\
    \    static const int sieve_size = (1 << 18);\n\n  public:\n    prime_number_utility()\
    \ = delete;\n    ~prime_number_utility() = delete;\n\n    static bool is_prime(long\
    \ long n){\n        if(!has_table_made){\n            sieve.assign(sieve_size,\
    \ true);\n            sieve[0] = sieve[1] = false;\n            sieve[2] = true;\n\
    \            for(int i = 4; i < sieve_size; i += 2) sieve[i] = false;\n      \
    \      int sqrt_size = ceil(std::sqrt(sieve_size)) + 1;\n            for(int i\
    \ = 3; i <= sqrt_size; i += 2){\n                if(!sieve[i]) continue;\n   \
    \             for(int j = i * 2; j < sieve_size; j += i) sieve[j] = false;\n \
    \           }\n            has_table_made = true;\n        }\n        if(n < 0)\
    \ n *= -1;\n        if(n < sieve_size) return sieve[n];\n        \n        long\
    \ long sqrt_n = ceil(std::sqrt(n)) + 1;\n        if(n % 2 == 0) return false;\n\
    \        for(long long i = 3; i <= sqrt_n; i += 2){\n            if(!sieve[i])\
    \ continue;\n            if(n % i == 0) return false;\n        }\n        return\
    \ true;\n    }\n\n    static const std::vector<bool> &table(){ return sieve; }\n\
    };\nstd::vector<bool> prime_number_utility::sieve;\nbool prime_number_utility::has_table_made\
    \ = false;\n\n\n\n"
  code: "#ifndef PRIME_NUMBER_UTILITY\n#define PRIME_NUMBER_UTILITY\n#include <vector>\n\
    #include <math.h>\n\n/* is_prime::judge(n) := |n|\u304C\u7D20\u6570\u304B\u3069\
    \u3046\u304B\n * \u5224\u5B9A\u8868\u3092\u306A\u3089\u3057\u6642\u9593 O(NloglogN)\
    \ \u3067\u69CB\u6210\u3057\u3066\u5224\u5B9A\n */\nclass prime_number_utility{\n\
    \  protected:\n    static bool has_table_made;\n    static std::vector<bool> sieve;\n\
    \    static const int sieve_size = (1 << 18);\n\n  public:\n    prime_number_utility()\
    \ = delete;\n    ~prime_number_utility() = delete;\n\n    static bool is_prime(long\
    \ long n){\n        if(!has_table_made){\n            sieve.assign(sieve_size,\
    \ true);\n            sieve[0] = sieve[1] = false;\n            sieve[2] = true;\n\
    \            for(int i = 4; i < sieve_size; i += 2) sieve[i] = false;\n      \
    \      int sqrt_size = ceil(std::sqrt(sieve_size)) + 1;\n            for(int i\
    \ = 3; i <= sqrt_size; i += 2){\n                if(!sieve[i]) continue;\n   \
    \             for(int j = i * 2; j < sieve_size; j += i) sieve[j] = false;\n \
    \           }\n            has_table_made = true;\n        }\n        if(n < 0)\
    \ n *= -1;\n        if(n < sieve_size) return sieve[n];\n        \n        long\
    \ long sqrt_n = ceil(std::sqrt(n)) + 1;\n        if(n % 2 == 0) return false;\n\
    \        for(long long i = 3; i <= sqrt_n; i += 2){\n            if(!sieve[i])\
    \ continue;\n            if(n % i == 0) return false;\n        }\n        return\
    \ true;\n    }\n\n    static const std::vector<bool> &table(){ return sieve; }\n\
    };\nstd::vector<bool> prime_number_utility::sieve;\nbool prime_number_utility::has_table_made\
    \ = false;\n\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/prime_number_utility.hpp
  requiredBy:
  - math/factorize.hpp
  - math/totient.hpp
  - math/prime_number_list.hpp
  timestamp: '2023-06-12 02:08:44+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ntl-1-a.test.cpp
documentation_of: math/prime_number_utility.hpp
layout: document
redirect_from:
- /library/math/prime_number_utility.hpp
- /library/math/prime_number_utility.hpp.html
title: math/prime_number_utility.hpp
---
