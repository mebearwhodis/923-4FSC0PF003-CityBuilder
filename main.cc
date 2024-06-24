#include "game.h"

//TODO: check all #include guards

int main() {
    Game game;
    game.init();
    game.update();

#ifdef TRACY_ENABLE
    FrameMark;
#endif

    return 0;
}