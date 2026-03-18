#include "book.hpp"
#include "book_store.hpp"
#include <unordered_map>

int main(){

    size_t id = 10;
    float weight = 123.2f;
    float height = 12.4f;
    std::string name = "Lord of the Rings";
    std::string type = "book";
    std::string publisher = "HarperCollins";
    std::string author = "JRR Tolkien";

    Book Book1 = Book(id, weight, height, name, type, publisher, author);

    //-----------------------------------------------------------------------

    size_t bs_id = 12;
    std::string bs_name = "SomeBookStore";
    std::unordered_map<std::string, Item*> bs_items;
    std::string bs_book_types = "Fantasy Books";

    BookStore book_store1 = BookStore(bs_id, bs_name, bs_items, bs_book_types);
    std::string name_to_add = "Lord of the Rings";
    book_store1.AddItem(name_to_add, &Book1);
    book_store1.GetAllItems();

    return 0;
}