---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/factorize.hpp
    title: math/factorize.hpp
  - icon: ':warning:'
    path: math/prime_number_utility.hpp
    title: math/prime_number_utility.hpp
  - icon: ':warning:'
    path: math/primes_list.hpp
    title: math/primes_list.hpp
  - icon: ':warning:'
    path: standard/power.hpp
    title: standard/power.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links:
    - https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7267874
  bundledCode: "#line 1 \"math/totient.hpp\"\n\n\n#line 1 \"standard/power.hpp\"\n\
    \n\n#include <assert.h>\n\ntemplate<class T>\nT power(T x, long long n) {\n  \
    \  T ret = T(1);\n    while (n > 0) {\n        if (n & 1) ret = ret * x;\n   \
    \     x = x * x;\n        n >>= 1;\n    }\n    return ret;\n}\n\nlong long power(long\
    \ long x, long long n) {\n    long long ret = 1;\n    while (n > 0) {\n      \
    \  if (n & 1) ret = ret * x;\n        x = x * x;\n        n >>= 1;\n    }\n  \
    \  return ret;\n}\n\nlong long power(long long x, long long n, int MOD) {\n  \
    \  long long ret = 1;\n    x %= MOD;\n    while (n > 0) {\n        if (n & 1)\
    \ ret = ret * x % MOD;\n        x = x * x % MOD;\n        n >>= 1;\n    }\n  \
    \  return ret;\n}\n\n\n#line 1 \"math/factorize.hpp\"\n\n\n#include <utility>\n\
    #include <cmath>\n#line 1 \"math/primes_list.hpp\"\n\n\n#line 1 \"math/prime_number_utility.hpp\"\
    \n\n\n#include <vector>\n#include <math.h>\n\n/* is_prime::judge(n) := |n|\u304C\
    \u7D20\u6570\u304B\u3069\u3046\u304B\n * \u5224\u5B9A\u8868\u3092\u306A\u3089\u3057\
    \u6642\u9593 O(NloglogN) \u3067\u69CB\u6210\u3057\u3066\u5224\u5B9A\n */\nclass\
    \ prime_number_utility{\n  protected:\n    static bool has_table_made;\n    static\
    \ std::vector<bool> sieve;\n    static const int sieve_size = (1 << 18);\n\n \
    \ public:\n    prime_number_utility() = delete;\n    ~prime_number_utility() =\
    \ delete;\n\n    static bool is_prime(long long n){\n        if(!has_table_made){\n\
    \            sieve.assign(sieve_size, true);\n            sieve[0] = sieve[1]\
    \ = false;\n            sieve[2] = true;\n            for(int i = 4; i < sieve_size;\
    \ i += 2) sieve[i] = false;\n            int sqrt_size = ceil(std::sqrt(sieve_size))\
    \ + 1;\n            for(int i = 3; i <= sqrt_size; i += 2){\n                if(!sieve[i])\
    \ continue;\n                for(int j = i * 2; j < sieve_size; j += i) sieve[j]\
    \ = false;\n            }\n            has_table_made = true;\n        }\n   \
    \     if(n < 0) n *= -1;\n        if(n < sieve_size) return sieve[n];\n      \
    \  \n        long long sqrt_n = ceil(std::sqrt(n)) + 1;\n        if(n % 2 == 0)\
    \ return false;\n        for(long long i = 3; i <= sqrt_n; i += 2){\n        \
    \    if(!sieve[i]) continue;\n            if(n % i == 0) return false;\n     \
    \   }\n        return true;\n    }\n\n    static const std::vector<bool> &table(){\
    \ return sieve; }\n};\nstd::vector<bool> prime_number_utility::sieve;\nbool prime_number_utility::has_table_made\
    \ = false;\n\n\n\n#line 5 \"math/primes_list.hpp\"\n\n// \u6607\u9806\u306E\u7D20\
    \u6570\u30EA\u30B9\u30C8\nclass primes_list{\n  protected:\n    static std::vector<int>\
    \ primes;\n\n  private:\n    static void expand(int nex){\n        int i = (primes.empty()\
    \ ? 2 : primes.back() + 1);\n        while((int)primes.size() < nex){\n      \
    \      if(prime_number_utility::is_prime(i)) primes.push_back(i);\n          \
    \  i++;\n        }\n    }\n\n  public:\n    primes_list() = delete;\n    ~primes_list()\
    \ = delete;\n\n\tstatic void resize(int siz){\n\t\tif((int)primes.size() > siz){\n\
    \t\t\twhile(primes.size() - siz > 0){\n\t\t\t\tprimes.pop_back();\n\t\t\t}\n\t\
    \t}\n\t\telse{\n\t\t\texpand(siz);\n\t\t}\n\t}\n\n\t// primes.back() \u304C lim\
    \ \u3092\u8D85\u3048\u308B\u307E\u3067\u62E1\u5F35\n\tstatic void set_lower_limit(int\
    \ lim){\n\t\twhile(primes.empty() || primes.back() < lim){\n\t\t\texpand(primes.size()\
    \ + 1);\n\t\t}\n\t}\n\n    static const std::vector<int> &list(){ return primes;\
    \ }\n};\nstd::vector<int> primes_list::primes;\n\n\n#line 6 \"math/factorize.hpp\"\
    \n\n/* \u7D20\u56E0\u6570\u5206\u89E3\n * prime_factorize(p1^e1 * p2^e2 * ...)\
    \ => {{p1, e1}, {p2, e2], ...}\n * prime_factorize(1) => {}\n * prime_factorize(0)\
    \ => {{0, 1}}\n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7267865\n\
    \ */ \nstd::vector<std::pair<long long, int>> factorize(long long N){\n    std::vector<std::pair<long\
    \ long, int>> ret;\n    primes_list::set_lower_limit(ceil(sqrt(N)));\n    long\
    \ long p;\n    for(int i=0; p = primes_list::list()[i], p * p <= N; i++){\n  \
    \      while(N % p == 0){\n            if(ret.empty() || ret.back().first != p)\
    \ ret.push_back({p, 1});\n            else ret.back().second++;\n            N\
    \ /= p;\n        }\n        if(N == 1) break;\n    }\n    if(N != 1) ret.push_back({N,\
    \ 1});\n    return ret;\n}\n\n\n#line 5 \"math/totient.hpp\"\n\n/* \u30AA\u30A4\
    \u30E9\u30FC\u95A2\u6570\n * O(\u221AN)\n * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7267874\n\
    \ */\nlong long totient(long long n){\n\tstd::vector<std::pair<long long, int>>\
    \ facs = factorize(n);\n\tlong long ret = 1;\n\tfor(std::pair<long long, int>\
    \ p : facs) ret *= power(p.first, p.second - 1) * (p.first - 1);\n\treturn ret;\n\
    }\n\n\n"
  code: "#ifndef TOTIENT\n#define TOTIENT\n#include \"../standard/power.hpp\"\n#include\
    \ \"factorize.hpp\"\n\n/* \u30AA\u30A4\u30E9\u30FC\u95A2\u6570\n * O(\u221AN)\n\
    \ * verify : https://judge.u-aizu.ac.jp/onlinejudge/review.jsp?rid=7267874\n */\n\
    long long totient(long long n){\n\tstd::vector<std::pair<long long, int>> facs\
    \ = factorize(n);\n\tlong long ret = 1;\n\tfor(std::pair<long long, int> p : facs)\
    \ ret *= power(p.first, p.second - 1) * (p.first - 1);\n\treturn ret;\n}\n\n#endif"
  dependsOn:
  - standard/power.hpp
  - math/factorize.hpp
  - math/primes_list.hpp
  - math/prime_number_utility.hpp
  isVerificationFile: false
  path: math/totient.hpp
  requiredBy: []
  timestamp: '2023-06-12 02:08:44+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/totient.hpp
layout: document
redirect_from:
- /library/math/totient.hpp
- /library/math/totient.hpp.html
title: math/totient.hpp
---
