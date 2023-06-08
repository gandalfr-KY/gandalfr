---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/integer/prime_number_utility.hpp
    title: math/integer/prime_number_utility.hpp
  _extendedRequiredBy:
  - icon: ':warning:'
    path: math/integer/factorize.hpp
    title: math/integer/factorize.hpp
  - icon: ':warning:'
    path: math/integer/totient.hpp
    title: math/integer/totient.hpp
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/integer/primes_list.hpp\"\n\n\n#include <assert.h>\n\
    #line 1 \"math/integer/prime_number_utility.hpp\"\n\n\n#include <vector>\n#include\
    \ <math.h>\n\n/* is_prime::judge(n) := |n|\u304C\u7D20\u6570\u304B\u3069\u3046\
    \u304B\n * \u5224\u5B9A\u8868\u3092\u306A\u3089\u3057\u6642\u9593 O(NloglogN)\
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
    \ = false;\n\n\n\n#line 5 \"math/integer/primes_list.hpp\"\n\n// \u6607\u9806\u306E\
    \u7D20\u6570\u30EA\u30B9\u30C8\nclass primes_list{\n  protected:\n    static std::vector<int>\
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
    \ }\n};\nstd::vector<int> primes_list::primes;\n\n\n"
  code: "#ifndef PRIMES_LIST\n#define PRIMES_LIST\n#include <assert.h>\n#include \"\
    prime_number_utility.hpp\"\n\n// \u6607\u9806\u306E\u7D20\u6570\u30EA\u30B9\u30C8\
    \nclass primes_list{\n  protected:\n    static std::vector<int> primes;\n\n  private:\n\
    \    static void expand(int nex){\n        int i = (primes.empty() ? 2 : primes.back()\
    \ + 1);\n        while((int)primes.size() < nex){\n            if(prime_number_utility::is_prime(i))\
    \ primes.push_back(i);\n            i++;\n        }\n    }\n\n  public:\n    primes_list()\
    \ = delete;\n    ~primes_list() = delete;\n\n\tstatic void resize(int siz){\n\t\
    \tif((int)primes.size() > siz){\n\t\t\twhile(primes.size() - siz > 0){\n\t\t\t\
    \tprimes.pop_back();\n\t\t\t}\n\t\t}\n\t\telse{\n\t\t\texpand(siz);\n\t\t}\n\t\
    }\n\n\t// primes.back() \u304C lim \u3092\u8D85\u3048\u308B\u307E\u3067\u62E1\u5F35\
    \n\tstatic void set_lower_limit(int lim){\n\t\twhile(primes.empty() || primes.back()\
    \ < lim){\n\t\t\texpand(primes.size() + 1);\n\t\t}\n\t}\n\n    static const std::vector<int>\
    \ &list(){ return primes; }\n};\nstd::vector<int> primes_list::primes;\n\n#endif"
  dependsOn:
  - math/integer/prime_number_utility.hpp
  isVerificationFile: false
  path: math/integer/primes_list.hpp
  requiredBy:
  - math/integer/factorize.hpp
  - math/integer/totient.hpp
  timestamp: '2023-06-06 22:24:51+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/integer/primes_list.hpp
layout: document
redirect_from:
- /library/math/integer/primes_list.hpp
- /library/math/integer/primes_list.hpp.html
title: math/integer/primes_list.hpp
---
