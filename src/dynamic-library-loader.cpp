#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>
#include <iostream>
#include <vector>

using namespace std;

// Function pointer types
typedef void* CardHandle;
typedef void* GameHandle;
typedef void* PlayerHandle;

// Declare function pointers for dynamic loading
void* (*fptr_createCard)();
void (*fptr_destroyCard)(CardHandle);
void (*fptr_setCard)(CardHandle);
void (*fptr_displayCard)(CardHandle);
vector<int> (*fptr_getCardOrdered)(CardHandle);

void* (*fptr_createGame)();
void (*fptr_destroyGame)(GameHandle);
void (*fptr_startGame)(GameHandle);
void (*fptr_displayGame)(GameHandle);
int (*fptr_prizesGame)(GameHandle,vector<int>);
int (*fptr_extraballGame)(GameHandle);

void* (*fptr_createPlayer)();
void (*fptr_destroyPlayer)(PlayerHandle);
void (*fptr_displayCredits)(PlayerHandle);
void (*fptr_addCredits)(PlayerHandle,int);
void (*fptr_subCredits)(PlayerHandle);


void menu2(CardHandle card, GameHandle game, PlayerHandle player){
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
                system("clear");
                int option3;
                do{
                    vector<int> validCard = fptr_getCardOrdered(card);
                    if(validCard.empty()){
                        fptr_setCard(card);
                    }
                    
                    fptr_displayCard(card);
                    fptr_displayCredits(player);
                    cout << "\t1) Draw 30 Balls ";
                    cout << "\t2) Extra Ball ";
                    cout << "\t3) Exit ";
                    cout << "\n\tEnter your option: ";  
                    cin>>option3;
                    switch (option3){
                        case 1: {
                            system("clear");
                            extrab = true; 
                            fptr_startGame(game);
                            fptr_displayGame(game);
                            fptr_subCredits(player);
                            vector<int> card_ordered = fptr_getCardOrdered(card);
                            int result = fptr_prizesGame(game,card_ordered);
//NO prizes in the first 30 balls  
                            if (result == 0){
                                cout << "\tNo Prizes." << endl;
                            }
//First Prize in the first 30 balls                           
                            if(result == 1 && prize1 == false){
                                prize1 = true;
                                cout << "\tFirst Prize!" << endl;
                                cout << "\tAdded 10 Credits!!!" << endl;
                                fptr_addCredits(player,10);
                            }
//Second Prize in the first 30 balls  
                            if(result == 2 && prize2 == false){
                                prize2 = true;
                                cout << "\tSecond Prize!!" << endl;
                                cout << "\tAdded 50 Credits!!!" << endl;
                                fptr_addCredits(player,50);
                            }
//Both Prizes in the first 30 balls, game end
                            if (result == 3 && prize3 == false){
                                prize3 = true;
                                cout << "\tFirst and Second Prizes!!!" << endl;
                                cout << "\tAdded 60 Credits!!!" << endl;
                                cout << "\n\tCongratulations, the game is over!!!!!!\n" << endl;
                                fptr_addCredits(player,60);
                                fptr_displayCard(card);
                                prize1 = false;
                                prize2 = false;
                                prize3 = false;
                                extrab = false;
                                option3 = 3; 
                            }
                            break; 
                        }
                        case 2: {
                            if(extrab){
                                system("clear");
                                int extraball = fptr_extraballGame(game);
                                cout << "\n\tExtra Ball -> " << extraball;
                                fptr_displayGame(game);
                                fptr_subCredits(player);
                                vector<int> card_ordered = fptr_getCardOrdered(card);
                                int result = fptr_prizesGame(game,card_ordered);
//NO prizes extra ball                       
                                if (result == 0){
                                    cout << "\tNo Prizes." << endl;
                                }
//First Prize extra ball                                 
                                if(result == 1 && prize1 == false){
                                    prize1 = true;
                                    cout << "\tFirst Prize!" << endl;
                                    cout << "\tAdded 10 Credits!!!" << endl;
                                    fptr_addCredits(player,10);
                                }
//Second Prize extra ball
                                if(result == 2 && prize2 == false){
                                    prize2 = true;
                                    cout << "\tSecond Prize!!" << endl;
                                    cout << "\tAdded 50 Credits!!!" << endl;
                                    fptr_addCredits(player,50);
                                }
//Both Prizes extra ball, game end
                                if (result == 3){
                                    if(prize3 == false && prize2 == false && prize1 == false){
                                        cout << "\tFirst and Second Prizes!!!" << endl;
                                        cout << "\tAdded 60 Credits!!!" << endl;
                                        fptr_addCredits(player,60);
                                    }
                                    if (prize1 == true){
                                        cout << "\tSecond Prize!!" << endl;
                                        cout << "\tAdded 50 Credits!!!" << endl;
                                        fptr_addCredits(player,50);
                                    }
                                    if (prize2 == true){
                                        cout << "\tFirst Prize!!" << endl;
                                        cout << "\tAdded 10 Credits!!!" << endl;
                                        fptr_addCredits(player,10);
                                    }
                                    cout << "\n\tCongratulations, the game is over!!!!!!\n" << endl;
                                    fptr_displayCard(card);
                                    prize1 = false;
                                    prize2 = false;
                                    prize3 = false;
                                    extrab = false;
                                    option3 = 3; 
                                    break;
                                } 
                            }else {
                                system("clear");
                                cout << "\tYou need to Draw the Balls first!" << endl;
                            }
                            break;
                        }
                        case 3:
                            prize1 = false;
                            prize2 = false;
                            prize3 = false;
                            extrab = false;
                            option3 = 3; 
                            break;
                        default:  
                            cout << "Invalid Input" << endl;
                    }
                }while (option3 != 3);
                break;
            }
            case 2: {
                system("clear");
                fptr_setCard(card);
                fptr_displayCard(card);
                break;
            }
            default:  
                cout << "Invalid Input" << endl;    
        }
    }while (option2 != 3);
}


void* getFunctionPointer(void* lib, const char* funcName) {
 //
 // Get the function pointer to the function
    void* fptr = dlsym(lib, funcName);
    if (!fptr) {
      fprintf(stderr, "Could not get function pointer for %s\n  error is: %s\n\n", funcName, dlerror());
      return NULL;
    }
    return fptr;
}




int main(int argc, char* argv[]) {

// Open the dynamic library
    void* lib = dlopen("./bin/shared/libbingo_library.so",  RTLD_LAZY | RTLD_GLOBAL);

    if (!lib) {
// Apparently, the library could not be opened
        fprintf(stderr, "Could not open libbingo_library.so\n");
        exit(1);
    }

 // Call the function via the function pointer
    fptr_createCard = (void* (*)())getFunctionPointer(lib, "createCard");
    fptr_destroyCard = (void (*)(CardHandle))getFunctionPointer(lib, "destroyCard");
    fptr_setCard = (void (*)(CardHandle))getFunctionPointer(lib, "setCardWrapper");
    fptr_displayCard = (void (*)(CardHandle))getFunctionPointer(lib, "displayCardWrapper");
    fptr_getCardOrdered = (vector<int> (*)(CardHandle)) getFunctionPointer(lib, "getCardOrdered");


    fptr_createGame = (void* (*)())getFunctionPointer(lib, "createGame");
    fptr_destroyGame = (void (*)(GameHandle))getFunctionPointer(lib, "destroyGame");
    fptr_startGame = (void (*)(GameHandle))getFunctionPointer(lib, "startGameWrapper");
    fptr_displayGame = (void (*)(GameHandle))getFunctionPointer(lib, "displayGameWrapper");
    fptr_prizesGame = (int (*)(GameHandle,vector<int>))getFunctionPointer(lib, "prizesWrapper");
    fptr_extraballGame = (int (*)(GameHandle))getFunctionPointer(lib, "drawExtraBallWrapper");

    fptr_createPlayer = (void* (*)())getFunctionPointer(lib, "createCard");
    fptr_destroyPlayer = (void (*)(PlayerHandle))getFunctionPointer(lib, "destroyPlayer");
    fptr_displayCredits = (void (*)(PlayerHandle))getFunctionPointer(lib, "displayCreditsWrapper");
    fptr_addCredits = (void (*)(PlayerHandle,int))getFunctionPointer(lib, "addCreditsWrapper");
    fptr_subCredits = (void (*)(PlayerHandle))getFunctionPointer(lib, "subCreditsWrapper");

//Check if Objects exist
    CardHandle card = fptr_createCard();
    if (!card) {
        fprintf(stderr, "Failed to create Card instance.\n");
        exit(1);
    }
    GameHandle game = fptr_createGame();
    if (!game) {
        fprintf(stderr, "Failed to create Game instance.\n");
        exit(1);
    }
    PlayerHandle player = fptr_createPlayer();
    if (!player) {
        fprintf(stderr, "Failed to create Player instance.\n");
        exit(1);
    }


//Start the Game
    system("clear");
    int option;
    fptr_addCredits(player, 500);
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
                menu2(card,game,player);
                break;
            }
            case 2: {
                system("clear");
                cout << "\t################################" << endl;
                cout << "\t#           BINGO GAME         #" << endl;
                cout << "\t################################" << endl;
                cout << "\nRULES OF THE GAME:\n" << endl;

                cout << "1. Ball Universe: Numbers in the balls can only be in the interval 1 to 60." << endl;
                cout << "2. Card Universe: Numbers in the cards can only be in the interval 1 to 60." << endl;
                cout << "3. Draw Balls: Each draw consists of 30 balls. Not all balls are drawn in each game." << endl;
                cout << "4. Extra Balls: Additional balls can be bought in a game." << endl;
                cout << "5. Cards: Each player can have a maximum of 1 card." << endl;
                cout << "6. Card Size: Each card consists of 3 rows and 5 columns (3 x 5)." << endl;
                cout << "7. Pattern of Prizes: Specific patterns on the card grant prizes." << endl;
                cout << "8. Prize (in credits): If your card has a prize pattern, you can win between 10 to 50 credits." << endl;
                cout << "9. Credits: Each game costs 1 credit to play." << endl;
                cout << "\nGood luck and enjoy the game!" << endl;
                break;
            }
            default:  
                cout << "Invalid Input" << endl;    
        }
    }while (option != 3);  
//End the Game

// Clean up
    fptr_destroyCard(card);
    fptr_destroyGame(game);
    fptr_destroyPlayer(player);

// Close the library
    dlclose(lib);
    return 0;
}