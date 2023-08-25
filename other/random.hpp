#pragma once
#include <random>

#include "../graph/graph.hpp"

template <int id> struct random_utility {
    static inline std::mt19937 mt;

    static void set_seed(int seed) {
        mt.seed(seed); // mtにseedを設定
    }

    static long long random_int(long long min_value, long long max_value) {
        std::uniform_int_distribution<long long> distribution(min_value,
                                                              max_value);
        return distribution(mt);
    }

    static double random_double(double min_value, double max_value) {
        std::uniform_real_distribution<double> distribution(min_value,
                                                            max_value);
        return distribution(mt);
    }

    static graph<int, false> generate_tree(int V) {
        graph<int, false> g(V);
        for (int i = 1; i < V; ++i) {
            g.add_edge(random_int(0, i - 1), i);
        }
        return g;
    }
};

using rnd = random_utility<-1>;
