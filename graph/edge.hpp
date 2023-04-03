#ifndef EDGE_STRUCT
#define EDGE_STRUCT
#include <iostream>

namespace internal{
    template<class WEIGHT>
    struct _base_edge{
        int from;
        int to;
        WEIGHT cost;
        int id;
        _base_edge(int _from, int _to, WEIGHT _cost, int _id) : from(_from), to(_to), cost(_cost), id(_id) {}
        friend bool operator>(const _base_edge &e1, const _base_edge &e2){
            if(e1.cost == e2.cost){
                if(e1.from == e2.from){
                    return e1.to > e2.to;
                }
                return e1.from > e2.from;
            }
            return e1.cost > e2.cost;
        }
        friend bool operator>=(const _base_edge &e1, const _base_edge &e2){
            if(e1.cost == e2.cost){
                if(e1.from == e2.from){
                    return e1.to >= e2.to;
                }
                return e1.from > e2.from;
            }
            return e1.cost > e2.cost;
        }
        friend bool operator<(const _base_edge &e1, const _base_edge &e2){
            if(e1.cost == e2.cost){
                if(e1.from == e2.from){
                    return e1.to < e2.to;
                }
                return e1.from < e2.from;
            }
            return e1.cost < e2.cost;
        }
        friend bool operator<=(const _base_edge &e1, const _base_edge &e2){
            if(e1.cost == e2.cost){
                if(e1.from == e2.from){
                    return e1.to <= e2.to;
                }
                return e1.from < e2.from;
            }
            return e1.cost < e2.cost;
        }
        friend std::ostream &operator<<(std::ostream &os, const _base_edge<WEIGHT> &e) {
            os << e.from << " " << e.to << " " << e.cost;
            return os;
        }
        const _base_edge &operator=(const _base_edge &e){
            from = e.from, to = e.to, cost = e.cost, id = e.id;
            return *this;
        } 
    };

    template<>
    struct _base_edge<int>{
        int from;
        int to;
        const int cost = 1;
        int id;
        _base_edge(int _from, int _to, int _id) : from(_from), to(_to), id(_id) {}
        friend bool operator>(const _base_edge &e1, const _base_edge &e2){
            if(e1.from == e2.from){
                return e1.to > e2.to;
            }
            return e1.from > e2.from;
        }
        friend bool operator>=(const _base_edge &e1, const _base_edge &e2){
            if(e1.from == e2.from){
                return e1.to >= e2.to;
            }
            return e1.from > e2.from;
        }
        friend bool operator<(const _base_edge &e1, const _base_edge &e2){
            if(e1.from == e2.from){
                return e1.to < e2.to;
            }
            return e1.from < e2.from;
        }
        friend bool operator<=(const _base_edge &e1, const _base_edge &e2){
            if(e1.from == e2.from){
                return e1.to <= e2.to;
            }
            return e1.from < e2.from;
        }
        friend std::ostream &operator<<(std::ostream &os, const _base_edge<int> &e) {
            os << e.from << " " << e.to;
            return os;
        }
        const _base_edge &operator=(const _base_edge &e){
            from = e.from, to = e.to, id = e.id;
            return *this;
        } 
    };
}

template<class WEIGHT> using weighted_edge = internal::_base_edge<WEIGHT>;
using unweighted_edge = internal::_base_edge<int>;

#endif