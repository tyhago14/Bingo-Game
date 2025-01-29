#include "player.h"
#include <iostream>

using namespace std;

void Player::displayCredits() {
    cout << "\tCredits:" << credits <<endl;
}

void Player::addCredits(int c) {
    credits = credits + c;
}

void Player::subCredits() {
    credits = credits - 1;
}

extern "C" {
    Player* createPlayer() {
        return new Player();
    }

    void destroyPlayer(Player* player) {
        delete player;
    }

    void addCreditsWrapper(Player* player, int c) {
        player->addCredits(c);
    }

    void displayCreditsWrapper(Player* player) {
        player->displayCredits();
    }

    void subCreditsWrapper(Player* player) {
        player->subCredits();
    }
}