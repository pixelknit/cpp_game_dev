#include <iostream>

struct Node{
  int value;
  Node* next;
};

void PrintList(Node* node){
  Node* current = node;
  while (current != nullptr){
    std::cout << current->value << "\n";
    current = current->next;
  }
}

int main(){
  
  Node head = Node();
  Node middle = Node();
  Node tail = Node();

  head.value = 10;
  head.next = &middle;

  middle.value = 20;
  middle.next = &tail;

  tail.value = 30;
  tail.next = nullptr;

  PrintList(&head);


  return 0;
}
