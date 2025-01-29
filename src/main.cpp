#include <iostream>
#include <random>
#include <chrono>
#include <unordered_set>
#include <vector>
#include <algorithm>
#include "bingo_library/card.h"
#include "bingo_library/player.h"
#include "bingo_library/game.h"

using namespace std;

/* mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
uniform_int_distribution<int> dist(1, 60); */
/*
class Card{
    public:
        //Save Card
        unordered_set<int> card_unorded;// {2, 4, 8, 10, 12, 14, 16, 18, 20, 22, 24, 26, 28, 30, 32} //
        vector<int> card_ordered;
        
        //New Card//
        void setCard(){
             card_unorded.clear();
            while (card_unorded.size() < 15){
                int random_number = dist(rng);
                card_unorded.insert(random_number);
            } 
        }

        //Display Card//
        void displayCard(){
            //Order the values
            card_ordered.assign(card_unorded.begin(), card_unorded.end());
            sort(card_ordered.begin(), card_ordered.end());

            cout << "\n\t\t      CARD" <<endl;
            cout << "\t\t|" << card_ordered[0] << " " << card_ordered[3] << " " << card_ordered[6] << " " << card_ordered[9] << " " << card_ordered[12] << "|" <<endl;
            cout << "\t\t|" << card_ordered[1] << " " << card_ordered[4] << " " << card_ordered[7] << " " << card_ordered[10] << " " << card_ordered[13] << "|" <<endl;
            cout << "\t\t|" << card_ordered[2] << " " << card_ordered[5] << " " << card_ordered[8] << " " << card_ordered[11] << " " << card_ordered[14] << "|" <<endl;
            cout << endl;
        }
};
*/
/*
class Player{
    public:
        int credits = 500;
        void displayCredits(){
            cout << "\tCredits:" << credits <<endl;
        }
        void addCredits(int c){
            credits = credits + c;
        }
        void subCredits(){
            credits = credits - 1;
        }
};
*/
/*
class Game{
    public:
        unordered_set<int> drawballs;
        void start(){
              while (drawballs.size() < 30){
                int random_number = dist(rng);
                drawballs.insert(random_number);
            } 
        }

        void displayBalls(){
            int index = 0;
            cout << endl << "\tDraw balls:" << endl;
            cout << "\t";
            for (const auto& ball : drawballs) {
                cout << ball << " ";
                if(index == 14){
                    cout << endl << "\t";
                }
                index++;
            }
            cout << endl;
        }

        int prizes(vector<int> &card_ordered){
            vector<int> position;
            int hit = 0;
            int result = 0;
            cout << endl << "\tBalls hit: ";
            for (const auto& ball : card_ordered) {
                auto it = drawballs.find(ball);
                if(it != drawballs.end()){
                    cout << ball << " ";
                    position.push_back(ball);
                    hit++;
                }else {
                    position.push_back(0);
                }
            }
            cout <<"{" << hit <<" balls}\n";
            if(hit<9){
                return 0;
            } else {         // First Prize // 
                if(card_ordered[0]==position[0] && card_ordered[3]==position[3] && 
                card_ordered[4]==position[4] && card_ordered[6]==position[6] &&
                card_ordered[7]==position[7] && card_ordered[8]==position[8] && 
                card_ordered[9]==position[9] && card_ordered[10]==position[10] &&
                card_ordered[12]==position[12]){
                    result += 1;
                }}
            if(hit >= 11){  // Second Prize // 
                if(card_ordered[0]==position[0] && card_ordered[2]==position[2] && 
                card_ordered[3]==position[3] && card_ordered[5]==position[5] &&
                card_ordered[7]==position[7] && card_ordered[8]==position[8] && 
                card_ordered[6]==position[6] && card_ordered[9]==position[9] &&
                card_ordered[11]==position[11] && card_ordered[12]==position[12] &&
                card_ordered[14]==position[14]){
                    result += 2;
                }
            }
            return result;
        }
};
*/
void menu2(){
    Card newCard;
    Player newPlayer;
    Game newGame;
    int option2;
    bool extrab = false;
    bool prize1= false;
    bool prize2= false;
    bool prize3= false;
    system("clear"); 
    do{
        cout<<"\t################################"<<endl;
        cout<<"\t#            BINGO             #"<<endl;
        cout<<"\t# 1) Start the game            #"<<endl;
        cout<<"\t# 2) Generate new Bingo card   #"<<endl;
        cout<<"\t# 3) Back                      #"<<endl;               
        cout<<"\t################################"<<endl;
        cout<<endl;
        cout << "\tEnter your option: ";  
        cin>>option2;
        switch (option2){
            case 1: {
                int option3;
                do{
                    if(newCard.card_ordered.empty()){
                        newCard.setCard();
                    }
                    newCard.displayCard();
                    newPlayer.displayCredits();
                    cout << "\t1) Draw 30 Balls ";
                    cout << "\t2) Extra Ball ";
                    cout << "\t3) Exit ";
                    cout << "\n\tEnter your option: ";  
                    cin>>option3;
                    switch (option3){
                        case 1: {
                            system("clear"); 
                            newGame.start();
                            extrab = true;
                            newGame.displayBalls();
                            newPlayer.subCredits();
                            int result = newGame.prizes(newCard.card_ordered);
                            if (result == 0){
                                cout << "\tNo Prizes." << endl;

                            }
                            
                            if(result == 1 && prize1 == false){
                                prize1 = true;
                                cout << "\tFirst Prize!" << endl;
                                cout << "\tAdded 10 Credits!!!" << endl;
                                newPlayer.addCredits(10);
                            }
                            if(result == 2 && prize2 == false){
                                prize2 = true;
                                cout << "\tSecond Prize!!" << endl;
                                cout << "\tAdded 50 Credits!!!" << endl;
                                newPlayer.addCredits(50);

                            }
                            if (result == 3 && prize3 == false){
                                prize3 = true;
                                cout << "\tFirst and Second Prizes!!!" << endl;
                                cout << "\tAdded 60 Credits!!!" << endl;
                                cout << "\n\tCongratulations, the game is over!!!!!!\n" << endl;
                                newPlayer.addCredits(60);
                                prize1 = false;
                                prize2 = false;
                                prize3 = false;
                                extrab = false;
                                option3 = 3; 
                                break;
                            }
                            break; 
                        }
                        case 2: {
                            if(extrab){
                                int extraball = newGame.drawExtraBall();
                                cout << "\n\tExtra Ball -> " << extraball;
                                newGame.displayBalls();
                                newPlayer.subCredits();
                                int result = newGame.prizes(newCard.card_ordered);
                                if (result == 0){
                                    cout << "\tNo Prizes." << endl;
                                }
                                
                                if(result == 1 && prize1 == false){
                                    prize1 = true;
                                    cout << "\tFirst Prize!" << endl;
                                    cout << "\tAdded 10 Credits!!!" << endl;
                                    newPlayer.addCredits(10);
                                }
                                if(result == 2 && prize2 == false){
                                    prize2 = true;
                                    cout << "\tSecond Prize!!" << endl;
                                    cout << "\tAdded 50 Credits!!!" << endl;
                                    newPlayer.addCredits(50);
                                }
                                if (result == 3){
                                    if(prize3 == false && prize2 == false && prize1 == false){
                                        newPlayer.addCredits(60);
                                        cout << "\tFirst and Second Prizes!!!" << endl;
                                        cout << "\tAdded 60 Credits!!!" << endl;
                                    }
                                    if (prize1 == true){
                                        cout << "\tSecond Prize!!" << endl;
                                        cout << "\tAdded 50 Credits!!!" << endl;
                                        newPlayer.addCredits(50);
                                    }
                                    if (prize2 == true){
                                        cout << "\tFirst Prize!!" << endl;
                                        cout << "\tAdded 10 Credits!!!" << endl;
                                        newPlayer.addCredits(10);
                                    }
                                    cout << "\n\tCongratulations, the game is over!!!!!!\n" << endl;
                                    prize1 = false;
                                    prize2 = false;
                                    prize3 = false;
                                    extrab = false;
                                    option3 = 3; 
                                    break;
                                } 
                            }else {
                                cout << "\tYou need to Draw the Balls first!" << endl;
                            }
                            break;
                        }
                        case 3:
                            option3 = 3; 
                            break;
                        default:  
                            cout << "Invalid Input" << endl;
                    }
                }while (option3 != 3);
                break;
            }
            case 2: {
                newCard.setCard();
                newCard.displayCard();
                break;
            }
            default:  
                cout << "Invalid Input" << endl;    
        }
    }while (option2 != 3);
}


int main()
{
    system("clear");
    int option;
    do{
        cout<<"\t################################"<<endl;
        cout<<"\t#            BINGO             #"<<endl;
        cout<<"\t# 1) Play the game             #"<<endl;
        cout<<"\t# 2) Rules                     #"<<endl;
        cout<<"\t# 3) Exit                      #"<<endl;               
        cout<<"\t################################"<<endl;
        cout<<endl;
        cout << "\tEnter your option: ";  
        cin>>option;
        switch (option){
            case 1: {
                menu2();
                break;
            }
            case 2: {
                cout << "Indique o caminho do ficheiro2: "<<endl;
                break;
            }
            default:  
                cout << "Invalid Input" << endl;    
        }
    }while (option != 3);  

    /* mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    uniform_int_distribution<int> dist(1, 60);
    int random_number = dist(rng);
    cout << "Random number between 0 and 60: " << random_number << endl; */
    return 0;
}