#ifndef CARD_H
#define CARD_H

#include <vector>

using namespace std;

class Card{
    public:
        vector<int> card_ordered;
        void setCard();
        void displayCard();
};

extern "C" {
    Card* createCard();
    void destroyCard(Card* card);
    void setCardWrapper(Card* card);
    void displayCardWrapper(Card* card);
    vector<int> getCardOrdered(Card* card);
}

#endif 