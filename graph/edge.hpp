#pragma once
#include <iostream>

namespace internal {
template <class DERIVED, class WEIGHT> struct _base_edge {
    int from;
    int to;
    WEIGHT cost;
    int id;
    _base_edge() {}
    _base_edge(int _from, int _to, WEIGHT _cost, int _id)
        : from(_from), to(_to), cost(_cost), id(_id) {}

    friend bool operator>(const _base_edge &e1, const _base_edge &e) {
        return e1.compare(e) > 0;
    }
    friend bool operator>=(const _base_edge &e1, const _base_edge &e) {
        return e1.compare(e) >= 0;
    }
    friend bool operator<(const _base_edge &e1, const _base_edge &e) {
        return e1.compare(e) < 0;
    }
    friend bool operator<=(const _base_edge &e1, const _base_edge &e) {
        return e1.compare(e) <= 0;
    }
    friend std::ostream &operator<<(std::ostream &os,
                                    const _base_edge<DERIVED, WEIGHT> &e) {
        e.print(os);
        return os;
    }
    _base_edge &operator=(const _base_edge &e) = default;

    virtual ~_base_edge() = default;

    DERIVED reverse() const {
        return {to, from, cost, id};
    }

    operator int() const { return to; }

  protected:
    virtual void print(std::ostream &os) const = 0;
    virtual int compare(const _base_edge &e) const = 0;
};
} // namespace internal

template <class WEIGHT>
struct edge : public internal::_base_edge<edge<WEIGHT>, WEIGHT> {
    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to << " " << this->cost;
    }
    int compare(
        const internal::_base_edge<edge<WEIGHT>, WEIGHT> &e) const override {
        if (this->cost == e.cost) {
            if (this->from == e.from)
                return this->to - e.to;
            return this->from - e.from;
        }
        return this->cost - e.cost;
    }
};

template <> struct edge<int> : public internal::_base_edge<edge<int>, int> {
    static inline const int cost = 1;
    using internal::_base_edge<edge<int>, int>::_base_edge;
    edge(int _from, int _to, int _id)
        : _base_edge<edge<int>, int>(_from, _to, 0, _id) {}

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to;
    }
    int compare(const internal::_base_edge<edge<int>, int> &e) const override {
        if (this->from == e.from)
            return this->to - e.to;
        return this->from - e.from;
    }
};
