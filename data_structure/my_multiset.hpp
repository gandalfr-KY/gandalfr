#pragma once

#include <iostream>
#include <set>

template <typename _Key, typename _Compare = std ::less<_Key>,
          typename _Alloc = std ::allocator<_Key>>
class my_multiset : public std::multiset<_Key, _Compare, _Alloc> {
  public:
    using std::multiset<_Key, _Compare, _Alloc>::multiset;
    bool erase_one(const _Key &__x) {
        auto it = this->find(__x);
        if (it == this->end()) {
            return false;
        } else {
            this->erase(it);
            return true;
        }
    }
    int erase_all(const _Key &__x) {
        int ret = this->count(__x);
        if (ret == 0) {
            return 0;
        } else {
            this->erase(__x);
            return ret;
        }
    }
    const _Key &front() const { return *this->begin(); }
    const _Key &back() const { return *--this->end(); }
    friend std::ostream &operator<<(std::ostream &os, const my_multiset &ms) {
        auto it = ms.begin();
        os << *it;
        for (++it; it != ms.end(); ++it) {
            os << ' ' << *it;
        }
        return os;
    }
};
