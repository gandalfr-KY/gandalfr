#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"

#include <queue>

#include "testenv.hpp"
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/Lca.hpp"
#include "gandalfr/graph/lowlink.hpp"

using namespace gandalfr;

TEST(GRAPH, LCA) {
    Graph<UNWEIGHTED, UNDIRECTED> G(10);
    G.addEdge(0, 1);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(1, 8);
    G.addEdge(2, 5);
    G.addEdge(4, 5);
    G.addEdge(4, 9);
    G.addEdge(5, 6);
    G.addEdge(5, 7);

    Lca lca(G, 2);
    
    EQ(lca.getAncestor(1, 5), 2);
    EQ(lca.getAncestor(7, 9), 5);
    EQ(lca.getAncestor(0, 8), 1);
    EQ(lca.getAncestor(2, 8), 2);
}

TEST(GRAPH, BRIDGES) {
    Graph<UNWEIGHTED, UNDIRECTED> G(10);
    G.addEdge(0, 1);
    G.addEdge(0, 2);
    G.addEdge(1, 2);
    G.addEdge(1, 3);
    G.addEdge(3, 4); // 4
    G.addEdge(4, 5); // 5
    G.addEdge(6, 7);
    G.addEdge(6, 8);
    G.addEdge(7, 8);
    G.addEdge(8, 9); // 9
    G.addEdge(3, 1); // duplicated

    std::vector<Edge<false>> expectedBridges = 
    {
        // Edge<false>(1, 3, 3), 
        Edge<false>(3, 4, 4), 
        Edge<false>(4, 5, 5), 
        Edge<false>(8, 9, 9)
    };
    
    auto tmp = G.bridges();
    for (auto &e : tmp) if (e.v0 > e.v1) std::swap(e.v0, e.v1);
    sort(all(tmp), [](Edge<false> a, Edge<false> b) {
        if (a.v0 == b.v0) return a.v1 < b.v1;
        return a.v0 < b.v0;
    });

    EQ(tmp.size(), expectedBridges.size());
    rep(i,0,expectedBridges.size()) {
        EQ(tmp[i].v0, expectedBridges[i].v0);
        EQ(tmp[i].v1, expectedBridges[i].v1);
        EQ(tmp[i].id, expectedBridges[i].id);
    }
}

int main() {
    RunAllTests<false>();
    return 0;
}
