#pragma once
#include <deque>
#include <iostream>
#include <map>
#include <queue>
#include <set>
#include <unordered_map>
#include <utility>
#include <vector>

namespace gandalfr {

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (size_t i = 0; i < v.size(); ++i) {
        os << v[i] << (i + 1 != v.size() ? " " : "");
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &st) {
    for (auto it = st.begin(); it != st.end(); ++it) {
        os << *it << (std::next(it) != st.end() ? " " : "");
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &st) {
    for (auto it = st.begin(); it != st.end(); ++it) {
        os << *it << (std::next(it) != st.end() ? " " : "");
    }
    return os;
}

template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << '(' << p.first << ", " << p.second << ')';
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, std::queue<T> q) {
    while (!q.empty()) {
        os << q.front() << (q.size() > 1 ? " " : "");
        q.pop();
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &dq) {
    for (size_t i = 0; i < dq.size(); ++i) {
        os << dq[i] << (i + 1 != dq.size() ? " " : "");
    }
    return os;
}

template <typename Tp, typename Sequence, typename Compare>
std::ostream &operator<<(std::ostream &os,
                         std::priority_queue<Tp, Sequence, Compare> q) {
    while (!q.empty()) {
        os << q.top() << (q.size() > 1 ? " " : "");
        q.pop();
    }
    return os;
}

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os, const std::map<Key, T> &m) {
    for (auto it = m.begin(); it != m.end(); ++it) {
        os << *it << (std::next(it) != m.end() ? " " : "");
    }
    return os;
}

template <typename Key, typename T>
std::ostream &operator<<(std::ostream &os,
                         const std::unordered_map<Key, T> &um) {
    for (auto it = um.begin(); it != um.end(); ++it) {
        os << *it << (std::next(it) != um.end() ? " " : "");
    }
    return os;
}

///////////////////// input /////////////////////

template <typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v) {
    for (T &in : v)
        is >> in;
    return is;
}
template <typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template <typename T> void print_debug(const T &t) {
    std::cerr << t << std::endl;
}
template <typename First, typename... Rest>
void print_debug(First parm1, Rest... parm) {
    std::cerr << parm1 << ", ", print_debug(parm...);
}
#define debug(...)                                                             \
    std::cerr << #__VA_ARGS__ << ": ";                                         \
    print_debug(__VA_ARGS__);

} // namespace gandalfr
