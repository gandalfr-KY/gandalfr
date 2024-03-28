#pragma once

#include <assert.h>
#include <memory>
#include <utility>

#include "gandalfr/types.hpp"

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
        // 00: xx, 01: xo, 10: ox, 11: oo
        u32 stateOfChildren() const {
            u32 state = ((bool)children[1] << 1) | (bool)children[0];
            return state;
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
    NodePtr rootPtr = std::make_shared<BinaryTrieNode>(bit_width);

    NodePtr getNodePtr(u64 n) const {
        NodePtr curPtr = rootPtr;
        while (!curPtr->isLeaf()) {
            curPtr->affectXor();
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (!nxtPtr) {
                return nullptr;
            }
            curPtr = nxtPtr;
        }
        return curPtr;
    }

  public:
    void insert(u64 n) {
        NodePtr curPtr = rootPtr;
        while (!curPtr->isLeaf()) {
            curPtr->affectXor();
            curPtr->sub_cnt += 1;
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (!nxtPtr) {
                nxtPtr = std::make_shared<BinaryTrieNode>(curPtr->level - 1);
            }
            curPtr = nxtPtr;
        }
        assert(curPtr->isLeaf());
        curPtr->sub_cnt += 1;
    }

    u32 size() const { return rootPtr->sub_cnt; }

    u32 count(u64 n) const {
        NodePtr ptr = getNodePtr(n);
        return (ptr ? ptr->sub_cnt : 0);
    }

    void erase(u64 n) const {
        u32 cnt = count(n);
        if (cnt == 0)
            return;
        NodePtr curPtr = rootPtr;
        while (true) {
            curPtr->affectXor();
            curPtr->sub_cnt -= cnt;
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (nxtPtr->sub_cnt == cnt) {
                nxtPtr = nullptr;
                return;
            }
            curPtr = nxtPtr;
        }
    }

    void eraseOne(u64 n) const {
        if (count(n) == 0)
            return;
        NodePtr curPtr = rootPtr;
        while (!curPtr->isLeaf()) {
            curPtr->affectXor();
            curPtr->sub_cnt -= 1;
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (nxtPtr->sub_cnt == 1) {
                nxtPtr = nullptr;
                return;
            }
            curPtr = nxtPtr;
        }
        curPtr->sub_cnt -= 1;
    }

    // n: 0-indexed
    u64 nthElement(u32 n) const {
        assert(n < size());
        u64 ret = 0;
        NodePtr curPtr = rootPtr;
        while (!curPtr->isLeaf()) {
            curPtr->affectXor();
            ret <<= 1;
            u32 state = curPtr->stateOfChildren();
            NodePtr &zPtr = curPtr->children[0];
            NodePtr &oPtr = curPtr->children[1];
            assert(state > 0);
            if (state == 1 || (state == 3 && n < zPtr->sub_cnt)) {
                curPtr = zPtr;
            } else {
                n -= (state & 1 ? zPtr->sub_cnt : 0);
                ret |= 1;
                curPtr = oPtr;
            }
        }
        return ret;
    }

    // https://atcoder.jp/contests/abc312/submissions/51738375
    u32 lowerBound(u64 n) const {
        u32 ret = 0;
        NodePtr curPtr = rootPtr;
        while (!curPtr->isLeaf()) {
            curPtr->affectXor();
            bool b = curPtr->getBit(n);
            NodePtr &nxtPtr = curPtr->children[b];
            NodePtr &zPtr = curPtr->children[0];
            if (b && zPtr) {
                ret += zPtr->sub_cnt;
            }
            if (!nxtPtr) {
                break;
            }
            curPtr = nxtPtr;
        }
        return ret;
    }

    u32 upperBound(u64 n) const { return lowerBound(n + 1); }

    void applyXor(u64 n) { rootPtr->xval ^= n; }
};
} // namespace gandalfr
