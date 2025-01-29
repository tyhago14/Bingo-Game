#ifndef GAME_H
#define GAME_H

#include <unordered_set>
#include <vector>

using namespace std;

class Game {
public:
    unordered_set<int> drawballs;
    void start();
    void displayBalls();
    int prizes(vector<int>& card_ordered);
    int drawExtraBall();
};

extern "C" {
    Game* createGame();
    void destroyGame(Game* game);
    void startGameWrapper(Game* game);
    void displayGameWrapper(Game* game);
    int prizesWrapper(Game* game, vector<int> card_ordered);
    int drawExtraBallWrapper(Game* game);
}

#endif 