#pragma once

#include <algorithm>
#include <exception>
#include <iostream>

#include "gandalfr/types.hpp"

namespace gandalfr {

template <u32 sz, typename T, typename Compare = std::less<T>>
class StaticPriorityQueue {
    static_assert(sz, "The size of the queue must be 1 or bigger.");
    u32 elms = 0;
    T buff[sz + 1];

  public:
    bool empty() const { return elms == 0; }
    u32 size() const { return elms; }
    const T &top() const {
        if (elms) [[likely]] {
            return buff[0];
        }
        throw std::runtime_error("The queue is empty.");
    }
    void push(const T &x) {
        buff[elms++] = x;
        std::push_heap(buff, buff + elms, Compare());
        if (elms > sz) {
            pop();
        }
    }
    void pop() {
        if (elms == 0) [[unlikely]] {
            throw std::runtime_error("The queue is empty.");
        }
        std::pop_heap(buff, buff + elms, Compare());
        --elms;
    }
    void merge(StaticPriorityQueue other) {
        while (!other.empty()) {
            push(other.top());
            other.pop();
        }
    }
    friend std::ostream &operator<<(std::ostream &os, StaticPriorityQueue pq) {
        while (!pq.empty()) {
            os << pq.top() << (pq.size() == 1 ? "" : " ");
            pq.pop();
        }
        return os;
    }
};
} // namespace gandalfr
