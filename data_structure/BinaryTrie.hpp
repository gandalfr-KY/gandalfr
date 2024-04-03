#pragma once

#include <assert.h>
#include <memory>
#include <utility>

#include "gandalfr/types.hpp"

namespace gandalfr {

template <u32 bitWidth> class BinaryTrie {
    static_assert(bitWidth <= 64, "bitWidth must be 64 or less");
    struct BinaryTrieNode {
        std::shared_ptr<BinaryTrieNode> children[2] = {nullptr, nullptr};
        u32 level, subCnt = 0;
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
    NodePtr rootPtr = std::make_shared<BinaryTrieNode>(bitWidth);

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
            curPtr->subCnt += 1;
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (!nxtPtr) {
                nxtPtr = std::make_shared<BinaryTrieNode>(curPtr->level - 1);
            }
            curPtr = nxtPtr;
        }
        assert(curPtr->isLeaf());
        curPtr->subCnt += 1;
    }

    u32 size() const { return rootPtr->subCnt; }

    u32 count(u64 n) const {
        NodePtr ptr = getNodePtr(n);
        return (ptr ? ptr->subCnt : 0);
    }

    void erase(u64 n) const {
        u32 cnt = count(n);
        if (cnt == 0)
            return;
        NodePtr curPtr = rootPtr;
        while (true) {
            curPtr->affectXor();
            curPtr->subCnt -= cnt;
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (nxtPtr->subCnt == cnt) {
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
            curPtr->subCnt -= 1;
            NodePtr &nxtPtr = curPtr->children[curPtr->getBit(n)];
            if (nxtPtr->subCnt == 1) {
                nxtPtr = nullptr;
                return;
            }
            curPtr = nxtPtr;
        }
        curPtr->subCnt -= 1;
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
            if (state == 1 || (state == 3 && n < zPtr->subCnt)) {
                curPtr = zPtr;
            } else {
                n -= (state & 1 ? zPtr->subCnt : 0);
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
                ret += zPtr->subCnt;
            }
            if (!nxtPtr) {
                break;
            }
            curPtr = nxtPtr;
        }
        return ret;
    }

    u32 upperBound(u64 n) const {
        return (n < UMAX64 ? lowerBound(n + 1) : size());
    }

    void applyXor(u64 n) { rootPtr->xval ^= n; }

    void clear() { rootPtr = std::make_shared<BinaryTrieNode>(bitWidth); }
};
} // namespace gandalfr
