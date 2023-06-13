---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/prime_number_list.hpp
    title: math/prime_number_list.hpp
  - icon: ':heavy_check_mark:'
    path: math/prime_number_utility.hpp
    title: math/prime_number_utility.hpp
  _extendedRequiredBy:
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
    document_title: "\u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B"
    links: []
  bundledCode: "#line 1 \"math/factorize.hpp\"\n\n\n#include <utility>\n#include <cmath>\n\
    #line 1 \"math/prime_number_list.hpp\"\n\n\n#include <assert.h>\n#line 1 \"math/prime_number_utility.hpp\"\
    \n\n\n#include <vector>\n#include <math.h>\n\n/* is_prime::judge(n) := |n|\u304C\
    \u7D20\u6570\u304B\u3069\u3046\u304B\n * \u5224\u5B9A\u8868\u3092\u306A\u3089\u3057\
    \u6642\u9593 O(NloglogN) \u3067\u69CB\u6210\u3057\u3066\u5224\u5B9A\n */\nclass\
    \ prime_number_utility{\n  protected:\n    static const int init_seive_size =\
    \ (1 << 24), sqrt_size = (1 << 12);\n    static inline std::vector<bool> sieve;\n\
    \n  public:\n    prime_number_utility() = delete;\n    ~prime_number_utility()\
    \ = delete;\n\n    static bool is_prime(long long n) {\n        if(sieve.empty()){\
    \ // \u7BE9\u304C\u672A\u69CB\u7BC9\u306A\u3089\n            sieve.assign(init_seive_size,\
    \ true);\n            sieve[0] = sieve[1] = false;\n            for(int i = 4;\
    \ i < init_seive_size; i += 2) sieve[i] = false;\n            for(int i = 3; i\
    \ <= sqrt_size; i += 2) {\n                if(!sieve[i]) continue;\n         \
    \       for(int j = i * 2; j < init_seive_size; j += i) sieve[j] = false;\n  \
    \          }\n        }\n\n        // n \u304C\u5C0F\u3055\u3044\u3068\u304D\u3001\
    \u7BE9\u3092\u53C2\u7167\n        if(n < init_seive_size) return sieve[n];\n \
    \       if(n & 1 == 0) return 0;\n        // n \u304C\u5927\u304D\u3044\u3068\u304D\
    \u3001O(\u221An) \u8A66\u3057\u5272\u308A\u3067\u8A08\u7B97\n        long long\
    \ sqrt_n = std::ceil(std::sqrt(n)) + 1;\n        for(long long i = 3; i <= sqrt_n;\
    \ i += 2) {\n            if(!sieve[i]) continue;\n            if(n % i == 0) return\
    \ false;\n        }\n        return true;\n    }\n\n    static const std::vector<bool>\
    \ &table(){ return sieve; }\n};\n\n\n\n#line 5 \"math/prime_number_list.hpp\"\n\
    \n// \u6607\u9806\u306E\u7D20\u6570\u30EA\u30B9\u30C8\nclass prime_number_list{\n\
    protected:\n    static inline std::vector<int> primes{2, 3};\n\npublic:\n    prime_number_list()\
    \ = delete;\n    ~prime_number_list() = delete;\n\n    static void reserve(int\
    \ siz){\n        for(int i = primes.back() + 2; (int)primes.size() < siz; i +=\
    \ 2){\n            if(prime_number_utility::is_prime(i)) primes.push_back(i);\n\
    \        }\n    }\n\n\t// primes.back() \u304C lim \u3092\u8D85\u3048\u308B\u307E\
    \u3067\u62E1\u5F35\n\tstatic void set_minimum_limit(int lim){\n\t\twhile(primes.back()\
    \ < lim) reserve(primes.size() + 1);\n\t}\n\n    static const std::vector<int>\
    \ &list(){ return primes; }\n};\n\n\n#line 6 \"math/factorize.hpp\"\n\n/**\n *\
    \ @brief \u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B\n * @return prime_factorize(p1^e1\
    \ * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...}\n * @attention prime_factorize(1)\
    \ => {}\n * @attention prime_factorize(0) => {{0, 1}}\n */ \nstd::vector<std::pair<long\
    \ long, int>> factorize(long long N){\n    std::vector<std::pair<long long, int>>\
    \ ret;\n    prime_number_list::set_minimum_limit(ceil(sqrt(N)));\n    long long\
    \ p;\n    for(long long p : prime_number_list::list()){\n        if(N == 1 ||\
    \ (__int128_t)p * p > N) break;\n        while(N % p == 0){\n            if(ret.empty()\
    \ || ret.back().first != p) ret.push_back({p, 1});\n            else ret.back().second++;\n\
    \            N /= p;\n        }\n    }\n    if(N != 1) ret.push_back({N, 1});\n\
    \    return ret;\n}\n\n\n"
  code: "#ifndef FACTORIZE\n#define FACTORIZE\n#include <utility>\n#include <cmath>\n\
    #include \"prime_number_list.hpp\"\n\n/**\n * @brief \u7D20\u56E0\u6570\u5206\u89E3\
    \u3059\u308B\n * @return prime_factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2,\
    \ e2], ...}\n * @attention prime_factorize(1) => {}\n * @attention prime_factorize(0)\
    \ => {{0, 1}}\n */ \nstd::vector<std::pair<long long, int>> factorize(long long\
    \ N){\n    std::vector<std::pair<long long, int>> ret;\n    prime_number_list::set_minimum_limit(ceil(sqrt(N)));\n\
    \    long long p;\n    for(long long p : prime_number_list::list()){\n       \
    \ if(N == 1 || (__int128_t)p * p > N) break;\n        while(N % p == 0){\n   \
    \         if(ret.empty() || ret.back().first != p) ret.push_back({p, 1});\n  \
    \          else ret.back().second++;\n            N /= p;\n        }\n    }\n\
    \    if(N != 1) ret.push_back({N, 1});\n    return ret;\n}\n\n#endif"
  dependsOn:
  - math/prime_number_list.hpp
  - math/prime_number_utility.hpp
  isVerificationFile: false
  path: math/factorize.hpp
  requiredBy:
  - math/totient.hpp
  timestamp: '2023-06-13 23:12:39+09:00'
  verificationStatus: LIBRARY_ALL_AC
  verifiedWith:
  - test/ntl-1-a.test.cpp
documentation_of: math/factorize.hpp
layout: document
redirect_from:
- /library/math/factorize.hpp
- /library/math/factorize.hpp.html
title: "\u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B"
---
