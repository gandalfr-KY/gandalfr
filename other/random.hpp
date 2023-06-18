#pragma once
#include <random>

#include "../graph/graph.hpp"

struct random_utility {
    random_utility(int seed = 0) { mt.seed(seed); }

    long long random_int(long long min_value, long long max_value) {
        std::uniform_int_distribution<long long> distribution(min_value,
                                                              max_value);
        return distribution(mt);
    }

    double random_double(double min_value, double max_value) {
        std::uniform_real_distribution<double> distribution(min_value,
                                                            max_value);
        return distribution(mt);
    }

    template <typename T>
    std::vector<T> shuffled_array(const size_t size, T rand_min, T rand_max) {
        assert(rand_max - rand_min + 1 >= (T)size);

        std::vector<T> tmp;
        std::uniform_int_distribution<T> distribution(rand_min, rand_max);

        if (rand_max - rand_min + 1 >= size * 4) {
            const size_t make_size = static_cast<size_t>(size * 1.2);

            while (tmp.size() < size) {
                while (tmp.size() < make_size)
                    tmp.push_back(distribution(mt));
                std::sort(tmp.begin(), tmp.end());
                auto unique_end = std::unique(tmp.begin(), tmp.end());

                if (size < std::distance(tmp.begin(), unique_end)) {
                    unique_end = std::next(tmp.begin(), size);
                }
                tmp.erase(unique_end, tmp.end());
            }

            std::shuffle(tmp.begin(), tmp.end(), mt);
        } else {
            for (int i = rand_min; i <= rand_max; i++)
                tmp.push_back(i);
            std::shuffle(tmp.begin(), tmp.end(), mt);
            tmp.erase(std::next(tmp.begin(), size), tmp.end());
        }
        return tmp;
    }

    template <typename T>
    std::vector<int> sorted_array(const size_t size, T rand_min, T rand_max) {
        assert(rand_max - rand_min + 1 >= (T)size);
        std::vector<T> tmp = shuffled_array(size, rand_min, rand_max);
        std::sort(tmp.begin(), tmp.end());
        return tmp;
    }

  private:
    std::mt19937 mt;
};
