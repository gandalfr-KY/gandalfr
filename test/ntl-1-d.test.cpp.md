---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/enumeration_utility.hpp
    title: math/enumeration_utility.hpp
  - icon: ':heavy_check_mark:'
    path: math/prime_number_utility.hpp
    title: "\u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\u30DD\u30FC\u30C8\
      \u3059\u308B\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: math/totient.hpp
    title: "\u30AA\u30A4\u30E9\u30FC\u306E\u30C8\u30FC\u30B7\u30A7\u30F3\u30C8\u95A2\
      \u6570"
  - icon: ':question:'
    path: standard/mod_integer.hpp
    title: standard/mod_integer.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':heavy_check_mark:'
  attributes:
    '*NOT_SPECIAL_COMMENTS*': ''
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D
  bundledCode: "#line 1 \"test/ntl-1-d.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D\"\
    \n#include <bits/stdc++.h>\n#line 6 \"math/enumeration_utility.hpp\"\n\n#line\
    \ 5 \"standard/mod_integer.hpp\"\n\ninline long long mod_inverse(long long a,\
    \ int mod) {\n    assert(mod > 0);\n    long long b = mod, u = 1, v = 0;\n   \
    \ while (b) {\n        long long t = a / b;\n        a -= t * b, std::swap(a,\
    \ b);\n        u -= t * v, std::swap(u, v);\n    }\n    u %= mod;\n    if (u <\
    \ 0)\n        u += mod;\n    return u;\n}\n\n// mod_integer<P> a := P\u3092\u6CD5\
    \u3068\u3059\u308B\u3068\u304D\u306E\u6574\u6570\u578B;\ntemplate <int mod> class\
    \ mod_integer {\n  private:\n    long long val; // \u5024\u306F\u5FC5\u305A 0\
    \ <= val < mod \u306B\u4FDD\u305F\u308C\u308B\n    friend mod_integer operator+(const\
    \ mod_integer &a) { return a; }\n    friend mod_integer operator-(const mod_integer\
    \ &a) { return -a.val; }\n    friend mod_integer operator+(const mod_integer &a,\
    \ const mod_integer &b) {\n        return mod_integer(a.val + b.val);\n    }\n\
    \    friend mod_integer operator-(const mod_integer &a, const mod_integer &b)\
    \ {\n        return mod_integer(a.val - b.val);\n    }\n    friend mod_integer\
    \ operator*(const mod_integer &a, const mod_integer &b) {\n        return mod_integer(a.val\
    \ * b.val);\n    }\n    friend mod_integer operator/(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer((a.val * mod_inverse(b.val, mod))\
    \ % mod);\n    }\n\n    friend bool operator==(const mod_integer &a, const mod_integer\
    \ &b) {\n        return a.val == b.val;\n    }\n    friend bool operator!=(const\
    \ mod_integer &a, const mod_integer &b) {\n        return a.val != b.val;\n  \
    \  }\n\n    // map \u3068\u304B\u306B\u4E57\u305B\u305F\u3044\u306E\u3067\u3001\
    \u4FBF\u5B9C\u7684\u306B\u5B9A\u7FA9\n    friend bool operator<(const mod_integer\
    \ &a, const mod_integer &b) {\n        return a.val < b.val;\n    }\n\n  public:\n\
    \    mod_integer(long long n) : val(n) {\n        val %= mod;\n        if (val\
    \ < 0)\n            val += mod;\n    }\n    mod_integer() : val(0) {}\n    int\
    \ value() const { return (int)val; }\n\n    mod_integer &operator=(const mod_integer\
    \ &a) = default;\n    mod_integer &operator+=(const mod_integer &a) {\n      \
    \  val += a.val;\n        if (val >= mod)\n            val -= mod;\n        return\
    \ *this;\n    }\n    mod_integer &operator-=(const mod_integer &a) {\n       \
    \ val -= a.val;\n        if (val < 0)\n            val += mod;\n        return\
    \ *this;\n    }\n    mod_integer &operator*=(const mod_integer &a) {\n       \
    \ (val *= a.val) %= mod;\n        return *this;\n    }\n    mod_integer &operator/=(const\
    \ mod_integer &a) {\n        (val *= mod_inverse(a.val, mod)) %= mod;\n      \
    \  return *this;\n    }\n\n    friend std::istream &operator>>(std::istream &is,\
    \ mod_integer &a) {\n        is >> a.val;\n        a.val %= mod;\n        if (a.val\
    \ < 0)\n            a.val += mod;\n        return is;\n    }\n    friend std::ostream\
    \ &operator<<(std::ostream &os, const mod_integer &a) {\n        os << a.val;\n\
    \        return os;\n    }\n};\n\nusing mint = mod_integer<1000000007>;\nusing\
    \ _mint = mod_integer<998244353>;\n#line 8 \"math/enumeration_utility.hpp\"\n\n\
    template <class T> T power(T x, long long n) {\n    T ret = static_cast<T>(1);\n\
    \    while (n > 0) {\n        if (n & 1)\n            ret = ret * x;\n       \
    \ x = x * x;\n        n >>= 1;\n    }\n    return ret;\n}\n\nlong long power(long\
    \ long x, long long n) {\n    long long ret = 1;\n    while (n > 0) {\n      \
    \  if (n & 1)\n            ret = ret * x;\n        x = x * x;\n        n >>= 1;\n\
    \    }\n    return ret;\n}\n\nlong long power(long long x, long long n, int MOD)\
    \ {\n    long long ret = 1;\n    x %= MOD;\n    while (n > 0) {\n        if (n\
    \ & 1)\n            ret = ret * x % MOD;\n        x = x * x % MOD;\n        n\
    \ >>= 1;\n    }\n    return ret;\n}\n\ntemplate <class T> class factorial {\n\
    \  private:\n    static inline std::vector<T> fact{1};\n\n  public:\n    factorial()\
    \ = delete;\n    ~factorial() = delete;\n    static T get(int n) {\n        while\
    \ (n >= fact.size())\n            fact.push_back(fact.back() * fact.size());\n\
    \        return fact[n];\n    }\n};\nmint (*fact)(int) = factorial<mint>::get;\n\
    _mint (*_fact)(int) = factorial<_mint>::get;\n\ntemplate <class T> T permutation(int\
    \ n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ / factorial<T>::get(n - k);\n}\nmint (*perm)(int, int) = permutation<mint>;\n\
    _mint (*_perm)(int, int) = permutation<_mint>;\n\ntemplate <class T> static T\
    \ combnation(int n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ /\n           (factorial<T>::get(k) * factorial<T>::get(n - k));\n}\nmint (*comb)(int,\
    \ int) = combnation<mint>;\n_mint (*_comb)(int, int) = combnation<_mint>;\n#line\
    \ 3 \"math/prime_number_utility.hpp\"\n\n#line 5 \"math/prime_number_utility.hpp\"\
    \n\n/**\n * @brief \u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\u30DD\
    \u30FC\u30C8\u3059\u308B\u30AF\u30E9\u30B9\n * @brief \u7D20\u6570\u7BE9\u3092\
    \u56FA\u5B9A\u30B5\u30A4\u30BA\u3067\u69CB\u7BC9\u3001\u305D\u308C\u3092\u3082\
    \u3068\u306B\u7D20\u6570\u5217\u6319\u306A\u3069\u3092\u884C\u3046\n */\nclass\
    \ prime_number_utility {\n  protected:\n    static const int init_seive_size =\
    \ (1 << 24), sqrt_size = (1 << 13);\n    static inline std::vector<bool> sieve;\n\
    \    static inline std::vector<int> primes{2, 3};\n\n  public:\n    prime_number_utility()\
    \ = delete;\n    ~prime_number_utility() = delete;\n\n    /**\n     * @brief n\
    \ \u304C\u7D20\u6570\u304B\u3092\u5224\u5B9A\n     * @attention if n < (1 << 26)\
    \ : O(1)\n     * @attention else : O(\u221An)\n     */\n    static bool is_prime(long\
    \ long n) {\n        if (sieve.empty()) { // \u7BE9\u304C\u672A\u69CB\u7BC9\u306A\
    \u3089\n            sieve.assign(init_seive_size, true);\n            sieve[0]\
    \ = sieve[1] = false;\n            for (int i = 4; i < init_seive_size; i += 2)\n\
    \                sieve[i] = false;\n            for (int i = 3; i <= sqrt_size;\
    \ i += 2) {\n                if (!sieve[i])\n                    continue;\n \
    \               for (int j = i * 2; j < init_seive_size; j += i)\n           \
    \         sieve[j] = false;\n            }\n        }\n        if ((n & 1) ==\
    \ 0)\n            return 0;\n        // n \u304C\u5C0F\u3055\u3044\u3068\u304D\
    \u3001\u7BE9\u3092\u53C2\u7167\n        if (n < init_seive_size)\n           \
    \ return sieve[n];\n        // n \u304C\u5927\u304D\u3044\u3068\u304D\u3001O(\u221A\
    n) \u8A66\u3057\u5272\u308A\u3067\u8A08\u7B97\n        long long sqrt_n = std::ceil(std::sqrt(n))\
    \ + 1;\n        for (long long i = 3; i <= sqrt_n; i += 2) {\n            if (!sieve[i])\n\
    \                continue;\n            if (n % i == 0)\n                return\
    \ false;\n        }\n        return true;\n    }\n\n    static void expand_list(int\
    \ siz) {\n        for (int i = primes.back() + 2; (int)primes.size() < siz; i\
    \ += 2) {\n            if (is_prime(i))\n                primes.push_back(i);\n\
    \        }\n    }\n\n    // \u7D20\u6570\u306E\u30EA\u30B9\u30C8\u3092\u3001\u672B\
    \u5C3E\u306E\u6570\u304C lim \u3092\u8D85\u3048\u308B\u307E\u3067\u62E1\u5F35\n\
    \    static void set_lower_limit(int lim) {\n        while (primes.back() < lim)\n\
    \            expand_list(primes.size() + 1);\n    }\n\n    /**\n     * @brief\
    \ \u7D20\u56E0\u6570\u5206\u89E3\u3059\u308B\n     * @return prime_factorize(p1^e1\
    \ * p2^e2 * ...) => {{p1, e1}, {p2, e2], ...}\n     * @attention prime_factorize(1)\
    \ => {}\n     * @attention prime_factorize(0) => {{0, 1}}\n     */\n    static\
    \ std::vector<std::pair<long long, int>> factorize(long long N) {\n        std::vector<std::pair<long\
    \ long, int>> ret;\n        set_lower_limit(ceil(sqrt(N)));\n        for (long\
    \ long p : primes) {\n            if (N == 1 || (__int128_t)p * p > N)\n     \
    \           break;\n            while (N % p == 0) {\n                if (ret.empty()\
    \ || ret.back().first != p)\n                    ret.push_back({p, 1});\n    \
    \            else\n                    ret.back().second++;\n                N\
    \ /= p;\n            }\n        }\n        if (N != 1)\n            ret.push_back({N,\
    \ 1});\n        return ret;\n    }\n\n    static const std::vector<int> &list()\
    \ { return primes; }\n    static const std::vector<bool> &table() { return sieve;\
    \ }\n};\n#line 4 \"math/totient.hpp\"\n\n/**\n * @brief \u30AA\u30A4\u30E9\u30FC\
    \u306E\u30C8\u30FC\u30B7\u30A7\u30F3\u30C8\u95A2\u6570\n */\nlong long totient(long\
    \ long n) {\n    auto facs = prime_number_utility::factorize(n);\n    long long\
    \ ret = 1;\n    for (auto &p : facs)\n        ret *= power(p.first, p.second -\
    \ 1) * (p.first - 1);\n    return ret;\n}\n#line 4 \"test/ntl-1-d.test.cpp\"\n\
    using namespace std;\nusing ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j);\
    \ i < (ll)(n); i++)\n#define all(a) (a).begin(),(a).end()\n\nint main(void){\n\
    \    int N;\n    cin >> N;\n    cout << totient(N) << endl;\n}\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_D\"\n#include\
    \ <bits/stdc++.h>\n#include \"../math/totient.hpp\"\nusing namespace std;\nusing\
    \ ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    #define all(a) (a).begin(),(a).end()\n\nint main(void){\n    int N;\n    cin >>\
    \ N;\n    cout << totient(N) << endl;\n}"
  dependsOn:
  - math/totient.hpp
  - math/enumeration_utility.hpp
  - standard/mod_integer.hpp
  - math/prime_number_utility.hpp
  isVerificationFile: true
  path: test/ntl-1-d.test.cpp
  requiredBy: []
  timestamp: '2023-08-05 15:29:22+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ntl-1-d.test.cpp
layout: document
redirect_from:
- /verify/test/ntl-1-d.test.cpp
- /verify/test/ntl-1-d.test.cpp.html
title: test/ntl-1-d.test.cpp
---
