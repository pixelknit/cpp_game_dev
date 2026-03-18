#include "store.hpp"
#include "book_store.hpp"

BookStore::BookStore(size_t ID, std::string &NAME, std::unordered_map<std::string, Item*> &ITEMS, std::string &BOOK_TYPES)
    :Store(ID, NAME, ITEMS), m_book_types(std::move(BOOK_TYPES)){

    }

    void BookStore::GetAllItems() const{
        for (auto & x: m_items){
            std::cout << x.first << "\n";
            x.second->GetItemInfo();
            std::cout << "\n";
        }
    }
    void BookStore::AddItem(std::string &item_name, Item* item) {
        m_items[item_name] = item;
        std::cout << "Added item: " << item_name << "\n";
    }
