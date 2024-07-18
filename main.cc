#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: END write readme to explain buttons and mechanics - and switch the repo to public
//TODO: CLEANUP check all #include guards and Google style guide

//TODO: SOON Save & Load system

//TODO: VERY SOON maybe add an idle state to the BT, or something they can do when there are no available resources or no path to it -> check for a certain number of tries in the pathfinding? idk / try again every x seconds

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}