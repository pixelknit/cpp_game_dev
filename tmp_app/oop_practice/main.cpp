#include <iostream>
#include <vector>
#include "player.h"
#include "new_player.h"


int main(){

    int val = 10;
    std::string name = "Felipe";

    Player myPlayer = Player(val, name);
    myPlayer.GetValue();
    myPlayer.SetValue(45);
    myPlayer.GetValue();

    std::cout << "--------------------\n";

    float test = 145.0f;
    NewPlayer player2 = NewPlayer(val, name, test);
    player2.GetValue();
    player2.GetTest();

    return 0;
}