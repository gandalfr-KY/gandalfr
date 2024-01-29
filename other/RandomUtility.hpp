#pragma once
#include <random>

namespace gandalfr {

template <int id> struct RandomUtility {
    static inline std::mt19937 mt;

    static void set_seed(int seed) { mt.seed(seed); }

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
};
using RandUtil = RandomUtility<-1>;
} // namespace gandalfr
