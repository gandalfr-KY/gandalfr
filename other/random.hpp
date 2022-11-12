#ifndef RANDOM
#define RANDOM
#include <random>
#include "gandalfr/graph/graph.hpp"

struct random_utility{
    random_utility(int seed = 0) { mt.seed(seed); }

    long long random_int(long long min_value, long long max_value){
        std::uniform_int_distribution<long long> distribution(min_value, max_value);
        return distribution(mt);
    }

    double random_double(double min_value, double max_value){
        std::uniform_real_distribution<double> distribution(min_value, max_value);
        return distribution(mt);
    }

    std::vector<int> shuffled_array(const size_t size, int rand_min, int rand_max){
        assert(rand_max - rand_min + 1 >= size);

        std::vector<int> tmp;
        std::uniform_int_distribution<int> distribution(rand_min, rand_max);

        if(rand_max - rand_min + 1 >= size * 4){
            const size_t make_size = static_cast<size_t>(size*1.2);

            while(tmp.size() < size){
                while(tmp.size() < make_size) tmp.push_back(distribution(mt));
                std::sort(tmp.begin(), tmp.end());
                auto unique_end = std::unique(tmp.begin(), tmp.end());

                if(size < std::distance(tmp.begin(), unique_end)){
                    unique_end = std::next(tmp.begin(), size);
                }
                tmp.erase(unique_end, tmp.end());
            }

            std::shuffle(tmp.begin(), tmp.end(), mt);
        }
        else{
            for(int i=rand_min; i<=rand_max; i++) tmp.push_back(i);
            std::shuffle(tmp.begin(), tmp.end(), mt);
            tmp.erase(std::next(tmp.begin(), size), tmp.end());
        }
        return tmp;
    }

    std::vector<int> sorted_array(const size_t size, int rand_min, int rand_max){
        assert(rand_max - rand_min + 1 >= size);
        std::vector<int> tmp = shuffled_array(size, rand_min, rand_max);
        std::sort(tmp.begin(), tmp.end());
        return tmp;
    }

    unweighted_graph<false> generate_unweighted_graph(int N, int M, bool is_connected = true){
        assert(M <= N * (N - 1) / 2);
        if(is_connected) M -= N - 1;
        assert(M >= 0);
        unweighted_graph<false> ret(N);
        if(is_connected) {
            for(int i=1; i<N; i++) ret.add_edge(i, random_int(0, i-1));
        }
        std::vector<std::vector<int>> from_to(N, std::vector<int>(N, true));
        std::vector<std::pair<int, int>> edges;

        for(const unweighted_edge &e : ret.edge_set()) from_to[e.from][e.to] = false;
        for(int i=0; i<N; i++) for(int j=i+1; j<N; j++) if(from_to[i][j]) edges.push_back({i, j});
        std::vector<int> selected_edge = sorted_array(M, 0, edges.size() - 1);
        for(int x : selected_edge) ret.add_edge(edges[x].first, edges[x].second);
        return ret;
    }

  private:
    std::mt19937 mt;

};

#endif