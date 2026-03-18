#pragma once

#include <iostream>

class Item {
protected:
  size_t m_id;
  float m_weight;
  float m_height;
  std::string m_name;
  std::string m_type;

public:
  Item(size_t ID, float WEIGHT, float HEIGHT, std::string &NAME,
       std::string &TYPE);

  virtual void GetItemInfo() const = 0;
};