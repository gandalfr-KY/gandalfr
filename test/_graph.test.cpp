#define PROBLEM "https://onlinejudge.u-aizu.ac.jp/problems/ITP1_1_A"

#include <queue>

#include "testenv.hpp"
#include "gandalfr/other/io.hpp"
#include "gandalfr/graph/LCA.hpp"

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

    LCA lca(G, 2);
    
    EQ(lca.getAncestor(1, 5), 2);
    EQ(lca.getAncestor(7, 9), 5);
    EQ(lca.getAncestor(0, 8), 1);
    EQ(lca.getAncestor(2, 8), 2);
}

int main() {
    RunAllTests<false>();
    return 0;
}
