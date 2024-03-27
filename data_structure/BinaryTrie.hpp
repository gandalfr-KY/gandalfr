#pragma once

#include <memory>
#include "gandalfr/types.hpp"

namespace gandalfr {

template <u32 bit_width> struct BinaryTrie {
    static_assert(bit_width <= 64, "bit_width must be 64 or less");

  private:
    struct BinaryTrieNode {
        std::shared_ptr<BinaryTrieNode> child[2] = {nullptr, nullptr};
        std::shared_ptr<BinaryTrieNode> par = nullptr;
        u32 level;
        BinaryTrieNode(u32 lvl) : level(lvl) {}
        u32 num_children() {
            if (child[0] && child[1])
                return 2;
            else if (child[0] || child[1])
                return 1;
            else
                return 0;
        }
    };
    std::shared_ptr<BinaryTrieNode> root =
        std::make_shared<BinaryTrieNode>(bit_width - 1);

  public:
    void insert(u64 n) {
        auto cur = root;
        while (cur->level) {
            bool b = (n >> cur->level) & 1;
            if (!cur->child[b]) {
                cur->child[b] =
                    std::make_shared<BinaryTrieNode>(cur->level - 1);
                cur->child[b]->par = cur;
            }
            cur = cur->child[b];
        }
    }

    u32 count(u64 n) {
        auto cur = root;
        while (cur->level) {
            bool b = (n >> cur->level) & 1;
            if (!cur->child[b]) {
                return 0;
            }
            cur = cur->child[b];
        }
        return 1;
    }

    void erase(u64 n) {
        auto cur = root;
        while (cur->level) {
            bool b = (n >> cur->level) & 1;
            if (!cur->child[b]) {
                return;
            }
            cur = cur->child[b];
        }
        while (cur->par && !cur.num_children()) {
            auto tmp = cur;
            cur = cur->par;
            tmp.reset();
        }
    }
};
} // namespace gandalfr
