#pragma once

#include <assert.h>
#include <memory>
#include <utility>

#include "../types.hpp"

namespace gandalfr {

template <u32 bit_width> class BinaryTrie {
    static_assert(bit_width <= 64, "bit_width must be 64 or less");
    struct BinaryTrieNode {
        std::shared_ptr<BinaryTrieNode> children[2] = {nullptr, nullptr};
        u32 level, sub_cnt = 0;
        u64 xval = 0;

        BinaryTrieNode(u32 lvl) : level(lvl) {}
        bool getBit(u64 v) const { return (v >> (level - 1)) & 1; }
        bool isLeaf() const { return level == 0; }
        // 0: xx, 1: xo, 2: ox, 3: oo
        u32 stateOfChildren() const {
            return ((bool)children[1] << 1) | (bool)children[0];
        }
        void affectXor() {
            if (getBit(xval)) {
                std::swap(children[0], children[1]);
            }
            if (children[0])
                children[0]->xval ^= xval;
            if (children[1])
                children[1]->xval ^= xval;
            xval = 0;
        }
    };
    using NodePtr = std::shared_ptr<BinaryTrieNode>;
    NodePtr root_ptr = std::make_shared<BinaryTrieNode>(bit_width);

    NodePtr getNodePtr(u64 n) const {
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->isLeaf()) {
            cur_ptr->affectXor();
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->getBit(n)];
            if (!nxt_ptr) {
                return nullptr;
            }
            cur_ptr = nxt_ptr;
        }
        return cur_ptr;
    }

  public:
    void insert(u64 n) {
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->isLeaf()) {
            cur_ptr->affectXor();
            cur_ptr->sub_cnt += 1;
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->getBit(n)];
            if (!nxt_ptr) {
                nxt_ptr = std::make_shared<BinaryTrieNode>(cur_ptr->level - 1);
            }
            cur_ptr = nxt_ptr;
        }
        assert(cur_ptr->isLeaf());
        cur_ptr->sub_cnt += 1;
    }

    u32 size() const { return root_ptr->sub_cnt; }

    u32 count(u64 n) const {
        NodePtr ptr = getNodePtr(n);
        return (ptr ? ptr->sub_cnt : 0);
    }

    void erase(u64 n) const {
        u32 cnt = count(n);
        if (cnt == 0)
            return;
        NodePtr cur_ptr = root_ptr;
        while (true) {
            cur_ptr->affectXor();
            cur_ptr->sub_cnt -= cnt;
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->getBit(n)];
            if (nxt_ptr->sub_cnt == cnt) {
                nxt_ptr = nullptr;
                return;
            }
            cur_ptr = nxt_ptr;
        }
    }

    void eraseOne(u64 n) const {
        if (count(n) == 0)
            return;
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->isLeaf()) {
            cur_ptr->affectXor();
            cur_ptr->sub_cnt -= 1;
            NodePtr &nxt_ptr = cur_ptr->children[cur_ptr->getBit(n)];
            if (nxt_ptr->sub_cnt == 1) {
                nxt_ptr = nullptr;
                return;
            }
            cur_ptr = nxt_ptr;
        }
        cur_ptr->sub_cnt -= 1;
    }

    // n: 0-indexed
    u64 nthElement(u32 n) const {
        assert(n < size());
        u64 ret = 0;
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->isLeaf()) {
            cur_ptr->affectXor();
            ret <<= 1;
            u32 state = cur_ptr->stateOfChildren();
            NodePtr &z_ptr = cur_ptr->children[0];
            NodePtr &o_ptr = cur_ptr->children[1];
            assert(state > 0);
            if (state == 1 || (state == 3 && n < z_ptr->sub_cnt)) {
                cur_ptr = z_ptr;
            } else {
                n -= (state & 1 ? z_ptr->sub_cnt : 0);
                ret |= 1;
                cur_ptr = o_ptr;
            }
        }
        return ret;
    }

    // https://atcoder.jp/contests/abc312/submissions/51738375
    u32 lowerBound(u64 n) const {
        u32 ret = 0;
        NodePtr cur_ptr = root_ptr;
        while (!cur_ptr->isLeaf()) {
            cur_ptr->affectXor();
            bool b = cur_ptr->getBit(n);
            NodePtr &nxt_ptr = cur_ptr->children[b];
            NodePtr &z_ptr = cur_ptr->children[0];
            if (b && z_ptr) {
                ret += z_ptr->sub_cnt;
            }
            if (!nxt_ptr) {
                break;
            }
            cur_ptr = nxt_ptr;
        }
        return ret;
    }

    u32 upperBound(u64 n) const {
        return (n < u64MAX ? lowerBound(n + 1) : size());
    }

    void applyXor(u64 n) { root_ptr->xval ^= n; }

    void clear() { root_ptr = std::make_shared<BinaryTrieNode>(bit_width); }
};
} // namespace gandalfr
