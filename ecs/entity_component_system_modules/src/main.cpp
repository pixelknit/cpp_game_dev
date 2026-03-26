#include "entities.hpp"
#include "component.hpp"
#include "entity.hpp"

int main(){
  Person person1;
  person1.m_weight = 143.3f;
  person1.m_name = "Amy";
  person1.AddComponent<EatingComponent>();
  person1.AddComponent<FlyingComponent>();

  std::cout << "Person... \n";
  if (auto* e = person1.GetComponent<EatingComponent>())
    e->Eat();
  if (auto* f = person1.GetComponent<FlyingComponent>())
    f->Fly();

  Animal animal1;
  animal1.m_weight = 143.3f;
  animal1.m_species = "Bird";
  animal1.AddComponent<EatingComponent>();
  animal1.AddComponent<FlyingComponent>();

  std::cout << "Animal... \n";
  if (auto* e = animal1.GetComponent<EatingComponent>())
    e->Eat();
  if (auto* f = animal1.GetComponent<FlyingComponent>())
    f->Fly();
  
  return 0;
}
