#pragma once

#include "entity.hpp"

struct Person: public Entity{
  float m_weight;
  std::string m_name;
};

struct Animal: public Entity{
  float m_weight;
  std::string m_species;
};