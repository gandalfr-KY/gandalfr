---
data:
  _extendedDependsOn: []
  _extendedRequiredBy: []
  _extendedVerifiedWith: []
  _isVerificationFailed: false
  _pathExtension: cpp
  _verificationStatusIcon: ':warning:'
  attributes:
    links: []
  bundledCode: "#line 1 \"make_library_united.cpp\"\n#include <iostream>\n#include\
    \ <vector>\n#include <string>\n#include <filesystem>\n#include <fstream>\n\nusing\
    \ std::endl; using std::string;\nusing std::filesystem::directory_iterator;\n\n\
    std::ofstream fout(\"all\");\nstring base_path = \"/home/gandalfr/CompPro-Workspace/library/\"\
    ;\n\nstring get_extention(const string &path){\n    int dot_pos = path.find('.');\n\
    \    if(dot_pos == -1) return \"\";\n    return string(path.begin() + dot_pos\
    \ + 1, path.end());\n}\n\nvoid file_search(const string &path){\n    for (const\
    \ auto & file : directory_iterator(path)){\n        string filename = file.path();\n\
    \        if(file.is_directory()){\n            file_search(filename);\n      \
    \  }\n        else if(get_extention(filename).compare(\"hpp\") == 0){\n      \
    \      fout << \"#include \\\"\" << string(filename.begin() + base_path.size(),\
    \ filename.end()) << \"\\\"\" << endl;\n        }\n    }\n}\n\nint main() {\n\
    \    string path = \"/home/gandalfr/CompPro-Workspace/library/gandalfr\";\n  \
    \  file_search(path);\n    return EXIT_SUCCESS;\n}\n"
  code: "#include <iostream>\n#include <vector>\n#include <string>\n#include <filesystem>\n\
    #include <fstream>\n\nusing std::endl; using std::string;\nusing std::filesystem::directory_iterator;\n\
    \nstd::ofstream fout(\"all\");\nstring base_path = \"/home/gandalfr/CompPro-Workspace/library/\"\
    ;\n\nstring get_extention(const string &path){\n    int dot_pos = path.find('.');\n\
    \    if(dot_pos == -1) return \"\";\n    return string(path.begin() + dot_pos\
    \ + 1, path.end());\n}\n\nvoid file_search(const string &path){\n    for (const\
    \ auto & file : directory_iterator(path)){\n        string filename = file.path();\n\
    \        if(file.is_directory()){\n            file_search(filename);\n      \
    \  }\n        else if(get_extention(filename).compare(\"hpp\") == 0){\n      \
    \      fout << \"#include \\\"\" << string(filename.begin() + base_path.size(),\
    \ filename.end()) << \"\\\"\" << endl;\n        }\n    }\n}\n\nint main() {\n\
    \    string path = \"/home/gandalfr/CompPro-Workspace/library/gandalfr\";\n  \
    \  file_search(path);\n    return EXIT_SUCCESS;\n}\n"
  dependsOn: []
  isVerificationFile: false
  path: make_library_united.cpp
  requiredBy: []
  timestamp: '2023-02-28 19:59:17+09:00'
  verificationStatus: LIBRARY_NO_TESTS
  verifiedWith: []
documentation_of: make_library_united.cpp
layout: document
redirect_from:
- /library/make_library_united.cpp
- /library/make_library_united.cpp.html
title: make_library_united.cpp
---
