#pragma once

#include "Graph.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
void GRAPH_TYPE::preorderImpl(i32 cu, std::vector<bool> &visited,
                              std::vector<i32> &result) const {
    result.push_back(cu);
    for (auto &e : G[cu]) {
        i32 to = e->dst(cu);
        if (visited[to])
            continue;
        visited[to] = true;
        preorderImpl(to, visited, result);
    }
}

GRAPH_TEMPLATE
void GRAPH_TYPE::inorderImpl(i32 cu, std::vector<bool> &visited,
                             std::vector<i32> &result) const {
    for (auto &e : G[cu]) {
        i32 to = e->dst(cu);
        if (visited[to])
            continue;
        visited[to] = true;
        result.push_back(cu);
        inorderImpl(to, visited, result);
    }
    result.push_back(cu);
}

GRAPH_TEMPLATE
void GRAPH_TYPE::postorderImpl(i32 cu, std::vector<bool> &visited,
                               std::vector<i32> &result) const {
    for (auto &e : G[cu]) {
        i32 to = e->dst(cu);
        if (visited[to])
            continue;
        visited[to] = true;
        postorderImpl(to, visited, result);
    }
    result.push_back(cu);
}

GRAPH_TEMPLATE
void GRAPH_TYPE::parentsImpl(i32 cu, std::vector<bool> &visited,
                             std::vector<i32> &result) const {
    for (auto &e : G[cu]) {
        i32 to = e->dst(cu);
        if (visited[to])
            continue;
        visited[to] = true;
        result[to] = cu;
        parentsImpl(to, visited, result);
    }
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::preorder(i32 start) const {
    std::vector<i32> result;
    std::vector<bool> visited(N, false);
    visited[start] = true;
    preorderImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::preorder(i32 start,
                                      std::vector<bool> &visited) const {
    assert(!visited[start]);
    std::vector<i32> result;
    visited[start] = true;
    preorderImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::inorder(i32 start) const {
    std::vector<i32> result;
    std::vector<bool> visited(N, false);
    visited[start] = true;
    inorderImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::inorder(i32 start,
                                     std::vector<bool> &visited) const {
    assert(!visited[start]);
    std::vector<i32> result;
    visited[start] = true;
    inorderImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::postorder(i32 start) const {
    std::vector<i32> result;
    std::vector<bool> visited(N, false);
    visited[start] = true;
    postorderImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::postorder(i32 start,
                                       std::vector<bool> &visited) const {
    assert(!visited[start]);
    std::vector<i32> result;
    visited[start] = true;
    postorderImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::parents(i32 start) const {
    std::vector<i32> result(N, -1);
    std::vector<bool> visited(N, false);
    visited[start] = true;
    parentsImpl(start, visited, result);
    return result;
}

GRAPH_TEMPLATE
std::vector<i32> GRAPH_TYPE::parents(i32 start, std::vector<bool> &visited,
                                     std::vector<i32> &result) const {
    assert(!visited[start]);
    visited[start] = true;
    parentsImpl(start, visited, result);
    return result;
}

} // namespace gandalfr
