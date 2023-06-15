---
data:
  _extendedDependsOn: []
  _extendedRequiredBy:
  - icon: ':heavy_check_mark:'
    path: math/factorize.hpp
    title: "\u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B"
  - icon: ':heavy_check_mark:'
    path: math/totient.hpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u30C8\u30FC\u30B7\u30A7\u30F3\u30C8\u95A2\
      \u6570"
  _extendedVerifiedWith:
  - icon: ':heavy_check_mark:'
    path: test/ntl-1-a.test.cpp
    title: test/ntl-1-a.test.cpp
  - icon: ':heavy_check_mark:'
    path: test/ntl-1-d.test.cpp
    title: test/ntl-1-d.test.cpp
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    document_title: "\u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\u30DD\u30FC\
      \u30C8\u3059\u308B\u30AF\u30E9\u30B9"
    links: []
  bundledCode: "#line 1 \"math/prime_number_utility.hpp\"\n\n\n#include <vector>\n\
    #include <math.h>\n\n/**\n * @brief \u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\
    \u3092\u30B5\u30DD\u30FC\u30C8\u3059\u308B\u30AF\u30E9\u30B9\n * @brief \u7D20\
    \u6570\u7BE9\u3092\u56FA\u5B9A\u30B5\u30A4\u30BA\u3067\u69CB\u7BC9\u3001\u305D\
    \u308C\u3092\u3082\u3068\u306B\u7D20\u6570\u5217\u6319\u306A\u3069\u3092\u884C\
    \u3046\n */\nclass prime_number_utility{\nprotected:\n    static const int init_seive_size\
    \ = (1 << 26), sqrt_size = (1 << 13);\n    static inline std::vector<bool> sieve;\n\
    \    static inline std::vector<int> primes{2, 3};\n\npublic:\n    prime_number_utility()\
    \ = delete;\n    ~prime_number_utility() = delete;\n\n    /**\n     * @brief n\
    \ \u304C\u7D20\u6570\u304B\u3092\u5224\u5B9A\n     * @attention if n < (1 << 26)\
    \ : O(1)\n     * @attention else : O(\u221An)\n     */\n    static bool is_prime(long\
    \ long n) {\n        if(sieve.empty()){ // \u7BE9\u304C\u672A\u69CB\u7BC9\u306A\
    \u3089\n            sieve.assign(init_seive_size, true);\n            sieve[0]\
    \ = sieve[1] = false;\n            for(int i = 4; i < init_seive_size; i += 2)\
    \ sieve[i] = false;\n            for(int i = 3; i <= sqrt_size; i += 2) {\n  \
    \              if(!sieve[i]) continue;\n                for(int j = i * 2; j <\
    \ init_seive_size; j += i) sieve[j] = false;\n            }\n        \n      \
    \  }\n        if((n & 1) == 0) return 0;\n        // n \u304C\u5C0F\u3055\u3044\
    \u3068\u304D\u3001\u7BE9\u3092\u53C2\u7167\n        if(n < init_seive_size) return\
    \ sieve[n];\n        // n \u304C\u5927\u304D\u3044\u3068\u304D\u3001O(\u221An)\
    \ \u8A66\u3057\u5272\u308A\u3067\u8A08\u7B97\n        long long sqrt_n = std::ceil(std::sqrt(n))\
    \ + 1;\n        for(long long i = 3; i <= sqrt_n; i += 2) {\n            if(!sieve[i])\
    \ continue;\n            if(n % i == 0) return false;\n        }\n        return\
    \ true;\n    }\n\n    static void expand_list(int siz){\n        for(int i = primes.back()\
    \ + 2; (int)primes.size() < siz; i += 2){\n            if(is_prime(i)) primes.push_back(i);\n\
    \        }\n    }\n\n\t// \u7D20\u6570\u306E\u30EA\u30B9\u30C8\u3092\u3001\u672B\
    \u5C3E\u306E\u6570\u304C lim \u3092\u8D85\u3048\u308B\u307E\u3067\u62E1\u5F35\n\
    \tstatic void set_minimum_limit(int lim){\n\t\twhile(primes.back() < lim) expand_list(primes.size()\
    \ + 1);\n\t}\n\n    static const std::vector<int> &list(){ return primes; }\n\
    \    static const std::vector<bool> &table(){ return sieve; }\n};\n\n\n"
  code: "#ifndef PRIME_NUMBER_UTILITY\n#define PRIME_NUMBER_UTILITY\n#include <vector>\n\
    #include <math.h>\n\n/**\n * @brief \u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\
    \u3092\u30B5\u30DD\u30FC\u30C8\u3059\u308B\u30AF\u30E9\u30B9\n * @brief \u7D20\
    \u6570\u7BE9\u3092\u56FA\u5B9A\u30B5\u30A4\u30BA\u3067\u69CB\u7BC9\u3001\u305D\
    \u308C\u3092\u3082\u3068\u306B\u7D20\u6570\u5217\u6319\u306A\u3069\u3092\u884C\
    \u3046\n */\nclass prime_number_utility{\nprotected:\n    static const int init_seive_size\
    \ = (1 << 26), sqrt_size = (1 << 13);\n    static inline std::vector<bool> sieve;\n\
    \    static inline std::vector<int> primes{2, 3};\n\npublic:\n    prime_number_utility()\
    \ = delete;\n    ~prime_number_utility() = delete;\n\n    /**\n     * @brief n\
    \ \u304C\u7D20\u6570\u304B\u3092\u5224\u5B9A\n     * @attention if n < (1 << 26)\
    \ : O(1)\n     * @attention else : O(\u221An)\n     */\n    static bool is_prime(long\
    \ long n) {\n        if(sieve.empty()){ // \u7BE9\u304C\u672A\u69CB\u7BC9\u306A\
    \u3089\n            sieve.assign(init_seive_size, true);\n            sieve[0]\
    \ = sieve[1] = false;\n            for(int i = 4; i < init_seive_size; i += 2)\
    \ sieve[i] = false;\n            for(int i = 3; i <= sqrt_size; i += 2) {\n  \
    \              if(!sieve[i]) continue;\n                for(int j = i * 2; j <\
    \ init_seive_size; j += i) sieve[j] = false;\n            }\n        \n      \
    \  }\n        if((n & 1) == 0) return 0;\n        // n \u304C\u5C0F\u3055\u3044\
    \u3068\u304D\u3001\u7BE9\u3092\u53C2\u7167\n        if(n < init_seive_size) return\
    \ sieve[n];\n        // n \u304C\u5927\u304D\u3044\u3068\u304D\u3001O(\u221An)\
    \ \u8A66\u3057\u5272\u308A\u3067\u8A08\u7B97\n        long long sqrt_n = std::ceil(std::sqrt(n))\
    \ + 1;\n        for(long long i = 3; i <= sqrt_n; i += 2) {\n            if(!sieve[i])\
    \ continue;\n            if(n % i == 0) return false;\n        }\n        return\
    \ true;\n    }\n\n    static void expand_list(int siz){\n        for(int i = primes.back()\
    \ + 2; (int)primes.size() < siz; i += 2){\n            if(is_prime(i)) primes.push_back(i);\n\
    \        }\n    }\n\n\t// \u7D20\u6570\u306E\u30EA\u30B9\u30C8\u3092\u3001\u672B\
    \u5C3E\u306E\u6570\u304C lim \u3092\u8D85\u3048\u308B\u307E\u3067\u62E1\u5F35\n\
    \tstatic void set_minimum_limit(int lim){\n\t\twhile(primes.back() < lim) expand_list(primes.size()\
    \ + 1);\n\t}\n\n    static const std::vector<int> &list(){ return primes; }\n\
    \    static const std::vector<bool> &table(){ return sieve; }\n};\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: math/prime_number_utility.hpp
  requiredBy:
  - math/factorize.hpp
  - math/totient.hpp
  timestamp: '2023-06-15 15:10:19+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ntl-1-a.test.cpp
  - test/ntl-1-d.test.cpp
documentation_of: math/prime_number_utility.hpp
layout: document
redirect_from:
- /library/math/prime_number_utility.hpp
- /library/math/prime_number_utility.hpp.html
title: "\u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\u30DD\u30FC\u30C8\u3059\
  \u308B\u30AF\u30E9\u30B9"
---
