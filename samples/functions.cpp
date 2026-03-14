#include <iostream>
#include <vector>

void Func(std::string &player){
    player += "_server"; 
}

std::string Func2(std::string &player){
    return player + "_new_server";
}

int main(){

    std::string player1 {"One"};
    std::string player2 {"Two"};
    std::string player3 {"Three"};

    std::cout << player1 << "\n";
    Func(player1);
    std::cout << player1 << "\n";

    std::string new_server = Func2(player2);
    std::cout << player2 << "\n";
    std::cout << new_server << "\n";

    std::cout << "--------------------------\n"

    return 0;
}