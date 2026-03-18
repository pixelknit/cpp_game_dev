#pragma once

#include "item.hpp"

class Book : public Item {
private:
  std::string m_publisher;
  std::string m_author;

public:
  Book(size_t ID, float WEIGHT, float HEIGHT, std::string &NAME,
       std::string &TYPE, std::string &PUBLISHER, std::string &AUTHOR);

  void GetItemInfo() const override;
};