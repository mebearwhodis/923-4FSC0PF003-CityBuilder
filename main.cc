#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: check all #include guards and Google style guide
//TODO: have text update when something changes
//TODO: have little guys harvest resources
//TODO: Save & Load system

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}