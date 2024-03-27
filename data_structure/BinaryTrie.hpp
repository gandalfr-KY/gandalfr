#pragma once

#include <memory>
#include <assert.h>
#include "gandalfr/types.hpp"

namespace gandalfr {

template <u32 bit_width> struct BinaryTrie {
    static_assert(bit_width <= 64, "bit_width must be 64 or less");

  private:
    struct BinaryTrieNode {
        std::shared_ptr<BinaryTrieNode> children[2] = {nullptr, nullptr};
        u32 level, sub_cnt = 0;
        BinaryTrieNode(u32 lvl) : level(lvl) {}
        // 00: xx, 01: xo, 10: ox, 11: oo
        u32 stateOfChildren() const {
            return ((bool)children[1] << 1) | (bool)children[0];
        }
        bool isLeaf() const {
            return level == 0;
        }
        bool nextIndex(u64 n) const {
            return (n >> (level - 1)) & 1;
        }
    };
    using NodePtr = std::shared_ptr<BinaryTrieNode>;
    NodePtr root = std::make_shared<BinaryTrieNode>(bit_width);
    // u64 xorval = 0;

    NodePtr getNodePtr(u64 n) const {
        NodePtr cur = root;
        while (!cur->isLeaf()) {
            bool b = cur->nextIndex(n);
            if (!cur->children[b]) {
                return nullptr;
            }
            cur = cur->children[b];
        }
        return cur;
    }

  public:
    void insert(u64 n) {
        NodePtr cur = root;
        while (cur->level) {
            cur->sub_cnt += 1;
            bool b = cur->nextIndex(n);
            if (!cur->children[b]) {
                cur->children[b] =
                    std::make_shared<BinaryTrieNode>(cur->level - 1);
            }
            cur = cur->children[b];
        }
        cur->sub_cnt += 1;
    }

    u32 size() const {
        return root->sub_cnt;
    }

    u32 count(u64 n) const {
        NodePtr ptr = getNodePtr(n);
        return (ptr ? ptr->sub_cnt : 0);
    }

    void erase(u64 n) const {
        u32 cnt = count(n);
        if (cnt == 0) return;
        NodePtr cur = root;
        while (true) {
            cur->sub_cnt -= cnt;
            bool b = cur->nextIndex(n);
            if (cur->children[b]->sub_cnt == cnt) {
                cur->children[b] = nullptr;
                return;
            }
            cur = cur->children[b];
        }
    }

    void eraseOne(u64 n) const {
        if (count(n) == 0) return;
        NodePtr cur = root;
        while (!cur->isLeaf()) {
            cur->sub_cnt -= 1;
            bool b = cur->nextIndex(n);
            if (cur->children[b]->sub_cnt == 1) {
                cur->children[b] = nullptr;
                return;
            }
            cur = cur->children[b];
        }
        cur->sub_cnt -= 1;
    }

    // n: 0-indexed
    u64 nthElement(u32 n) const {
        assert(n < size());
        u64 ret = 0;
        NodePtr cur = root;
        while (!cur->isLeaf()) {
            ret <<= 1;
            u32 state = cur->stateOfChildren();
            assert(state > 0);
            if (state == 1 || (state == 3 && n < cur->children[0]->sub_cnt)) {
                cur = cur->children[0];
            } else {
                n -= (state & 1 ? cur->children[0]->sub_cnt : 0);
                ret |= 1;
                cur = cur->children[1];
            }
        }
        return ret;
    }

    // https://atcoder.jp/contests/abc312/submissions/51738375
    u32 lowerBound(u64 n) const {
        u32 ret = 0;
        NodePtr cur = root;
        while (!cur->isLeaf()) {
            bool b = cur->nextIndex(n);
            if (b && cur->children[0]) {
                ret += cur->children[0]->sub_cnt;
            }
            if (!cur->children[b]) {
                break;
            }
            cur = cur->children[b];
        }
        return ret;
    }

    u32 upperBound(u64 n) const {
        return lowerBound(n + 1);
    }


};
} // namespace gandalfr
