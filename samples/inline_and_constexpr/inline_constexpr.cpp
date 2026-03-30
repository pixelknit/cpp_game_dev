#include <iostream>

constexpr double PI = 3.141592;

void PrintData(int value){
    std::cout << value << "\n";
}

constexpr int MultTest(int a, int b){
    return a * b;
}

int main(){

    PrintData(10);
    PrintData(100);

    constexpr int c = MultTest(50, 2);

    //

    return 0;
}