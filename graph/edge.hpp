#pragma once
#include <iostream>

namespace internal {
template <class DERIVED, class Weight> struct _base_edge {
    int from;
    int to;
    Weight cost;
    int id;
    _base_edge() {}
    _base_edge(int _from, int _to, Weight _cost, int _id)
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
                                    const _base_edge<DERIVED, Weight> &e) {
        e.print(os);
        return os;
    }
    _base_edge &operator=(const _base_edge &e) = default;

    virtual ~_base_edge() = default;

    DERIVED minmax() const {
        auto [f, t] = std::minmax(from, to);
        return {f, t, cost, id};
    }
    DERIVED reverse() const { return {to, from, cost, id}; }

    operator int() const { return to; }

  protected:
    virtual void print(std::ostream &os) const = 0;
    virtual int compare(const _base_edge &e) const = 0;
};
} // namespace internal

template <class Weight>
struct edge : public internal::_base_edge<edge<Weight>, Weight> {
    using internal::_base_edge<edge<Weight>, Weight>::_base_edge;

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to << " " << this->cost;
    }
    int compare(
        const internal::_base_edge<edge<Weight>, Weight> &e) const override {
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

namespace internal {

template <class DERIVED, class Weight> 
struct _flow_base_edge : public _base_edge<DERIVED, Weight> {
    _flow_base_edge *r_ptr = nullptr;
    Weight capacity;

    _flow_base_edge() {}
    _flow_base_edge(int _from, int _to, Weight _capacity, int _id, _flow_base_edge *_r_ptr)
        : _base_edge<DERIVED, Weight>(_from, _to, 1, _id), capacity(_capacity), r_ptr(_r_ptr) {}
    _flow_base_edge(int _from, int _to, Weight _capacity, Weight _cost, int _id, _flow_base_edge *_r_ptr)
        : _base_edge<DERIVED, Weight>(_from, _to, _cost, _id), capacity(_capacity), r_ptr(_r_ptr) {}

    DERIVED reverse() = delete;
};
} // namespace internal

template <class Weight>
struct flow_edge : public internal::_flow_base_edge<flow_edge<Weight>, Weight> {
    using internal::_flow_base_edge<flow_edge<Weight>, Weight>::_flow_base_edge;

  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to << " " << this->capacity;
    }
    int compare(
        const internal::_base_edge<flow_edge<Weight>, Weight> &e) const override {
        if (this->cost == e.cost) {
            if (this->from == e.from)
                return this->to - e.to;
            return this->from - e.from;
        }
        return this->cost - e.cost;
    }
};

