---
data:
  _extendedDependsOn:
  - icon: ':warning:'
    path: math/polynomial/polynomial.hpp
    title: math/polynomial/polynomial.hpp
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: hpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"math/polynomial/differentiate.hpp\"\n\n\n#line 1 \"math/polynomial/polynomial.hpp\"\
    \n\n\n\ntemplate<class coef>\nclass polynomial{\n  private:\n    std::vector<coef>\
    \ p;\n    std::string variable_name = \"x\";\n\n    const friend polynomial operator+(const\
    \ polynomial &a){\n        return a;\n    }\n\n    const friend polynomial operator-(const\
    \ polynomial &a){\n        polynomial<coef> ret(a);\n        for(coef &c : ret)\
    \ c *= -1;\n        return ret;\n    }\n\n    friend const polynomial operator+(const\
    \ polynomial &a, const polynomial &b){\n        int siz = std::max(a.p.size(),\
    \ b.p.size());\n        int siz1 = a.p.size(), siz2 = b.p.size();\n        polynomial\
    \ ret;\n        ret.p.resize(siz);\n        for(int i=0; i<siz; i++){\n      \
    \      ret.p[i] = (i < siz1 ? a.p[i] : 0) + (i < siz2 ? b.p[i] : 0);\n       \
    \ }\n        while(ret.p.back() == 0 && ret.p.size() != 1) ret.p.pop_back();\n\
    \        return ret;\n    }\n\n    friend const polynomial operator-(const polynomial\
    \ &a, const polynomial &b){\n        int siz = std::max(a.p.size(), b.p.size());\n\
    \        int siz1 = a.p.size(), siz2 = b.p.size();\n        polynomial ret;\n\
    \        ret.p.resize(siz);\n        for(int i=0; i<siz; i++){\n            ret.p[i]\
    \ = (i < siz1 ? a.p[i] : 0) - (i < siz2 ? b.p[i] : 0);\n        }\n        while(ret.p.back()\
    \ == 0 && ret.p.size() != 1) ret.p.pop_back();\n        return ret;\n    }\n\n\
    \    friend const polynomial operator*(const polynomial &a, const polynomial &b){\n\
    \        int siz1 = a.p.size(), siz2 = b.p.size();\n        polynomial ret;\n\
    \        ret.p.resize(siz1 + siz2 - 1);\n        for(int i=0; i<siz1; i++) for(int\
    \ j=0; j<siz2; j++) ret.p[i + j] += a.p[i] * b.p[j];\n        return ret;\n  \
    \  }\n\n    friend const polynomial operator/(const polynomial &a, const polynomial\
    \ &b){\n        int siz1 = a.p.size(), siz2 = b.p.size();\n        if(siz1 < siz2)\
    \ return {0};\n        polynomial ret, remain(a);\n        ret.p.resize(siz1 -\
    \ siz2 + 1, 0);\n        for(int i=siz1-siz2; i>=0; i--){\n            ret.p[i]\
    \ = remain.p.back() / b.p.back();\n            for(int j=1; j<siz2; j++){\n  \
    \              remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];\n \
    \           }\n            remain.p.pop_back();\n        }\n        return ret;\n\
    \    }\n\n    friend const polynomial operator%(const polynomial &a, const polynomial\
    \ &b){\n        int siz1 = a.p.size(), siz2 = b.p.size();\n        if(siz1 < siz2)\
    \ return {0};\n        polynomial ret, remain(a);\n        ret.p.resize(siz1 -\
    \ siz2 + 1, 0);\n        for(int i=siz1-siz2; i>=0; i--){\n            ret.p[i]\
    \ = remain.p.back() / b.p.back();\n            for(int j=1; j<siz2; j++){\n  \
    \              remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];\n \
    \           }\n            remain.p.pop_back();\n        }\n        return remain;\n\
    \    }\n\n    friend int compare(const polynomial &a, const polynomial &b){\n\
    \        int siz1 = a.p.size();\n        int siz2 = b.p.size();\n        if(siz1\
    \ > siz2) return +1;\n        if(siz1 < siz2) return -1;\n        for(int i=siz1-1;\
    \ i>=0; i--) {\n            if(a.p[i] > b.p[i]) return +1;\n            if(a.p[i]\
    \ < b.p[i]) return -1;\n        }\n        return 0;\n    }\n\n    friend bool\
    \ operator==(const polynomial &a, const polynomial &b){\n        return (compare(a,\
    \ b) == 0);\n    }\n\n    friend bool operator!=(const polynomial &a, const polynomial\
    \ &b){\n        return (compare(a, b) != 0);\n    }\n\n    friend bool operator<(const\
    \ polynomial &a, const polynomial &b){\n        return (compare(a, b) < 0);\n\
    \    }\n\n    friend bool operator<=(const polynomial &a, const polynomial &b){\n\
    \        return (compare(a, b) <= 0);\n    }\n\n    friend bool operator>(const\
    \ polynomial &a, const polynomial &b){\n        return (compare(a, b) > 0);\n\
    \    }\n\n    friend bool operator>=(const polynomial &a, const polynomial &b){\n\
    \        return (compare(a, b) >= 0);\n    }\n\n  public:\n    polynomial(const\
    \ std::vector<coef> &vec) : p(vec) {\n        while(p.back() == 0 && p.size()\
    \ != 1) p.pop_back();\n    }\n    polynomial(const coef &n = 0)  : polynomial(std::vector<coef>{n})\
    \ {}\n\n    int max_order() const {\n        return p.size() - 1;\n    }\n   \
    \ \n    coef get(int n) const {\n        assert(0 <= n);\n        return (n <\
    \ p.size() ? p[n] : 0);\n    }\n\n    void set(int n, const coef &x){\n      \
    \  assert(0 <= n);\n        if(n >= p.size()) p.resize(n + 1, 0);\n        p[n]\
    \ = x;\n        while(p.back() == 0 && p.size() != 1) p.pop_back();\n    }\n\n\
    \    polynomial &operator=(const polynomial &a){\n        p = a.p;\n        return\
    \ *this;\n    }\n\n    void operator+=(const polynomial &a){\n        *this =\
    \ operator+(*this, a);\n    }\n\n    void operator-=(const polynomial &a){\n \
    \       *this = operator-(*this, a);\n    }\n\n    void operator*=(const polynomial\
    \ &a){\n        *this = operator*(*this, a);\n    }\n\n    void operator/=(const\
    \ polynomial &a){\n        *this = operator/(*this, a);\n    }\n\n    void operator%=(const\
    \ polynomial &a){\n        *this = operator%(*this, a);\n    }\n\n    coef operator[](int\
    \ n) const{\n        return get(n);\n    }\n    \n    coef operator()(const coef\
    \ &x) const{\n        coef ret = 0;\n        coef pwr = 1;\n        for(int i=0;\
    \ i<p.size(); i++){\n            ret += p[i] * pwr;\n            pwr *= x;\n \
    \       }\n        return ret;\n    }\n    \n    friend std::ostream &operator<<(std::ostream\
    \ &os, const polynomial &a) {\n        if(a.p.size() == 1 && a.p[0] == 0) os <<\
    \ \"0\";\n        else for(int i=a.p.size()-1; i>=0; i--){\n            if(a.p[i]\
    \ == 0) continue;\n            std::string sign;\n            if(i != a.p.size()-1\
    \ && a.p[i] > 0) sign = \"+ \";\n            if(a.p[i] < 0) sign = \"- \";\n \
    \           os << sign << (a.p[i] >= 0 ? a.p[i] : a.p[i]) << ' ' << a.variable_name\
    \ << '^' << i << ' ';\n        }\n        return os;\n    }\n\n};\n\n\n\n#line\
    \ 4 \"math/polynomial/differentiate.hpp\"\n\ntemplate<class T>\npolynomial<T>\
    \ differentiate(polynomial<T> a){\n    polynomial<T> ret;\n    for(int i=0; i<a.max_order();\
    \ i++){\n        ret.set_coefficient(i, a.get_coefficient(i + 1) * (i + 1));\n\
    \    }\n    return ret;\n}\n\n\n"
  code: "#ifndef DIFFERENTIATE\n#define DIFFERENTIATE\n#include \"polynomial.hpp\"\
    \n\ntemplate<class T>\npolynomial<T> differentiate(polynomial<T> a){\n    polynomial<T>\
    \ ret;\n    for(int i=0; i<a.max_order(); i++){\n        ret.set_coefficient(i,\
    \ a.get_coefficient(i + 1) * (i + 1));\n    }\n    return ret;\n}\n\n#endif"
  dependsOn:
  - math/polynomial/polynomial.hpp
  isVerificationFile: false
  path: math/polynomial/differentiate.hpp
  requiredBy: []
  timestamp: '2023-06-06 22:51:20+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/polynomial/differentiate.hpp
layout: document
redirect_from:
- /library/math/polynomial/differentiate.hpp
- /library/math/polynomial/differentiate.hpp.html
title: math/polynomial/differentiate.hpp
---
