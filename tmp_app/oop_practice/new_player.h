#pragma once

#include "player.h"

class NewPlayer: public Player{
    private:
        float newPlayerTest;

    public:
        NewPlayer(int u_value, std::string u_name, float val): Player(u_value, u_name), newPlayerTest(val){

        }

        void GetTest(){
            std::cout << newPlayerTest << "\n";
        }

};