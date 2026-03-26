#pragma once

#include <typeindex>
#include <memory>
#include <unordered_map>
#include "component.hpp"

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
