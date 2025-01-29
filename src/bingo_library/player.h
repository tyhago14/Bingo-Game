#ifndef PLAYER_H
#define PLAYER_H

using namespace std;

class Player{
    public:
        int credits = 500;
        void displayCredits();
        void addCredits(int c);
        void subCredits();
};

extern "C" {
    Player* createPlayer();
    void destroyPlayer(Player* player);
    void displayCreditsWrapper(Player* player);
    void addCreditsWrapper(Player* player, int c);
    void subCreditsWrapper(Player* player);
}

#endif 