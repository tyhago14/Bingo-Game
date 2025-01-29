#include "card.h"
#include <iostream>
#include <random>
#include <chrono>
#include <unordered_set>
#include <vector>
#include <algorithm>

using namespace std;

unordered_set<int> card_unorded;

void Card::setCard() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(1, 60);
    card_unorded.clear();
    while (card_unorded.size() < 15) {
        int random_number = dist(rng);
        card_unorded.insert(random_number);
    }
}

void Card::displayCard() {
    card_ordered.assign(card_unorded.begin(), card_unorded.end());
    sort(card_ordered.begin(), card_ordered.end());

    cout << "\n\t\t      CARD" << endl;
    cout << "\t\t|" << card_ordered[0] << " " << card_ordered[3] << " " << card_ordered[6] << " " << card_ordered[9] << " " << card_ordered[12] << "|" << endl;
    cout << "\t\t|" << card_ordered[1] << " " << card_ordered[4] << " " << card_ordered[7] << " " << card_ordered[10] << " " << card_ordered[13] << "|" << endl;
    cout << "\t\t|" << card_ordered[2] << " " << card_ordered[5] << " " << card_ordered[8] << " " << card_ordered[11] << " " << card_ordered[14] << "|" << endl;
    cout << endl;
}

extern "C" {
    Card* createCard() {
        return new Card();
    }

    void destroyCard(Card* card) {
        delete card;
    }

    void setCardWrapper(Card* card) {
        card->setCard();
    }

    void displayCardWrapper(Card* card) {
        card->displayCard();
    }
    vector<int> getCardOrdered(Card* card) {
        return (card->card_ordered);
    }
}
