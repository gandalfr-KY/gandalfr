#ifndef IO_SUPPORTER
#define IO_SUPPORTER
#include <iostream>
#include <vector>
#include <utility>
#include <queue>

std::ostream &operator<<(std::ostream &dest, __uint128_t value) {
	std::ostream::sentry s(dest);
	if (s) {
		__uint128_t tmp = value < 0 ? -value : value;
		char buffer[128];
		char *d = std::end(buffer);
		do {
		--d;
		*d = "0123456789"[tmp % 10];
		tmp /= 10;
		} while (tmp != 0);
		int len = std::end(buffer) - d;
		if (dest.rdbuf()->sputn(d, len) != len) {
		dest.setstate(std::ios_base::badbit);
		}
	}
	return dest;
}

std::ostream &operator<<(std::ostream &dest, __int128_t value) {
	std::ostream::sentry s(dest);
	if (s) {
		__int128_t tmp = value < 0 ? -value : value;
		char buffer[128];
		char *d = std::end(buffer);
		do {
		--d;
		*d = "0123456789"[tmp % 10];
		tmp /= 10;
		} while (tmp != 0);
		if (value < 0) {
		--d;
		*d = '-';
		}
		int len = std::end(buffer) - d;
		if (dest.rdbuf()->sputn(d, len) != len) {
		dest.setstate(std::ios_base::badbit);
		}
	}
	return dest;
}

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

#endif