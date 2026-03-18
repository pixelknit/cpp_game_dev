#include "item.hpp"

Item::Item(size_t ID, float WEIGHT, float HEIGHT, std::string &NAME,
           std::string &TYPE)
    : m_id(std::move(ID)), m_weight(std::move(WEIGHT)), m_height(std::move(HEIGHT)), m_name(std::move(NAME)),
      m_type(std::move(TYPE)) {}