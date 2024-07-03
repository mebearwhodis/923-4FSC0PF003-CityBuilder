#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: check all #include guards

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}