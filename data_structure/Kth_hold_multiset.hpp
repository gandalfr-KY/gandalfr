#ifndef KTH_HOLD_MULTISET
#define KTH_HOLD_MULTISET
#include <assert.h>

#include <iostream>
#include <set>

/*
 * verify : https://yukicoder.me/submissions/856775
 */
template <class T> class Kth_hold_multiset {
  private:
    std::multiset<T> low, high; // low のサイズを K に保つ
    const int k;
    void refill() {
        while ((int)low.size() > k) {
            auto it = prev(low.end());
            high.insert(*it);
            low.erase(it);
        }
        while (!high.empty() && (int)low.size() < k) {
            auto it = high.begin();
            low.insert(*it);
            high.erase(it);
        }
    }

    class Iterator {
      public:
        Iterator(typename std::multiset<T>::iterator it, std::multiset<T> &low,
                 std::multiset<T> &high)
            : it_(it), low_(low), high_(high) {}

        bool operator==(const Iterator &other) const {
            return it_ == other.it_;
        }
        bool operator!=(const Iterator &other) const {
            return it_ != other.it_;
        }

        const T &operator*() const { return *it_; }

        Iterator &operator++() {
            ++it_;
            if (it_ == low_.end())
                it_ = high_.begin();
            return *this;
        }

        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }

      private:
        typename std::multiset<T>::iterator it_;
        std::multiset<T> &low_;
        std::multiset<T> &high_;
    };

  public:
    Kth_hold_multiset(int K) : k(K) { assert(K > 0); }

    void insert(T x) {
        if ((int)low.size() < k) {
            low.insert(x);
            return;
        }

        T Kth = *prev(low.end());
        if (x >= Kth)
            high.insert(x);
        else
            low.insert(x);
        refill();
    }

    void erase_a_element(T x) {
        if (high.empty()) {
            auto low_it = low.find(x);
            if (low_it != low.end())
                low.erase(low_it);
            return;
        }

        auto high_it = high.find(x);
        auto low_it = low.find(x);
        if (high_it != high.end())
            high.erase(high_it);
        else if (low_it != low.end())
            low.erase(low_it);
        refill();
    }

    void erase_all_element(T x) {
        low.erase(x);
        high.erase(x);
        refill();
    }

    Iterator find(T x) {
        auto low_it = low.find(x);
        if (low_it != low.end())
            return Iterator(low_it, low, high);
        else
            return Iterator(high.find(x), low, high);
    }

    int size() { return low.size() + high.size(); }

    T get_Kth_value() { return *prev(low.end()); }

    int count(T x) { return low.count(x) + high.count(x); }

    void dump() {
        int loop = low.size() + high.size();
        for (auto x : *this) {
            loop--;
            std::cout << x << (loop ? " " : "");
        }
    }

    Iterator begin() {
        return low.empty() ? Iterator(high.end(), low, high)
                           : Iterator(low.begin(), low, high);
    }
    Iterator end() { return Iterator(high.end(), low, high); }
};

#endif
