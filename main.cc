#include <Tracy/Tracy.hpp>
#include "game.h"

//TODO: check all #include guards and Google style guide
//TODO: have text update when something changes
//TODO: have little guys actually harvest resources - give them a variable of how many resources they have, icnrement it when they harvest and put it in the 'storage' when they get back home/to the storage
//TODO: Save & Load system

//TODO maybe add an idle state to the BT, or something they can do when there are no available resources -> check for a certain number of tries in the pathfinding? idk
//TODO Add a way to get trees to grow back
//TODO Add trading system ?

//TODO: Set building_type to plain after building something to avoid being able to build without engouh resources OR check again when constructing

int main() {
    Game game;
    game.init();
    game.update();

    return 0;
}