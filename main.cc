#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: check all #include guards and Google style guide

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}