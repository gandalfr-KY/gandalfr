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

        friend bool operator>(const _base_edge &e1, const _base_edge &e2){
            return static_cast<DERIVED const&>(e1).compare(e2) > 0;
        }
        friend bool operator>=(const _base_edge &e1, const _base_edge &e2){
            return static_cast<DERIVED const&>(e1).compare(e2) >= 0;
        }
        friend bool operator<(const _base_edge &e1, const _base_edge &e2){
            return static_cast<DERIVED const&>(e1).compare(e2) < 0;
        }
        friend bool operator<=(const _base_edge &e1, const _base_edge &e2){
            return static_cast<DERIVED const&>(e1).compare(e2) <= 0;
        }
        friend std::ostream &operator<<(std::ostream &os, const _base_edge<DERIVED, WEIGHT> &e) {
            static_cast<DERIVED const&>(e).print(os);
            return os;
        }
        const _base_edge &operator=(const _base_edge &e){
            from = e.from, to = e.to, cost = e.cost, id = e.id;
            return *this;
        } 
    };
}

    template<class WEIGHT>
    struct edge : public internal::_base_edge<edge<WEIGHT>, WEIGHT>{
        using internal::_base_edge<edge<WEIGHT>, WEIGHT>::_base_edge;
        int compare(const internal::_base_edge<edge<WEIGHT>, WEIGHT>& e2) const{
            if(this->cost == e2.cost){
                if(this->from == e2.from){
                    return this->to - e2.to;
                }
                return this->from - e2.from;
            }
            return this->cost - e2.cost;
        }
        void print(std::ostream &os) const {
            os << this->from << " " << this->to << " " << this->cost;
        }
    };

    template<>
    struct edge<int> : public internal::_base_edge<edge<int>, int>{
        const int cost = 1;
        edge(int _from, int _to, int _id) : _base_edge<edge<int>, int>(_from, _to, 0, _id) {}
        int compare(const internal::_base_edge<edge<int>, int>& e2) const{
            if(this->from == e2.from){
                return this->to - e2.to;
            }
            return this->from - e2.from;
        }
        void print(std::ostream &os) const {
            os << this->from << " " << this->to;
        }
    };

#endif