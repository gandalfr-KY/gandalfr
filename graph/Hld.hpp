#pragma once

#include "Graph.hpp"

namespace gandalfr {

GRAPH_TEMPLATE
class Hld {
  private:
    GRAPH_TYPE _G;
    std::vector<i32> _sz, _in, _out, _head, _par;
    i32 t = 0;

    void dfsSz(i32 v, i32 p = -1) {
        _par[v] = p;
        for (auto &e : _G.G[v]) {
            i32 u = e->dst(v);
            if (u == p)
                continue;
            dfsSz(u, v);
            _sz[v] += _sz[u];
            if (_sz[u] > _sz[_G[v][0]->dst(v)])
                std::swap(e, _G.G[v][0]);
        }
    }

    void dfsHld(i32 v, i32 p = -1) {
        _in[v] = t++;
        for (auto &e : _G[v]) {
            i32 u = e->dst(v);
            if (u == p)
                continue;
            _head[u] = (u == _G[v][0]->dst(v) ? _head[v] : u);
            dfsHld(u, v);
        }
        _out[v] = t;
    }

  public:
    Hld(const GRAPH_TYPE &G, i32 root = 0)
        : _G(G), _sz(G.numNodes(), 1), _in(G.numNodes()), _out(G.numNodes()),
          _head(G.numNodes()), _par(G.numNodes()) {
        _head[root] = root;
        dfsSz(root);
        dfsHld(root);
    }

    /**
     * [in_v, out_v)
     */
    std::pair<i32, i32> node(i32 v) const { return {_in[v], _out[v]}; }

    /**
     * [in, out) のリストが返る
     * 各区間に対してクエリ処理すればよい
     */
    std::vector<std::pair<i32, i32>> path(i32 u, i32 v) const {
        std::vector<std::pair<i32, i32>> intervals;
        while (true) {
            if (_in[u] > _in[v])
                std::swap(u, v);
            intervals.emplace_back(std::max(_in[_head[v]], _in[u]), _in[v] + 1);
            if (_head[u] == _head[v])
                break;
            v = _par[_head[v]];
        }
        return intervals;
    }
};
} // namespace gandalfr
