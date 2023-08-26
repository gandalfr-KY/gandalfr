---
data:
  _extendedDependsOn:
  - icon: ':heavy_check_mark:'
    path: math/Eratosthenes.hpp
    title: "\u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\u30DD\u30FC\u30C8\
      \u3059\u308B\u30AF\u30E9\u30B9"
  - icon: ':heavy_check_mark:'
    path: math/enumeration_utility.hpp
    title: math/enumeration_utility.hpp
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
    PROBLEM: https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A
    links:
    - https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A
  bundledCode: "#line 1 \"test/ntl-1-a.test.cpp\"\n#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A\"\
    \n#include <bits/stdc++.h>\n#line 4 \"math/Eratosthenes.hpp\"\n\n#line 6 \"math/Eratosthenes.hpp\"\
    \n\n#line 6 \"math/enumeration_utility.hpp\"\n\n#line 5 \"standard/mod_integer.hpp\"\
    \n\ninline long long mod_inverse(long long a, int mod) {\n    assert(mod > 0);\n\
    \    long long b = mod, u = 1, v = 0;\n    while (b) {\n        long long t =\
    \ a / b;\n        a -= t * b, std::swap(a, b);\n        u -= t * v, std::swap(u,\
    \ v);\n    }\n    u %= mod;\n    if (u < 0)\n        u += mod;\n    return u;\n\
    }\n\n// mod_integer<P> a := P\u3092\u6CD5\u3068\u3059\u308B\u3068\u304D\u306E\u6574\
    \u6570\u578B;\ntemplate <int mod> class mod_integer {\n  private:\n    long long\
    \ val; // \u5024\u306F\u5FC5\u305A 0 <= val < mod \u306B\u4FDD\u305F\u308C\u308B\
    \n    friend mod_integer operator+(const mod_integer &a) { return a; }\n    friend\
    \ mod_integer operator-(const mod_integer &a) { return -a.val; }\n    friend mod_integer\
    \ operator+(const mod_integer &a, const mod_integer &b) {\n        return mod_integer(a.val\
    \ + b.val);\n    }\n    friend mod_integer operator-(const mod_integer &a, const\
    \ mod_integer &b) {\n        return mod_integer(a.val - b.val);\n    }\n    friend\
    \ mod_integer operator*(const mod_integer &a, const mod_integer &b) {\n      \
    \  return mod_integer(a.val * b.val);\n    }\n    friend mod_integer operator/(const\
    \ mod_integer &a, const mod_integer &b) {\n        return mod_integer((a.val *\
    \ mod_inverse(b.val, mod)) % mod);\n    }\n\n    friend bool operator==(const\
    \ mod_integer &a, const mod_integer &b) {\n        return a.val == b.val;\n  \
    \  }\n    friend bool operator!=(const mod_integer &a, const mod_integer &b) {\n\
    \        return a.val != b.val;\n    }\n\n    // map \u3068\u304B\u306B\u4E57\u305B\
    \u305F\u3044\u306E\u3067\u3001\u4FBF\u5B9C\u7684\u306B\u5B9A\u7FA9\n    friend\
    \ bool operator<(const mod_integer &a, const mod_integer &b) {\n        return\
    \ a.val < b.val;\n    }\n\n  public:\n    mod_integer(long long n) : val(n) {\n\
    \        val %= mod;\n        if (val < 0)\n            val += mod;\n    }\n \
    \   mod_integer() : val(0) {}\n    int value() const { return (int)val; }\n\n\
    \    mod_integer &operator=(const mod_integer &a) = default;\n    mod_integer\
    \ &operator+=(const mod_integer &a) {\n        val += a.val;\n        if (val\
    \ >= mod)\n            val -= mod;\n        return *this;\n    }\n    mod_integer\
    \ &operator-=(const mod_integer &a) {\n        val -= a.val;\n        if (val\
    \ < 0)\n            val += mod;\n        return *this;\n    }\n    mod_integer\
    \ &operator*=(const mod_integer &a) {\n        (val *= a.val) %= mod;\n      \
    \  return *this;\n    }\n    mod_integer &operator/=(const mod_integer &a) {\n\
    \        (val *= mod_inverse(a.val, mod)) %= mod;\n        return *this;\n   \
    \ }\n\n    friend std::istream &operator>>(std::istream &is, mod_integer &a) {\n\
    \        is >> a.val;\n        a.val %= mod;\n        if (a.val < 0)\n       \
    \     a.val += mod;\n        return is;\n    }\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const mod_integer &a) {\n        os << a.val;\n        return os;\n   \
    \ }\n};\n\n// d_mod_integer<P> a := P\u3092\u6CD5\u3068\u3059\u308B\u3068\u304D\
    \u306E\u6574\u6570\u578B;\ntemplate <int id> class dynamic_mod_integer {\n  private:\n\
    \    using d_mod_integer = dynamic_mod_integer<id>;\n    static inline int mod\
    \ = 998244353;\n    long long val; // \u5024\u306F\u5FC5\u305A 0 <= val < mod\
    \ \u306B\u4FDD\u305F\u308C\u308B\n    friend d_mod_integer operator+(const d_mod_integer\
    \ &a) { return a; }\n    friend d_mod_integer operator-(const d_mod_integer &a)\
    \ { return -a.val; }\n    friend d_mod_integer operator+(const d_mod_integer &a,\n\
    \                                   const d_mod_integer &b) {\n        return\
    \ d_mod_integer(a.val + b.val);\n    }\n    friend d_mod_integer operator-(const\
    \ d_mod_integer &a,\n                                   const d_mod_integer &b)\
    \ {\n        return d_mod_integer(a.val - b.val);\n    }\n    friend d_mod_integer\
    \ operator*(const d_mod_integer &a,\n                                   const\
    \ d_mod_integer &b) {\n        return d_mod_integer(a.val * b.val);\n    }\n \
    \   friend d_mod_integer operator/(const d_mod_integer &a,\n                 \
    \                  const d_mod_integer &b) {\n        return d_mod_integer((a.val\
    \ * mod_inverse(b.val, mod)) % mod);\n    }\n\n    friend bool operator==(const\
    \ d_mod_integer &a, const d_mod_integer &b) {\n        return a.val == b.val;\n\
    \    }\n    friend bool operator!=(const d_mod_integer &a, const d_mod_integer\
    \ &b) {\n        return a.val != b.val;\n    }\n\n    // map \u3068\u304B\u306B\
    \u4E57\u305B\u305F\u3044\u306E\u3067\u3001\u4FBF\u5B9C\u7684\u306B\u5B9A\u7FA9\
    \n    friend bool operator<(const d_mod_integer &a, const d_mod_integer &b) {\n\
    \        return a.val < b.val;\n    }\n\n  public:\n    dynamic_mod_integer(long\
    \ long n) : val(n) {\n        val %= mod;\n        if (val < 0)\n            val\
    \ += mod;\n    }\n    dynamic_mod_integer() : val(0) {}\n    int value() const\
    \ { return (int)val; }\n    static void set_mod(int _mod) {\n        assert(_mod\
    \ >= 0);\n        mod = _mod;\n    }\n\n    d_mod_integer &operator=(const d_mod_integer\
    \ &a) = default;\n    d_mod_integer &operator+=(const d_mod_integer &a) {\n  \
    \      val += a.val;\n        if (val >= mod)\n            val -= mod;\n     \
    \   return *this;\n    }\n    d_mod_integer &operator-=(const d_mod_integer &a)\
    \ {\n        val -= a.val;\n        if (val < 0)\n            val += mod;\n  \
    \      return *this;\n    }\n    d_mod_integer &operator*=(const d_mod_integer\
    \ &a) {\n        (val *= a.val) %= mod;\n        return *this;\n    }\n    d_mod_integer\
    \ &operator/=(const d_mod_integer &a) {\n        (val *= mod_inverse(a.val, mod))\
    \ %= mod;\n        return *this;\n    }\n\n    friend std::istream &operator>>(std::istream\
    \ &is, d_mod_integer &a) {\n        is >> a.val;\n        a.val %= mod;\n    \
    \    if (a.val < 0)\n            a.val += mod;\n        return is;\n    }\n  \
    \  friend std::ostream &operator<<(std::ostream &os, const d_mod_integer &a) {\n\
    \        os << a.val;\n        return os;\n    }\n};\n\nusing mint = mod_integer<1000000007>;\n\
    using _mint = mod_integer<998244353>;\nusing dmint = dynamic_mod_integer<-1>;\n\
    #line 8 \"math/enumeration_utility.hpp\"\n\ntemplate <class T> T power(T x, long\
    \ long n) {\n    T ret = static_cast<T>(1);\n    while (n > 0) {\n        if (n\
    \ & 1)\n            ret = ret * x;\n        x = x * x;\n        n >>= 1;\n   \
    \ }\n    return ret;\n}\n\nlong long power(long long x, long long n) {\n    long\
    \ long ret = 1;\n    while (n > 0) {\n        if (n & 1)\n            ret = ret\
    \ * x;\n        x = x * x;\n        n >>= 1;\n    }\n    return ret;\n}\n\nlong\
    \ long power(long long x, long long n, int MOD) {\n    long long ret = 1;\n  \
    \  x %= MOD;\n    while (n > 0) {\n        if (n & 1)\n            ret = ret *\
    \ x % MOD;\n        x = x * x % MOD;\n        n >>= 1;\n    }\n    return ret;\n\
    }\n\nlong long power(long long x, long long n, long long MOD) {\n    long long\
    \ ret = 1;\n    x %= MOD;\n    while (n > 0) {\n        if (n & 1)\n         \
    \   ret = (__int128_t)ret * x % MOD;\n        x = (__int128_t)x * x % MOD;\n \
    \       n >>= 1;\n    }\n    return ret;\n}\n\ntemplate <class T> class factorial\
    \ {\n  private:\n    static inline std::vector<T> fact{T(1)};\n\n  public:\n \
    \   factorial() = delete;\n    ~factorial() = delete;\n    static T get(int n)\
    \ {\n        while (n >= (int)fact.size())\n            fact.push_back(fact.back()\
    \ * fact.size());\n        return fact[n];\n    }\n};\nmint (*fact)(int) = factorial<mint>::get;\n\
    _mint (*_fact)(int) = factorial<_mint>::get;\n\ntemplate <class T> T permutation(int\
    \ n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ / factorial<T>::get(n - k);\n}\nmint (*perm)(int, int) = permutation<mint>;\n\
    _mint (*_perm)(int, int) = permutation<_mint>;\n\ntemplate <class T> static T\
    \ combnation(int n, int k) {\n    assert(0 <= k && k <= n);\n    return factorial<T>::get(n)\
    \ /\n           (factorial<T>::get(k) * factorial<T>::get(n - k));\n}\nmint (*comb)(int,\
    \ int) = combnation<mint>;\n_mint (*_comb)(int, int) = combnation<_mint>;\n#line\
    \ 8 \"math/Eratosthenes.hpp\"\n\n/**\n * @see https://drken1215.hatenablog.com/entry/2023/05/23/233000\n\
    \ */\nbool MillerRabin(long long N, const std::vector<long long> &A) {\n    long\
    \ long s = 0, d = N - 1;\n    while (d % 2 == 0) {\n        ++s;\n        d >>=\
    \ 1;\n    }\n    for (auto a : A) {\n        if (N <= a)\n            return true;\n\
    \        long long t, x = power(a, d, N);\n        if (x != 1) {\n           \
    \ for (t = 0; t < s; ++t) {\n                if (x == N - 1)\n               \
    \     break;\n                x = (__int128_t)x * x % N;\n            }\n    \
    \        if (t == s)\n                return false;\n        }\n    }\n    return\
    \ true;\n}\n\n/**\n * @brief \u7D20\u6570\u5224\u5B9A\u3084\u5217\u6319\u3092\u30B5\
    \u30DD\u30FC\u30C8\u3059\u308B\u30AF\u30E9\u30B9\n * @brief \u7D20\u6570\u7BE9\
    \u3092\u56FA\u5B9A\u30B5\u30A4\u30BA\u3067\u69CB\u7BC9\u3001\u305D\u308C\u3092\
    \u3082\u3068\u306B\u7D20\u6570\u5217\u6319\u306A\u3069\u3092\u884C\u3046\n * @attention\
    \ \u69CB\u7BC9\u30B5\u30A4\u30BA\u304C (2^23) \u3067\u304A\u3088\u305D 0.5s\n\
    \ */\nclass Eratosthenes {\n  protected:\n    static inline int seive_size = (1\
    \ << 23);\n    static inline std::vector<bool> sieve;\n    static inline std::vector<int>\
    \ primes{2, 3}, movius, min_factor;\n\n    static void make_table() {\n      \
    \  sieve.assign(seive_size, true);\n        sieve[0] = sieve[1] = false;\n   \
    \     movius.assign(seive_size, 1);\n        min_factor.assign(seive_size, 1);\n\
    \        for (int i = 2; i <= seive_size; ++i) {\n            if (!sieve[i])\n\
    \                continue;\n            movius[i] = -1;\n            min_factor[i]\
    \ = i;\n            primes.push_back(i);\n            for (int j = i * 2; j <\
    \ seive_size; j += i) {\n                sieve[j] = false;\n                movius[j]\
    \ = ((j / i) % i == 0 ? 0 : -movius[j]);\n                if (min_factor[j] ==\
    \ 1)\n                    min_factor[j] = i;\n            }\n        }\n    }\n\
    \n    static std::vector<std::pair<long long, int>> fast_factorize(long long n)\
    \ {\n        std::vector<std::pair<long long, int>> ret;\n        while (n > 1)\
    \ {\n            if (ret.empty() || ret.back().first != min_factor[n]) {\n   \
    \             ret.push_back({min_factor[n], 1});\n            } else {\n     \
    \           ret.back().second++;\n            }\n            n /= min_factor[n];\n\
    \        }\n        return ret;\n    }\n\n    static std::vector<std::pair<long\
    \ long, int>> naive_factorize(long long n) {\n        std::vector<std::pair<long\
    \ long, int>> ret;\n        for (long long p : primes) {\n            if (n ==\
    \ 1 || p * p > n)\n                break;\n            while (n % p == 0) {\n\
    \                if (ret.empty() || ret.back().first != p)\n                 \
    \   ret.push_back({p, 1});\n                else\n                    ret.back().second++;\n\
    \                n /= p;\n            }\n        }\n        if (n != 1)\n    \
    \        ret.push_back({n, 1});\n        return ret;\n    }\n\n  public:\n   \
    \ Eratosthenes() = delete;\n    ~Eratosthenes() = delete;\n\n    static void set_sieve_size(int\
    \ size) {\n        assert(sieve.empty());\n        seive_size = size;\n    }\n\
    \n    /**\n     * @brief n \u304C\u7D20\u6570\u304B\u3092\u5224\u5B9A\n     */\n\
    \    static bool is_prime(long long n) {\n        if (sieve.empty())\n       \
    \     make_table();\n        assert(1 <= n);\n\n        if (n > 2 && (n & 1LL)\
    \ == 0) {\n            return false;\n        } else if (n < seive_size) {\n \
    \           return sieve[n];\n        } else if (n < 4759123141LL) {\n       \
    \     return MillerRabin(n, {2, 7, 61});\n        } else {\n            return\
    \ MillerRabin(\n                n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});\n\
    \        }\n    }\n\n    /**\n     * @brief \u7D20\u56E0\u6570\u5206\u89E3\u3059\
    \u308B\n     * @return factorize(p1^e1 * p2^e2 * ...) => {{p1, e1}, {p2, e2],\
    \ ...},\n     * @return factorize(1) => {}\n     */\n    static std::vector<std::pair<long\
    \ long, int>> factorize(long long n) {\n        if (sieve.empty())\n         \
    \   make_table();\n        assert(1 <= n);\n\n        if (n < seive_size) {\n\
    \            return fast_factorize(n);\n        } else {\n            return naive_factorize(n);\n\
    \        }\n    }\n\n    static int Movius(int n) {\n        if (movius.empty())\n\
    \            make_table();\n        assert(1 <= n);\n        return movius.at(n);\n\
    \    }\n\n    /**\n     * @brief \u7D04\u6570\u5217\u6319\n     * @attention if\
    \ n < sieve_size : O(N^(1/loglogN))\n     */\n    template <bool sort = true>\n\
    \    static std::vector<long long> divisors(long long n) {\n        std::vector<long\
    \ long> ds;\n        auto facs(factorize(n));\n        auto rec = [&](auto self,\
    \ long long d, int cu) -> void {\n            if (cu == (int)facs.size()) {\n\
    \                ds.push_back(d);\n                return;\n            }\n  \
    \          for (int e = 0; e <= facs[cu].second; ++e) {\n                self(self,\
    \ d, cu + 1);\n                d *= facs[cu].first;\n            }\n        };\n\
    \        rec(rec, 1LL, 0);\n        if constexpr (sort)\n            std::sort(ds.begin(),\
    \ ds.end());\n        return ds;;\n    }\n\n    /**\n     * @brief \u30AA\u30A4\
    \u30E9\u30FC\u306E\u30C8\u30FC\u30B7\u30A7\u30F3\u30C8\u95A2\u6570\n     */\n\
    \    static long long totient(long long n) {\n        long long ret = 1;\n   \
    \     for (auto [b, e] : factorize(n))\n            ret *= power(b, e - 1) * (b\
    \ - 1);\n        return ret;\n    }\n\n\n    static int kth_prime(int k) { return\
    \ primes.at(k); }\n};\n#line 4 \"test/ntl-1-a.test.cpp\"\nusing namespace std;\n\
    using ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    \nint main(void){\n \n    //input\n\n    int N;\n    cin >> N;\n\n    //calculate\n\
    \n    cout << N << \":\";\n    for(auto p : Eratosthenes::factorize(N)){\n   \
    \     rep(i,0,p.second) cout << \" \" << p.first;\n    }\n    cout << endl;\n\n\
    }\n"
  code: "#define PROBLEM \"https://onlinejudge.u-aizu.ac.jp/problems/NTL_1_A\"\n#include\
    \ <bits/stdc++.h>\n#include \"../math/Eratosthenes.hpp\"\nusing namespace std;\n\
    using ll = long long;\n#define rep(i, j, n) for(ll i = (ll)(j); i < (ll)(n); i++)\n\
    \nint main(void){\n \n    //input\n\n    int N;\n    cin >> N;\n\n    //calculate\n\
    \n    cout << N << \":\";\n    for(auto p : Eratosthenes::factorize(N)){\n   \
    \     rep(i,0,p.second) cout << \" \" << p.first;\n    }\n    cout << endl;\n\n\
    }"
  dependsOn:
  - math/Eratosthenes.hpp
  - math/enumeration_utility.hpp
  - standard/mod_integer.hpp
  isVerificationFile: true
  path: test/ntl-1-a.test.cpp
  requiredBy: []
  timestamp: '2023-08-26 20:18:13+09:00'
  verificationStatus: TEST_ACCEPTED
  verifiedWith: []
documentation_of: test/ntl-1-a.test.cpp
layout: document
redirect_from:
- /verify/test/ntl-1-a.test.cpp
- /verify/test/ntl-1-a.test.cpp.html
title: test/ntl-1-a.test.cpp
---
