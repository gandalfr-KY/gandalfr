#pragma once

#include <list>
#include <unordered_map>

template <typename KeyType, typename ValueType,
          typename Hash = std::hash<KeyType>>
class lru_cache {
  private:
    using Item = std::pair<KeyType, ValueType>;
    using ItemList = std::list<Item>;
    using ItemMap =
        std::unordered_map<KeyType, typename ItemList::iterator, Hash>;

    ItemList item_list;
    ItemMap item_map;
    size_t capacity;

  public:
    using iterator = typename ItemList::iterator;

    lru_cache(size_t size) : capacity(size) {}

    void put(const KeyType &key, const ValueType &value) {
        auto found = item_map.find(key);
        if (found != item_map.end()) {
            item_list.erase(found->second);
            item_map.erase(found);
        }
        if (item_list.size() == capacity) {
            item_map.erase(item_list.front().first);
            item_list.pop_front();
        }
        item_list.push_back(std::make_pair(key, value));
        item_map[key] = std::prev(item_list.end());
    }

    iterator get(const KeyType &key) {
        auto found = item_map.find(key);
        if (found == item_map.end()) {
            return end();
        }
        item_list.splice(item_list.end(), item_list, found->second);
        return found->second;
    }

    iterator begin() { return item_list.begin(); }
    iterator end() { return item_list.end(); }
    iterator find(const KeyType &key) {
        auto found = item_map.find(key);
        return found != item_map.end() ? found->second : item_list.end();
    }
};
