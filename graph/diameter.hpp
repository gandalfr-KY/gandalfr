#pragma once
#include <assert.h>

#include <iostream>

#include "shortest_path.hpp"

/**
 * @brief 木の直径
 */
template <typename WEIGHT> WEIGHT diameter(const graph<WEIGHT, false> &G) {
    assert(G.is_tree());
    std::vector<WEIGHT> dist = shortest_path(G, 0);
    int farthest_node =
        std::max_element(dist.begin(), dist.end()) - dist.begin();
    dist = shortest_path(G, farthest_node);
    return *std::max_element(dist.begin(), dist.end());
}
