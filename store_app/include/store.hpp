#pragma once

#include <cstddef>
#include <iostream>
#include "item.hpp"
#include <unordered_map>

class Store{
    protected:
        size_t m_id;
        std::string m_name;
        std::unordered_map<std::string, Item*> m_items;

    public:
        Store(size_t ID, std::string &NAME, std::unordered_map<std::string, Item*> &ITEMS);

        virtual void GetAllItems() const = 0;
        virtual void AddItem(std::string &item_name, Item* item) = 0; 
};