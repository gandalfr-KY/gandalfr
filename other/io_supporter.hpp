#ifndef IO_SUPPORTER
#define IO_SUPPORTER
#include <iostream>
#include <iterator>
#include <utility>
#include <queue>

template <template <typename, typename...> class ContainerType, typename ValueType>
std::ostream& operator<<(std::ostream &os, const ContainerType<ValueType>& container) {
    auto it = container.cbegin();
    for(; std::next(it) != container.cend(); ++it){
        os << *it << ' ';
    }
    return os << *it;
}

template <template <typename, typename...> class ContainerType, typename ValueType>
std::istream& operator>>(std::istream &is, ContainerType<ValueType>& container) {
    for(auto &x : container) is >> x;
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