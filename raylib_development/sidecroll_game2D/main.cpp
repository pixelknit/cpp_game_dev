#include "raylib.h"
#include "src/config.h"
#include "src/game.hpp"

int main(){
    Game game;

    while (!game.ShouldClose()){

        float deltaTime = GetFrameTime();

        game.HandleInput();
        game.Update(deltaTime);
        game.Draw();
    }

    return 0;
}