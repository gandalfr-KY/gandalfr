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
  bundledCode: "#line 2 \"math/polynomial.hpp\"\n#include <algorithm>\n#include <string>\n\
    #include <vector>\n\n/**\n * @deprecated \u7A4D\u304CO(n^2)\u3067\u304A\u305D\u3044\
    \u3002\u5F37\u3044\u4EBA\u306E\u30E9\u30A4\u30D6\u30E9\u30EA\u3092\u4F7F\u304A\
    \u3046\u3002\n */\ntemplate <class coef> class polynomial {\n  private:\n    std::vector<coef>\
    \ p;\n    std::string variable_name = \"x\";\n\n    const friend polynomial operator+(const\
    \ polynomial &a) { return a; }\n\n    const friend polynomial operator-(const\
    \ polynomial &a) {\n        polynomial<coef> ret(a);\n        for (coef &c : ret)\n\
    \            c *= -1;\n        return ret;\n    }\n\n    friend const polynomial\
    \ operator+(const polynomial &a,\n                                      const\
    \ polynomial &b) {\n        int siz = std::max(a.p.size(), b.p.size());\n    \
    \    int siz1 = a.p.size(), siz2 = b.p.size();\n        polynomial ret;\n    \
    \    ret.p.resize(siz);\n        for (int i = 0; i < siz; i++) {\n           \
    \ ret.p[i] = (i < siz1 ? a.p[i] : 0) + (i < siz2 ? b.p[i] : 0);\n        }\n \
    \       while (ret.p.back() == 0 && ret.p.size() != 1)\n            ret.p.pop_back();\n\
    \        return ret;\n    }\n\n    friend const polynomial operator-(const polynomial\
    \ &a,\n                                      const polynomial &b) {\n        int\
    \ siz = std::max(a.p.size(), b.p.size());\n        int siz1 = a.p.size(), siz2\
    \ = b.p.size();\n        polynomial ret;\n        ret.p.resize(siz);\n       \
    \ for (int i = 0; i < siz; i++) {\n            ret.p[i] = (i < siz1 ? a.p[i] :\
    \ 0) - (i < siz2 ? b.p[i] : 0);\n        }\n        while (ret.p.back() == 0 &&\
    \ ret.p.size() != 1)\n            ret.p.pop_back();\n        return ret;\n   \
    \ }\n\n    friend const polynomial operator*(const polynomial &a,\n          \
    \                            const polynomial &b) {\n        int siz1 = a.p.size(),\
    \ siz2 = b.p.size();\n        polynomial ret;\n        ret.p.resize(siz1 + siz2\
    \ - 1);\n        for (int i = 0; i < siz1; i++)\n            for (int j = 0; j\
    \ < siz2; j++)\n                ret.p[i + j] += a.p[i] * b.p[j];\n        return\
    \ ret;\n    }\n\n    friend const polynomial operator/(const polynomial &a,\n\
    \                                      const polynomial &b) {\n        int siz1\
    \ = a.p.size(), siz2 = b.p.size();\n        if (siz1 < siz2)\n            return\
    \ {0};\n        polynomial ret, remain(a);\n        ret.p.resize(siz1 - siz2 +\
    \ 1, 0);\n        for (int i = siz1 - siz2; i >= 0; i--) {\n            ret.p[i]\
    \ = remain.p.back() / b.p.back();\n            for (int j = 1; j < siz2; j++)\
    \ {\n                remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];\n\
    \            }\n            remain.p.pop_back();\n        }\n        return ret;\n\
    \    }\n\n    friend const polynomial operator%(const polynomial &a,\n       \
    \                               const polynomial &b) {\n        int siz1 = a.p.size(),\
    \ siz2 = b.p.size();\n        if (siz1 < siz2)\n            return {0};\n    \
    \    polynomial ret, remain(a);\n        ret.p.resize(siz1 - siz2 + 1, 0);\n \
    \       for (int i = siz1 - siz2; i >= 0; i--) {\n            ret.p[i] = remain.p.back()\
    \ / b.p.back();\n            for (int j = 1; j < siz2; j++) {\n              \
    \  remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];\n            }\n\
    \            remain.p.pop_back();\n        }\n        return remain;\n    }\n\n\
    \    friend int compare(const polynomial &a, const polynomial &b) {\n        int\
    \ siz1 = a.p.size();\n        int siz2 = b.p.size();\n        if (siz1 > siz2)\n\
    \            return +1;\n        if (siz1 < siz2)\n            return -1;\n  \
    \      for (int i = siz1 - 1; i >= 0; i--) {\n            if (a.p[i] > b.p[i])\n\
    \                return +1;\n            if (a.p[i] < b.p[i])\n              \
    \  return -1;\n        }\n        return 0;\n    }\n\n    friend bool operator==(const\
    \ polynomial &a, const polynomial &b) {\n        return (compare(a, b) == 0);\n\
    \    }\n\n    friend bool operator!=(const polynomial &a, const polynomial &b)\
    \ {\n        return (compare(a, b) != 0);\n    }\n\n    friend bool operator<(const\
    \ polynomial &a, const polynomial &b) {\n        return (compare(a, b) < 0);\n\
    \    }\n\n    friend bool operator<=(const polynomial &a, const polynomial &b)\
    \ {\n        return (compare(a, b) <= 0);\n    }\n\n    friend bool operator>(const\
    \ polynomial &a, const polynomial &b) {\n        return (compare(a, b) > 0);\n\
    \    }\n\n    friend bool operator>=(const polynomial &a, const polynomial &b)\
    \ {\n        return (compare(a, b) >= 0);\n    }\n\n  public:\n    polynomial(const\
    \ std::vector<coef> &vec) : p(vec) {\n        while (p.back() == 0 && p.size()\
    \ != 1)\n            p.pop_back();\n    }\n    polynomial(const coef &n = 0) :\
    \ polynomial(std::vector<coef>{n}) {}\n\n    int max_order() const { return p.size()\
    \ - 1; }\n\n    coef get_coef(int n) const {\n        assert(0 <= n);\n      \
    \  return (n < p.size() ? p[n] : 0);\n    }\n\n    void set_coef(int n, const\
    \ coef &x) {\n        assert(0 <= n);\n        if (n >= p.size())\n          \
    \  p.resize(n + 1, 0);\n        p[n] = x;\n        while (p.back() == 0 && p.size()\
    \ != 1)\n            p.pop_back();\n    }\n\n    polynomial &operator=(const polynomial\
    \ &a) {\n        p = a.p;\n        return *this;\n    }\n\n    void operator+=(const\
    \ polynomial &a) { *this = operator+(*this, a); }\n\n    void operator-=(const\
    \ polynomial &a) { *this = operator-(*this, a); }\n\n    void operator*=(const\
    \ polynomial &a) { *this = operator*(*this, a); }\n\n    void operator/=(const\
    \ polynomial &a) { *this = operator/(*this, a); }\n\n    void operator%=(const\
    \ polynomial &a) { *this = operator%(*this, a); }\n\n    coef operator[](int n)\
    \ const { return get_coef(n); }\n\n    coef operator()(const coef &x) const {\n\
    \        coef ret = 0;\n        coef pwr = 1;\n        for (int i = 0; i < p.size();\
    \ i++) {\n            ret += p[i] * pwr;\n            pwr *= x;\n        }\n \
    \       return ret;\n    }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const polynomial &a) {\n        if (a.p.size() == 1 && a.p[0] == 0)\n \
    \           os << \"0\";\n        else\n            for (int i = a.p.size() -\
    \ 1; i >= 0; i--) {\n                if (a.p[i] == 0)\n                    continue;\n\
    \                std::string sign;\n                if (i != a.p.size() - 1 &&\
    \ a.p[i] > 0)\n                    sign = \"+ \";\n                if (a.p[i]\
    \ < 0)\n                    sign = \"- \";\n                os << sign << (a.p[i]\
    \ >= 0 ? a.p[i] : a.p[i]) << ' '\n                   << a.variable_name << '^'\
    \ << i << ' ';\n            }\n        return os;\n    }\n\n    polynomial<coef>\
    \ integrate() {\n        polynomial<coef> ret(*this);\n        for (int i = 1;\
    \ i <= max_order() + 1; i++) {\n            ret.set_coef(i, get_coef(i - 1) /\
    \ i);\n        }\n        return ret;\n    }\n\n    polynomial<coef> differentiate()\
    \ {\n        polynomial<coef> ret;\n        for (int i = 0; i < max_order(); i++)\
    \ {\n            ret.set_coef(i, get_coef(i + 1) * (i + 1));\n        }\n    \
    \    return ret;\n    }\n};\n"
  code: "#pragma once\n#include <algorithm>\n#include <string>\n#include <vector>\n\
    \n/**\n * @deprecated \u7A4D\u304CO(n^2)\u3067\u304A\u305D\u3044\u3002\u5F37\u3044\
    \u4EBA\u306E\u30E9\u30A4\u30D6\u30E9\u30EA\u3092\u4F7F\u304A\u3046\u3002\n */\n\
    template <class coef> class polynomial {\n  private:\n    std::vector<coef> p;\n\
    \    std::string variable_name = \"x\";\n\n    const friend polynomial operator+(const\
    \ polynomial &a) { return a; }\n\n    const friend polynomial operator-(const\
    \ polynomial &a) {\n        polynomial<coef> ret(a);\n        for (coef &c : ret)\n\
    \            c *= -1;\n        return ret;\n    }\n\n    friend const polynomial\
    \ operator+(const polynomial &a,\n                                      const\
    \ polynomial &b) {\n        int siz = std::max(a.p.size(), b.p.size());\n    \
    \    int siz1 = a.p.size(), siz2 = b.p.size();\n        polynomial ret;\n    \
    \    ret.p.resize(siz);\n        for (int i = 0; i < siz; i++) {\n           \
    \ ret.p[i] = (i < siz1 ? a.p[i] : 0) + (i < siz2 ? b.p[i] : 0);\n        }\n \
    \       while (ret.p.back() == 0 && ret.p.size() != 1)\n            ret.p.pop_back();\n\
    \        return ret;\n    }\n\n    friend const polynomial operator-(const polynomial\
    \ &a,\n                                      const polynomial &b) {\n        int\
    \ siz = std::max(a.p.size(), b.p.size());\n        int siz1 = a.p.size(), siz2\
    \ = b.p.size();\n        polynomial ret;\n        ret.p.resize(siz);\n       \
    \ for (int i = 0; i < siz; i++) {\n            ret.p[i] = (i < siz1 ? a.p[i] :\
    \ 0) - (i < siz2 ? b.p[i] : 0);\n        }\n        while (ret.p.back() == 0 &&\
    \ ret.p.size() != 1)\n            ret.p.pop_back();\n        return ret;\n   \
    \ }\n\n    friend const polynomial operator*(const polynomial &a,\n          \
    \                            const polynomial &b) {\n        int siz1 = a.p.size(),\
    \ siz2 = b.p.size();\n        polynomial ret;\n        ret.p.resize(siz1 + siz2\
    \ - 1);\n        for (int i = 0; i < siz1; i++)\n            for (int j = 0; j\
    \ < siz2; j++)\n                ret.p[i + j] += a.p[i] * b.p[j];\n        return\
    \ ret;\n    }\n\n    friend const polynomial operator/(const polynomial &a,\n\
    \                                      const polynomial &b) {\n        int siz1\
    \ = a.p.size(), siz2 = b.p.size();\n        if (siz1 < siz2)\n            return\
    \ {0};\n        polynomial ret, remain(a);\n        ret.p.resize(siz1 - siz2 +\
    \ 1, 0);\n        for (int i = siz1 - siz2; i >= 0; i--) {\n            ret.p[i]\
    \ = remain.p.back() / b.p.back();\n            for (int j = 1; j < siz2; j++)\
    \ {\n                remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];\n\
    \            }\n            remain.p.pop_back();\n        }\n        return ret;\n\
    \    }\n\n    friend const polynomial operator%(const polynomial &a,\n       \
    \                               const polynomial &b) {\n        int siz1 = a.p.size(),\
    \ siz2 = b.p.size();\n        if (siz1 < siz2)\n            return {0};\n    \
    \    polynomial ret, remain(a);\n        ret.p.resize(siz1 - siz2 + 1, 0);\n \
    \       for (int i = siz1 - siz2; i >= 0; i--) {\n            ret.p[i] = remain.p.back()\
    \ / b.p.back();\n            for (int j = 1; j < siz2; j++) {\n              \
    \  remain.p[siz2 - j - 1 + i] -= b.p[siz2 - j - 1] * ret.p[i];\n            }\n\
    \            remain.p.pop_back();\n        }\n        return remain;\n    }\n\n\
    \    friend int compare(const polynomial &a, const polynomial &b) {\n        int\
    \ siz1 = a.p.size();\n        int siz2 = b.p.size();\n        if (siz1 > siz2)\n\
    \            return +1;\n        if (siz1 < siz2)\n            return -1;\n  \
    \      for (int i = siz1 - 1; i >= 0; i--) {\n            if (a.p[i] > b.p[i])\n\
    \                return +1;\n            if (a.p[i] < b.p[i])\n              \
    \  return -1;\n        }\n        return 0;\n    }\n\n    friend bool operator==(const\
    \ polynomial &a, const polynomial &b) {\n        return (compare(a, b) == 0);\n\
    \    }\n\n    friend bool operator!=(const polynomial &a, const polynomial &b)\
    \ {\n        return (compare(a, b) != 0);\n    }\n\n    friend bool operator<(const\
    \ polynomial &a, const polynomial &b) {\n        return (compare(a, b) < 0);\n\
    \    }\n\n    friend bool operator<=(const polynomial &a, const polynomial &b)\
    \ {\n        return (compare(a, b) <= 0);\n    }\n\n    friend bool operator>(const\
    \ polynomial &a, const polynomial &b) {\n        return (compare(a, b) > 0);\n\
    \    }\n\n    friend bool operator>=(const polynomial &a, const polynomial &b)\
    \ {\n        return (compare(a, b) >= 0);\n    }\n\n  public:\n    polynomial(const\
    \ std::vector<coef> &vec) : p(vec) {\n        while (p.back() == 0 && p.size()\
    \ != 1)\n            p.pop_back();\n    }\n    polynomial(const coef &n = 0) :\
    \ polynomial(std::vector<coef>{n}) {}\n\n    int max_order() const { return p.size()\
    \ - 1; }\n\n    coef get_coef(int n) const {\n        assert(0 <= n);\n      \
    \  return (n < p.size() ? p[n] : 0);\n    }\n\n    void set_coef(int n, const\
    \ coef &x) {\n        assert(0 <= n);\n        if (n >= p.size())\n          \
    \  p.resize(n + 1, 0);\n        p[n] = x;\n        while (p.back() == 0 && p.size()\
    \ != 1)\n            p.pop_back();\n    }\n\n    polynomial &operator=(const polynomial\
    \ &a) {\n        p = a.p;\n        return *this;\n    }\n\n    void operator+=(const\
    \ polynomial &a) { *this = operator+(*this, a); }\n\n    void operator-=(const\
    \ polynomial &a) { *this = operator-(*this, a); }\n\n    void operator*=(const\
    \ polynomial &a) { *this = operator*(*this, a); }\n\n    void operator/=(const\
    \ polynomial &a) { *this = operator/(*this, a); }\n\n    void operator%=(const\
    \ polynomial &a) { *this = operator%(*this, a); }\n\n    coef operator[](int n)\
    \ const { return get_coef(n); }\n\n    coef operator()(const coef &x) const {\n\
    \        coef ret = 0;\n        coef pwr = 1;\n        for (int i = 0; i < p.size();\
    \ i++) {\n            ret += p[i] * pwr;\n            pwr *= x;\n        }\n \
    \       return ret;\n    }\n\n    friend std::ostream &operator<<(std::ostream\
    \ &os, const polynomial &a) {\n        if (a.p.size() == 1 && a.p[0] == 0)\n \
    \           os << \"0\";\n        else\n            for (int i = a.p.size() -\
    \ 1; i >= 0; i--) {\n                if (a.p[i] == 0)\n                    continue;\n\
    \                std::string sign;\n                if (i != a.p.size() - 1 &&\
    \ a.p[i] > 0)\n                    sign = \"+ \";\n                if (a.p[i]\
    \ < 0)\n                    sign = \"- \";\n                os << sign << (a.p[i]\
    \ >= 0 ? a.p[i] : a.p[i]) << ' '\n                   << a.variable_name << '^'\
    \ << i << ' ';\n            }\n        return os;\n    }\n\n    polynomial<coef>\
    \ integrate() {\n        polynomial<coef> ret(*this);\n        for (int i = 1;\
    \ i <= max_order() + 1; i++) {\n            ret.set_coef(i, get_coef(i - 1) /\
    \ i);\n        }\n        return ret;\n    }\n\n    polynomial<coef> differentiate()\
    \ {\n        polynomial<coef> ret;\n        for (int i = 0; i < max_order(); i++)\
    \ {\n            ret.set_coef(i, get_coef(i + 1) * (i + 1));\n        }\n    \
    \    return ret;\n    }\n};\n"
  dependsOn: []
  isVerificationFile: false
  path: math/polynomial.hpp
  requiredBy: []
  timestamp: '2023-06-19 01:54:04+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: math/polynomial.hpp
layout: document
redirect_from:
- /library/math/polynomial.hpp
- /library/math/polynomial.hpp.html
title: math/polynomial.hpp
---
