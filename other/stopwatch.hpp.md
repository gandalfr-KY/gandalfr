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
  bundledCode: "#line 1 \"other/stopwatch.hpp\"\n\n\n#include <chrono>\n\n/* reset()\
    \ := \u30BF\u30A4\u30DE\u30FC\u30920\u306B\u30EA\u30BB\u30C3\u30C8\n * get_milliseconnds()\
    \ := \u30DF\u30EA\u79D2\u3092\u8FD4\u3059\n * get_seconnds() := \u79D2\u3092\u8FD4\
    \u3059\n */\nclass {\n  private:\n    std::chrono::system_clock::time_point start,\
    \ end;\n\n  public:\n    void reset(){ start = std::chrono::system_clock::now();\
    \ }\n    long long get_millisecconds(){\n        end = std::chrono::system_clock::now();\n\
    \        return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();\n\
    \    }\n    long long get_secconds(){\n        end = std::chrono::system_clock::now();\n\
    \        return std::chrono::duration_cast<std::chrono::seconds>(end-start).count();\n\
    \    }\n} static stopwatch;\n\n\n"
  code: "#ifndef STOPWATCH\n#define STOPWATCH\n#include <chrono>\n\n/* reset() :=\
    \ \u30BF\u30A4\u30DE\u30FC\u30920\u306B\u30EA\u30BB\u30C3\u30C8\n * get_milliseconnds()\
    \ := \u30DF\u30EA\u79D2\u3092\u8FD4\u3059\n * get_seconnds() := \u79D2\u3092\u8FD4\
    \u3059\n */\nclass {\n  private:\n    std::chrono::system_clock::time_point start,\
    \ end;\n\n  public:\n    void reset(){ start = std::chrono::system_clock::now();\
    \ }\n    long long get_millisecconds(){\n        end = std::chrono::system_clock::now();\n\
    \        return std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count();\n\
    \    }\n    long long get_secconds(){\n        end = std::chrono::system_clock::now();\n\
    \        return std::chrono::duration_cast<std::chrono::seconds>(end-start).count();\n\
    \    }\n} static stopwatch;\n\n#endif"
  dependsOn: []
  isVerificationFile: false
  path: other/stopwatch.hpp
  requiredBy: []
  timestamp: '2022-10-29 18:46:52+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: other/stopwatch.hpp
layout: document
redirect_from:
- /library/other/stopwatch.hpp
- /library/other/stopwatch.hpp.html
title: other/stopwatch.hpp
---
