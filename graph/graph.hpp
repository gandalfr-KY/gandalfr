#ifndef GRAPH_STRUCTURE
#define GRAPH_STRUCTURE
#include <vector>
#include <algorithm>
#include <iostream>
#include <bits/stl_numeric.h>
#include <assert.h>

struct unweighted_edge{
    int from;
    int to;
    int id;
};

struct unweighted_graph{
    int N, M = 0;
    std::vector<std::vector<unweighted_edge>> G;
    std::vector<unweighted_edge> E;
    const bool is_directed;
    
    unweighted_graph() : N(0), is_directed(false) {}
    unweighted_graph(bool _is_directed): N(0), G(0), is_directed(_is_directed) {};
    unweighted_graph(int _n, bool _is_directed): N(_n), G(_n), is_directed(_is_directed) {};

    void resize(int _n){
        N = _n;
        G.resize(_n);
    }

    void add_edge(int from, int to){
        if(is_directed){
            G[from].emplace_back(unweighted_edge{from, to, M});
            E.emplace_back(unweighted_edge{from, to, M++});
        }
        else{
            G[from].emplace_back(unweighted_edge{from, to, M});
            G[to].emplace_back(unweighted_edge{to, from, M});
            E.emplace_back(unweighted_edge{std::min(from, to), std::max(from, to), M++});
        }
    }

    const std::vector<unweighted_edge> &operator[](int _n){ return G[_n]; }

    const unweighted_graph &operator=(const unweighted_graph &graph){
        N = graph.N;
        M = graph.M;
        G = graph.G;
        E = graph.E;
        return *this;
    }

    bool operator==(const unweighted_graph &graph){
        assert(is_directed == graph.is_directed);
        if(N != graph.N) return false;
        if(M != graph.M) return false;
        std::vector<std::vector<std::vector<int>>> adjacency_matrix(2, std::vector<std::vector<int>>(N, std::vector<int>(N, false)));
        for(unweighted_edge &e : E){
            adjacency_matrix[0][e.from][e.to] = true;
            if(!is_directed) adjacency_matrix[0][e.to][e.from] = true;
        }
        for(const unweighted_edge &e : graph.E){
            adjacency_matrix[1][e.from][e.to] = true;
            if(!is_directed) adjacency_matrix[1][e.to][e.from] = true;
        }

        std::vector<int> nodes_id(N);
        std::iota(nodes_id.begin(), nodes_id.end(), 0);
        do{
            bool same = true;
            for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(adjacency_matrix[0][i][j] != adjacency_matrix[1][nodes_id[i]][nodes_id[j]]) same = false;
            if(same) return true;
        }while(std::next_permutation(nodes_id.begin(), nodes_id.end()));
        return false;
    }

    void print(){
        std::cout << N << " " << M << std::endl;
        for(unweighted_edge &e : E) std::cout << e.from << " " << e.to << std::endl;
    }
};

template<typename WEIGHT>
struct weighted_edge{
    int from;
    int to;
    WEIGHT cost;
    int id;
    friend bool operator>(const weighted_edge &e1, const weighted_edge &e2){ return e1.cost > e2.cost; }
    friend bool operator>=(const weighted_edge &e1, const weighted_edge &e2){ return e1.cost >= e2.cost; }
    friend bool operator<(const weighted_edge &e1, const weighted_edge &e2){ return e1.cost < e2.cost; }
    friend bool operator<=(const weighted_edge &e1, const weighted_edge &e2){ return e1.cost <= e2.cost; }
};

template<typename WEIGHT>
struct weighted_graph{
    int N, M = 0;
    std::vector<std::vector<weighted_edge<WEIGHT>>> G;
    std::vector<weighted_edge<WEIGHT>> E;
    const bool is_directed;

    weighted_graph() : N(0), is_directed(false) {}
    weighted_graph(bool _is_directed): N(0), G(0), is_directed(_is_directed) {};
    weighted_graph(int _n, bool _is_directed): N(_n), G(_n), is_directed(_is_directed) {};

    void resize(int _n){
        N = _n;
        G.resize(_n);
    }

    void add_edge(int from, int to, WEIGHT weight){
        if(is_directed){
            G[from].emplace_back(weighted_edge<WEIGHT>{from, to, weight, M});
            E.emplace_back(weighted_edge<WEIGHT>{from, to, weight, M++});
        }
        else{
            G[from].emplace_back(weighted_edge<WEIGHT>{from, to, weight, M});
            G[to].emplace_back(weighted_edge<WEIGHT>{to, from, weight, M});
            E.emplace_back(weighted_edge<WEIGHT>{std::min(from, to), std::max(from, to), weight, M++});
        }
    }

    std::vector<weighted_edge<WEIGHT>> &operator[](int _n){ return G[_n]; }

    const weighted_graph<WEIGHT> &operator=(const weighted_graph<WEIGHT> &graph){
        N = graph.N;
        M = graph.M;
        G = graph.G;
        E = graph.E;
        return *this;
    }

    bool operator==(const weighted_graph<WEIGHT> &graph){
        assert(is_directed == graph.is_directed);
        if(N != graph.N) return false;
        if(M != graph.M) return false;
        std::vector<std::vector<std::vector<WEIGHT>>> adjacency_matrix(2, std::vector<std::vector<WEIGHT>>(N, std::vector<WEIGHT>(N, 0)));
        for(weighted_edge<WEIGHT> &e : E){
            adjacency_matrix[0][e.from][e.to] = e.cost;
            if(!is_directed) adjacency_matrix[0][e.to][e.from] = e.cost;
        }
        for(const weighted_edge<WEIGHT> &e : graph.E){
            adjacency_matrix[1][e.from][e.to] = e.cost;
            if(!is_directed) adjacency_matrix[1][e.to][e.from] = e.cost;
        }

        std::vector<int> nodes_id(N);
        std::iota(nodes_id.begin(), nodes_id.end(), 0);
        do{
            bool same = true;
            for(int i=0; i<N; i++) for(int j=0; j<N; j++) if(adjacency_matrix[0][i][j] != adjacency_matrix[1][nodes_id[i]][nodes_id[j]]) same = false;
            if(same) return true;
        }while(next_permutation(nodes_id.begin(), nodes_id.end()));
        return false;
    }

    void print(){
        std::cout << N << " " << M << std::endl;
        for(weighted_edge<WEIGHT> &e : E) std::cout << e.from << " " << e.to << " " << e.cost << " " << e.id << std::endl;
    }
};

#endif