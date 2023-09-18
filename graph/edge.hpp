#pragma once
#include <iostream>
#include <algorithm>

namespace internal {
template <class Weight> struct _base_edge {
    int from;
    int to;
    Weight cost;
    int id;
    _base_edge() {}
    _base_edge(int _from, int _to, Weight _cost, int _id)
        : from(_from), to(_to), cost(_cost), id(_id) {}

    friend std::ostream &operator<<(std::ostream &os,
                                    const _base_edge<Weight> &e) {
        e.print(os);
        return os;
    }

    operator int() const { return to; }

  protected:
    virtual void print(std::ostream &os) const = 0;
};
} // namespace internal

template <class Weight>
struct edge : public internal::_base_edge<Weight> {
    using internal::_base_edge<Weight>::_base_edge;

    edge minmax() const {
        auto [f, t] = std::minmax(this->from, this->to);
        return {f, t, this->cost, this->id};
    }
    edge reverse() const { return {this->to, this->from, this->cost, this->id}; }

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to << " " << this->cost;
    }
};

template <> struct edge<int> : public internal::_base_edge<int> {
    static inline const int cost = 1;
    using internal::_base_edge<int>::_base_edge;
    edge(int _from, int _to, int _id)
        : _base_edge<int>(_from, _to, 1, _id) {}

    edge minmax() const {
        auto [f, t] = std::minmax(from, to);
        return {f, t, 1, id};
    }
    edge reverse() const { return {to, from, 1, id}; }

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to;
    }
};

template <class Weight, class Flow> 
struct flow_edge : public internal::_base_edge<Weight> {
    int r_idx = -1;
    Weight capacity, residual;

    flow_edge(int _from, int _to, Flow _residual, Flow _capacity, int _id)
        : internal::_base_edge<Weight>(_from, _to, 1, _id), residual(_residual), capacity(_capacity) {}
    flow_edge(int _from, int _to, Flow _residual, Flow _capacity, Weight _cost, int _id)
        : internal::_base_edge<Weight>(_from, _to, _cost, _id), residual(_residual), capacity(_capacity) {}

    flow_edge reverse() const {
        return {this->to, this->from, capacity - residual, capacity, this->cost, this->id};
    }

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to << " " << capacity - residual << "/" << capacity;
    }
};
