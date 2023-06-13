---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/factorize.hpp
    title: "\u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B"
  - icon: ':heavy_check_mark:'
    path: math/prime_number_list.hpp
    title: math/prime_number_list.hpp
  - icon: ':heavy_check_mark:'
    path: math/prime_number_utility.hpp
    title: math/prime_number_utility.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A
  bundledCode: "#line 1 \"test/ntl-1-a.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A\"\
    \n#include <bits/stdc++.h>\n#line 1 \"math/factorize.hpp\"\n\n\n#line 1 \"math/prime_number_list.hpp\"\
    \n\n\n#line 1 \"math/prime_number_utility.hpp\"\n\n\n#line 5 \"math/prime_number_utility.hpp\"\
    \n\n/* is_prime::judge(n) := |n|\u304C\u7D20\u6570\u304B\u3069\u3046\u304B\n *\
    \ \u5224\u5B9A\u8868\u3092\u306A\u3089\u3057\u6642\u9593 O(NloglogN) \u3067\u69CB\
    \u6210\u3057\u3066\u5224\u5B9A\n */\nclass prime_number_utility{\n  protected:\n\
    \    static bool has_table_made;\n    static std::vector<bool> sieve;\n    static\
    \ const int sieve_size = (1 << 18);\n\n  public:\n    prime_number_utility() =\
    \ delete;\n    ~prime_number_utility() = delete;\n\n    static bool is_prime(long\
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
    \ = false;\n\n\n\n#line 5 \"math/prime_number_list.hpp\"\n\n// \u6607\u9806\u306E\
    \u7D20\u6570\u30EA\u30B9\u30C8\nclass prime_number_list{\nprotected:\n    static\
    \ inline std::vector<int> primes{2, 3};\n\npublic:\n    prime_number_list() =\
    \ delete;\n    ~prime_number_list() = delete;\n\n    static void reserve(int siz){\n\
    \        for(int i = primes.back() + 2; (int)primes.size() < siz; i += 2){\n \
    \           if(prime_number_utility::is_prime(i)) primes.push_back(i);\n     \
    \   }\n    }\n\n\t// primes.back() \u304C lim \u3092\u8D85\u3048\u308B\u307E\u3067\
    \u62E1\u5F35\n\tstatic void set_minimum_limit(int lim){\n\t\twhile(primes.back()\
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
    \    return ret;\n}\n\n\n#line 4 \"test/ntl-1-a.test.cpp\"\nusing namespace std;\n\
    using ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    \nint main(void){\n \n    //input\n\n    int N;\n    cin >> N;\n\n    //calculate\n\
    \n    cout << N << \":\";\n    for(auto p : factorize(N)){\n        rep(i,0,p.second)\
    \ cout << \" \" << p.first;\n    }\n    cout << endl;\n\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A\"\n#include\
    \ <bits/stdc++.h>\n#include \"../math/factorize.hpp\"\nusing namespace std;\n\
    using ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    \nint main(void){\n \n    //input\n\n    int N;\n    cin >> N;\n\n    //calculate\n\
    \n    cout << N << \":\";\n    for(auto p : factorize(N)){\n        rep(i,0,p.second)\
    \ cout << \" \" << p.first;\n    }\n    cout << endl;\n\n}"
  dependsOn:
  - math/factorize.hpp
  - math/prime_number_list.hpp
  - math/prime_number_utility.hpp
  isVerificationFile: true
  path: test/ntl-1-a.test.cpp
  requiredBy: []
  timestamp: '2023-06-13 22:45:06+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ntl-1-a.test.cpp
layout: document
redirect_from:
- /verify/test/ntl-1-a.test.cpp
- /verify/test/ntl-1-a.test.cpp.html
title: test/ntl-1-a.test.cpp
---
