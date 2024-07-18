#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: END write readme to explain buttons and mechanics - and switch the repo to public
//TODO: CLEANUP check all #include guards and Google style guide
//TODO: END Remove debug square

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}