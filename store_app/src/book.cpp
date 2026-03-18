#include "book.hpp"

Book::Book(size_t ID, float WEIGHT, float HEIGHT, std::string &NAME,
           std::string &TYPE, std::string &PUBLISHER, std::string &AUTHOR)
    : Item(ID, WEIGHT, HEIGHT, NAME, TYPE), m_publisher(std::move(PUBLISHER)),
      m_author(std::move(AUTHOR)) {}

void Book::GetItemInfo() const {
  std::cout << "The Book name is: " << m_name << "\n";
  std::cout << "The Book author is:" << m_author << "\n";
}