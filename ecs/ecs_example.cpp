#include <iostream>
#include <typeindex>
#include <memory>
#include <unordered_map>

// template<typename T>
// T someFunc(T a, T b){
//   return a + b;
// }
//
// auto a = someFunc(12.2f, 12.5f);
// auto b = someFunc(12, 1);

struct Component{
  virtual ~Component() = default;
};

struct EatingComponent: public Component{
  void Eat(){
    std::cout << "Eating...\n";
  }
};

struct FlyingComponent: public Component{
  void Fly(){
    std::cout << "Flying....\n";
  }
};

struct Entity{
  private:
    std::unordered_map<std::type_index, std::unique_ptr<Component>> components;

  public:
    template<typename T, typename... Args>
    void AddComponent(Args&&... args){
      components[typeid(T)] = std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T>
    T* GetComponent(){
      auto it = components.find(typeid(T));
      if (it != components.end()){
        return static_cast<T*>(it->second.get());
      }
      return nullptr;
    }

    template<typename T>
    bool HasComponent() const{
      return components.count(typeid(T)) > 0;
    }

    template<typename T>
    void RemoveComponent(){
      components.erase(typeid(T));
    }
};

struct Person: public Entity{
  float m_weight;
  std::string m_name;
};

struct Animal: public Entity{
  float m_weight;
  std::string m_species;
};


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
