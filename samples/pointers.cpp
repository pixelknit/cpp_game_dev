#include <iostream>
#include <vector>

int main(){

    int myInt = 1000;
    int myInt2 = 2000;

    std::cout << myInt << "\n";
    const int* const myPtr = &myInt;

    // std::cout << myPtr << "\n";
    // std::cout << *myPtr << "\n";

    return 0;
}