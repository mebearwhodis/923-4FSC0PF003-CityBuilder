#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: write readme to explain buttons and mechanics - and switch the repo to public
//TODO: check all #include guards and Google style guide

//TODO: Add a way to get trees and berries to grow back -> Tilemap Tick() -> tire un nombre aléatoire, pourcentage de chance qu'un arbre et/ou baie aléatoire repousse
//TODO: Save & Load system

//TODO: maybe add an idle state to the BT, or something they can do when there are no available resources or no path to it -> check for a certain number of tries in the pathfinding? idk / try again every x seconds
//TODO: Add trading system ?
//TODO: Cap building costs at 999 and population at ??/??

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}