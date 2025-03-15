// #define _GLIBCXX_DEBUG

#include <bits/stdc++.h>

#include "gandalfr/other/io.hpp"
#include "gandalfr/types.hpp"
using namespace std;
using namespace gandalfr;

constexpr i32 board_size = 20;
char S[board_size][board_size];

struct Table {
    char table[board_size][board_size];
    Table() {
        rep(i, 0, board_size) {
            rep(j, 0, board_size) { table[i][j] = S[i][j]; }
        }
    }
    void act() {}
    void print() {
        rep(i, 0, board_size) {
            rep(j, 0, board_size) { cout << S[i][j]; }
            cout << endl;
        }
    }
};

struct Grid {
    i8 h = 0, w = 0;
    Grid() = default;
    Grid(i8 h, i8 w) : h(h), w(w) {}

    bool isValid() const { return (0 <= h && h < _H && 0 <= w && w < _W); }

    /**
     * 周囲 8 マスの位置を得る
     * 範囲外の座標はユーザが弾く方針で
     * | 7 3 4 |
     * | 2 x 0 |
     * | 6 1 5 |
     */
    std::vector<Grid> getAround() {
        std::vector<Grid> around = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};
        for (auto &g : around) {
            g.h += this->h, g.w += this->w;
        }
        return around;
    }

    // マンハッタン距離が2以下の座標を得る（現在地含む）
    std::vector<Grid> getAroundManhattan() {
        std::vector<Grid> around = {
            {-2, 0}, {-1, -1}, {-1, 0}, {-1, 1}, {0, -2}, {0, -1}, {0, 0},
            {0, 1},  {0, 2},   {1, -1}, {1, 0},  {1, 1},  {2, 0}};
        for (auto &g : around) {
            g.h += this->h, g.w += this->w;
        }
        return around;
    }

    std::strong_ordering operator<=>(const Grid &other) const {
        if (auto cmp = h <=> other.h; cmp != 0)
            return cmp;
        return w <=> other.w;
    }

    bool operator==(const Grid &other) const = default;

    Grid &operator+=(const Grid &other) {
        this->h += other.h;
        this->w += other.w;
        return *this;
    }

    Grid operator+(const Grid &other) { return Grid(*this) += other; }

    friend std::ostream &operator<<(std::ostream &os, const Grid &a) {
        os << a.h << ' ' << a.w;
        return os;
    }
    friend std::istream &operator>>(std::istream &is, Grid &a) {
        is >> a.h >> a.w;
        return is;
    }

    static void setSize(i8 H, i8 W) {
        _H = H;
        _W = W;
    }

  private:
    static inline i8 _H = 0, _W = 0;
};

// parentからの操作の差分を持つ
struct Node : public enable_shared_from_this<Node> {
    friend class Tree;

    shared_ptr<Node> _parent = nullptr;
    list<Node *> _children;
    list<Node *>::iterator _self;

  public:
    Node() = default;

    void proceed(Table &state) {}
    void rollback(Table &state) {}

    i32 score() const { return 0; }

    bool operator<(const Node &other) const { return score() < other.score(); }
};
bool operator<(const shared_ptr<Node> a, const shared_ptr<Node> b) {
    return a->score() < b->score();
}

struct Tree {
    shared_ptr<Node> _root, _ans;
    vector<shared_ptr<Node>> _vec, _nxvec;
    Table _ans_table;

    Tree(shared_ptr<Node> root) : _root(root), _ans(root) {
        _vec.push_back(_root);
    }

    void action(Table &state, shared_ptr<Node> cur) {
        // 次の状態を _nxvec に追加
    }

    void euler_tour(Table &state, shared_ptr<Node> cur) {
        if (cur->_children.empty()) {
            if (chmax(_ans, cur)) {
                _ans_table = state;
            }
            action(state, cur);
            return;
        }
        for (auto child : cur->_children) {
            child->proceed(state);
            euler_tour(state, child->shared_from_this());
            child->rollback(state);
        }
    }

    // Eulrer Tourで各葉を探索した後，_rootまで戻ってくる．
    bool traverse(Table &state) {
        euler_tour(state, _root);

        auto get_beam_width = [&]() { return 20; };

        if (_nxvec.empty()) {
            _vec.clear();
            return false;
        } else {
            i32 beam_width = get_beam_width();
            partial_sort(
                _nxvec.begin(), _nxvec.begin() + beam_width, _nxvec.end(),
                [](auto a, auto b) { return a->score() > b->score(); });
            _vec = vector<shared_ptr<Node>>(_nxvec.begin(),
                                            _nxvec.begin() + beam_width);
            _nxvec.clear();
            return true;
        }
    }

    ~Tree() {
        if (_ans)
            _ans = nullptr;
        assert(_root->_children.empty());
    }
};

shared_ptr<Node> input() {
    Grid::setSize(board_size, board_size);
    i32 tmp;
    cin >> tmp;
    rep(i, 0, board_size) {
        string s;
        cin >> s;
        rep(j, 0, board_size) { S[i][j] = s[j]; }
    }
    return make_shared<Node>();
}

int main() {
    Tree tree(input());
    Table state;
    state.print();
    while (tree.traverse(state))
        ;
}
