/**
    @file Controls.cpp
    @brief This program implements Controls.h. 
    @author Armin Farhang
    @author Brandon Luu
    @date 09/23/2023
*/

#include "Controls.h"

Controls::Controls() {
    paused = false;
    queue_mod = false;
}

Controls& Controls::getInstance() {
    static Controls instance;
    return instance;
}

bool Controls::isPause() {
    return paused;
}

bool Controls::isQueMode() {
    return queue_mod;
}

void Controls::setPause(bool pause) {
    paused = pause;
}

void Controls::setQueMode(bool mode) {
    queue_mod = mode;
}

int Controls::getTimeLeft() {
    return timeLeft;
}

void Controls::setTimeLeft(int time) {
    timeLeft = time;
}
