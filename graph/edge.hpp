#ifndef EDGE_STRUCT
#define EDGE_STRUCT
#include <iostream>

struct unweighted_edge{
    int from;
    int to;
    int id;
    friend bool operator>(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to > e2.to;
        }
        return e1.from > e2.from;
    }
    friend bool operator>=(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to >= e2.to;
        }
        return e1.from > e2.from;
    }
    friend bool operator<(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to < e2.to;
        }
        return e1.from < e2.from;
    }
    friend bool operator<=(const unweighted_edge &e1, const unweighted_edge &e2){
        if(e1.from == e2.from){
            return e1.to <= e2.to;
        }
        return e1.from < e2.from;
    }
    friend std::ostream &operator<<(std::ostream &os, const unweighted_edge &e) {
        os << e.from << " " << e.to;
        return os;
    }
};

template<class WEIGHT>
struct weighted_edge{
    int from;
    int to;
    WEIGHT cost;
    int id;
    friend bool operator>(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to > e2.to;
            }
            return e1.from > e2.from;
        }
        return e1.cost > e2.cost;
    }
    friend bool operator>=(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to >= e2.to;
            }
            return e1.from > e2.from;
        }
        return e1.cost > e2.cost;
    }
    friend bool operator<(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to < e2.to;
            }
            return e1.from < e2.from;
        }
        return e1.cost < e2.cost;
    }
    friend bool operator<=(const weighted_edge &e1, const weighted_edge &e2){
        if(e1.cost == e2.cost){
            if(e1.from == e2.from){
                return e1.to <= e2.to;
            }
            return e1.from < e2.from;
        }
        return e1.cost < e2.cost;
    }
    friend std::ostream &operator<<(std::ostream &os, const weighted_edge &e) {
        os << e.from << " " << e.to << " " << e.cost;
        return os;
    }
};

#endif