#include "game.h"
#include <iostream>
#include <random>
#include <chrono>

using namespace std;

void Game::start() {
    uniform_int_distribution<int> dist(1, 60);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    drawballs.clear();
    while (drawballs.size() < 30) {
        int random_number = dist(rng);
        drawballs.insert(random_number);
    }
}

void Game::displayBalls() {
    int index = 0;
    cout << endl << "\tDraw balls:" << endl;
    cout << "\t";
    for (const auto& ball : drawballs) {
        cout << ball << " ";
        if (index == 14 || index == 29 || index == 43) {
            cout << endl << "\t";
        }
        index++;
    }
    cout << endl;
}

int Game::prizes(vector<int>& card_ordered) {
    vector<int> position;
    int hit = 0;
    int result = 0;
    cout << endl << "\tBalls hit: ";
    for (const auto& ball : card_ordered) {
        auto it = drawballs.find(ball);
        if (it != drawballs.end()) {
            cout << ball << " ";
            position.push_back(ball);
            hit++;
        } else {
            position.push_back(0);
        }
    }
    cout << "{" << hit << " balls}\n";

    if (hit < 9) {
        return 0;
    } else { // First Prize
        if (card_ordered[0] == position[0] && card_ordered[3] == position[3] &&
            card_ordered[4] == position[4] && card_ordered[6] == position[6] &&
            card_ordered[7] == position[7] && card_ordered[8] == position[8] &&
            card_ordered[9] == position[9] && card_ordered[10] == position[10] &&
            card_ordered[12] == position[12]) {
            result += 1;
        }
    }
    if (hit >= 11) {  // Second Prize
        if (card_ordered[0] == position[0] && card_ordered[2] == position[2] &&
            card_ordered[3] == position[3] && card_ordered[5] == position[5] &&
            card_ordered[7] == position[7] && card_ordered[8] == position[8] &&
            card_ordered[6] == position[6] && card_ordered[9] == position[9] &&
            card_ordered[11] == position[11] && card_ordered[12] == position[12] &&
            card_ordered[14] == position[14]) {
            result += 2;
        }
    }
    return result;
}

int Game::drawExtraBall() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(1, 60);
    int random_number;
    bool inserted = false;

    // Keep generating until a unique number is inserted
    while (!inserted) {
        random_number = dist(rng);
        inserted = drawballs.insert(random_number).second;
    }
    return random_number;
}


extern "C" {
    Game* createGame() {
        return new Game();
    }

    void destroyGame(Game* game) {
        delete game;
    }

    void startGameWrapper(Game* game) {
        game->start();
    }

    void displayGameWrapper(Game* game) {
        game->displayBalls();
    }

    int prizesWrapper(Game* game, vector<int> card_ordered) {
        return game->prizes(card_ordered);
    }

    int drawExtraBallWrapper(Game* game){
        return game->drawExtraBall();
    }
}