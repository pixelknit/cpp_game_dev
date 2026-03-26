#pragma once

#include <iostream>

struct Component{
  virtual ~Component() = default;
};

struct EatingComponent: public Component{
  void Eat();
};

struct FlyingComponent: public Component{
  void Fly();
};