#ifndef EDGE_STRUCT
#define EDGE_STRUCT
#include <iostream>

namespace internal{
    template<class DERIVED, class WEIGHT>
    struct _base_edge{
        int from;
        int to;
        WEIGHT cost;
        int id;
        _base_edge(int _from, int _to, WEIGHT _cost, int _id) : from(_from), to(_to), cost(_cost), id(_id) {}

        friend bool operator>(const _base_edge &e1, const _base_edge &e){
            return e1.compare(e) > 0;
        }
        friend bool operator>=(const _base_edge &e1, const _base_edge &e){
            return e1.compare(e) >= 0;
        }
        friend bool operator<(const _base_edge &e1, const _base_edge &e){
            return e1.compare(e) < 0;
        }
        friend bool operator<=(const _base_edge &e1, const _base_edge &e){
            return e1.compare(e) <= 0;
        }
        friend std::ostream &operator<<(std::ostream &os, const _base_edge<DERIVED, WEIGHT> &e) {
            e.print(os);
            return os;
        }
        const _base_edge &operator=(const _base_edge &e){
            from = e.from, to = e.to, cost = e.cost, id = e.id;
            return *this;
        }

        virtual ~_base_edge() = default; 

      protected:
        virtual void print(std::ostream &os) const = 0;
        virtual int compare(const _base_edge &e) const = 0;
    };
}

template<class WEIGHT>
struct edge : public internal::_base_edge<edge<WEIGHT>, WEIGHT>{
    edge() : internal::_base_edge<edge<WEIGHT>, WEIGHT>(0, 0, 0, 0) {}
    using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;
  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to << " " << this->cost;
    }  
    int compare(const internal::_base_edge<edge<WEIGHT>, WEIGHT>& e) const override {
        if(this->cost == e.cost){
            if(this->from == e.from){
                return this->to - e.to;
            }
            return this->from - e.from;
        }
        return this->cost - e.cost;
    }
};

template<>
struct edge<int> : public internal::_base_edge<edge<int>, int>{
    const int cost = 1;
    edge() : internal::_base_edge<edge<int>, int>(0, 0, 0, 0) {}
    edge(int _from, int _to, int _id) : _base_edge<edge<int>, int>(_from, _to, 0, _id) {}
  protected:
    void print(std::ostream &os) const override {
        os << this->from << " " << this->to;
    }
    int compare(const internal::_base_edge<edge<int>, int>& e) const override {
        if(this->from == e.from){
            return this->to - e.to;
        }
        return this->from - e.from;
    }
};

#endif
