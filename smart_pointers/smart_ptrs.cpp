#include <iostream>
#include <memory>
#include <numbers>
#include <vector>

class Resource{
  private:
    int id;
  public:
    Resource(int id): id(id){
      std::cout << "Resource: " << id << " adquired\n";
    }

    ~Resource(){
      std::cout << "Resource " << id << " destroyed\n";
    }

    void use(){
      std::cout << "Using resource: " << id << "\n";
    }
};

//unique ptrs
void uniquePtrExample(){
  std::cout << "\n ---- Unique Pointer Example----\n";
  std::unique_ptr<Resource> ptr1 = std::make_unique<Resource>(1);
  ptr1->use();

  //transer ownership
  std::unique_ptr<Resource> ptr2 = std::move(ptr1);
  ptr2->use();
}

//shared ptr
void sharedPointerExample(){
  std::cout << "\n ---- Shared Pointer Example----\n";

  std::shared_ptr<Resource> ptr1 = std::make_shared<Resource>(2);
  std::cout << "Use count: " << ptr1.use_count() << "\n";
  {
    std::shared_ptr<Resource> ptr2 = ptr1;
    std::cout << "Use after copy count: " << ptr1.use_count() << "\n";
  }

  std::cout << "Use count after scope: " << ptr1.use_count() << "\n";

}

//weak ptr
void weakPointerExample(){
  std::cout << "\n ---- Weak Pointer Example----\n";
  
  std::shared_ptr<Resource> shared = std::make_shared<Resource>(3);
  std::weak_ptr<Resource> weak = shared;

  std::cout << "Use count: " << shared.use_count() << "\n";
  
  if (auto temp = weak.lock()){
    temp->use();
  }
  else {
    std::cout << "Resource expired!\n";
  }

  shared.reset();

  if (weak.expired()){
    std::cout << "Resource is now expired!\n";
  }

}

int main(){
  uniquePtrExample();
  sharedPointerExample();
  weakPointerExample();

  return 0;
}
