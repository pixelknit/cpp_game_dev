#include "store.hpp"

Store::Store(size_t ID, std::string &NAME,
             std::unordered_map<std::string, Item *> &ITEMS):
             m_id(std::move(ID)), m_items(std::move(ITEMS)) {

             }
