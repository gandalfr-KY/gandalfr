#ifndef IO_SUPPORTER
#define IO_SUPPORTER
#include <iostream>
#include <utility>
#include <queue>
#include <string>

template <template <typename, typename...> class ContainerType, typename ValueType>
std::ostream& operator<<(std::ostream &os, const ContainerType<ValueType>& container) {
    auto it = container.cbegin();
    if(it == container.end()) return os;
    os << *it;
    while(++it != container.cend()) os << ' ' << *it;
    return os;
}

template <template <typename, typename...> class ContainerType, typename ValueType>
std::istream& operator>>(std::istream &is, ContainerType<ValueType>& container) {
    for(auto &x : container) is >> x;
    return is;
}

std::ostream& operator<<(std::ostream &os, const std::string& s) {
    std::operator<<(os, s);
    return os;
}

std::istream& operator>>(std::istream &is, std::string& s) {
    std::operator>>(is, s);
    return is;
}

template<typename T1, typename T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2>& p) {
    os << p.first << ' ' << p.second;
    return os;
}
template<typename T1, typename T2>
std::istream &operator>>(std::istream &is, std::pair<T1, T2> &p) {
    is >> p.first >> p.second;
    return is;
}

template<typename T>
std::ostream &operator<<(std::ostream &os, std::queue<T>& q) {
    int sz = q.size();
    while(--sz){
        os << q.front() << ' ';
        q.push(q.front());
        q.pop();
    }
    os << q.front();
    q.push(q.front());
    q.pop();
    return os;
}

#endif