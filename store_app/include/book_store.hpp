#pragma once

#include "store.hpp"
#include "item.hpp"
#include <cstddef>
#include <iostream>
#include <unordered_map>

class BookStore: public Store{
    private:
        std::string m_book_types;
    
    public:
    BookStore(size_t ID, std::string &NAME, std::unordered_map<std::string, Item*> &ITEMS, std::string &BOOK_TYPES);

    void GetAllItems() const override;
    void AddItem(std::string &item_name, Item* item) override;
};