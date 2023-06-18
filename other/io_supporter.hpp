#pragma once
#include <deque>
#include <iostream>
#include <queue>
#include <string>
#include <utility>

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for (int i = 0; i < (int)v.size(); i++)
        os << v[i] << (i + 1 != (int)v.size() ? " " : "");
    return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &st) {
    for (const T &x : st) {
        std::cout << x << " ";
    }
    return os;
}

template <typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &st) {
    for (const T &x : st) {
        std::cout << x << " ";
    }
    return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, const std::deque<T> &dq) {
    for (const T &x : dq) {
        std::cout << x << " ";
    }
    return os;
}
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p) {
    os << p.first << ' ' << p.second;
    return os;
}
template <typename T>
std::ostream &operator<<(std::ostream &os, std::queue<T> &q) {
    int sz = q.size();
    while (--sz) {
        os << q.front() << ' ';
        q.push(q.front());
        q.pop();
    }
    os << q.front();
    q.push(q.front());
    q.pop();
    return os;
}

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
