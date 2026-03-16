#pragma once

#include <iostream>

namespace main_character{
    void walk(){
        std::cout << "The main character is walking\n";
    }
}

namespace enemy{
    void walk(){
        std::cout << "The enemy is walking\n";
    }
}

namespace npc{
    void walk(){
        std::cout << "The npc is walking\n";
    }
}