#ifndef IO_SUPPORTER
#define IO_SUPPORTER
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::vector<T> &v) {
    for(int i=0; i<(int)v.size(); i++) os << v[i] << (i+1 != (int)v.size() ? " " : "");
    return os;
}
template<typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &v){
    for(T &in : v) is >> in;
    return is;
}

template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2>& p) {
    os << p.first << " " << p.second;
    return os;
}
template<typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, std::queue<T> v) {
    int N = v.size();
    for(int i=0; i<N; i++) {
        os << v.front() << (i+1 != N ? " " : "");
        v.pop();
    }
    return os;
}
template<typename T>
std::istream &operator>>(std::istream &is, std::queue<T> &v) {
    for(T &in : is) v.push(is);
    return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::set<T> &st) {
    for(const T &x : st){
        std::cout << x << " ";
    }
    return os;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, const std::multiset<T> &st) {
    for(const T &x : st){
        std::cout << x << " ";
    }
    return os;
}


#endif