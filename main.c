#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include "blackjack.h"
#include "blackjack.c"
#include "Player.h"
//#include "Player.c"
#include "Dealer.h"
//#include "Dealer.c"

int main() {
    //Create deck pointer
    int deck[15] = {0}; //52 cards is store in an array to check every time the player or dealer get a card

    //Create player and dealer for new game
    struct playerInfo *player1 = createPlayer();
    struct dealerInfo *dealer1 = createDealer();

    displayTitle(); //Display title
    askMoneyPlayer(player1); //Get player money

    //TODO: Check if function of player and dealer is correctly split
    char playAgain = 'y';

    while (playAgain == 'y') {
        srand(time(NULL));
        memset(deck, 0, sizeof(deck)); //Set all value in deck to 0s for new play

        setPlayerForNewGame(player1); //Have to set value of cards to 0 every play
        setDealerForNewGame(dealer1); //Have to set value of cards to 0 every play

        printf("\n\tPLAYER TOTAL MONEY: $%d\n", getTotalMoney(player1));

        askBetMoney(player1); //Ask player for the amount of bet money

        play(player1, dealer1, deck);

        //Testing
//        printf("Player: %d %d\n", player1->firstCard, player1->secondCard);
//        printf("Dealer: %d %d\n", dealer1->firstCard, dealer1->secondCard);
//        int length = sizeof(deck) / sizeof(int);
//        for (int i = 0; i < length; ++i) {
//            printf("Array %d : %d\n", i, deck[i]);
//        }

        //Ask player if he/she want to play more
        playAgain = askPlayAgain(player1); //askPlayAgain function returns char 'y' or 'n'
    }

        //Testing
//    struct playerInfo *player = createPlayer();
//    player->firstCard = 5;
//    player->secondCard = 10;
//    player->thirdCard = 7;
//
//    printf("\nBust Player: %d\n", isPlayerBust(player));
//
//    struct dealerInfo *dealer = createDealer();
//    dealer->firstCard = 10;
//    dealer->secondCard = 5;
//    dealer->thirdCard = 7;
//
//    printf("\nBust dealer: %d\n", isDealerBust(dealer));
//
//    printWinner(player, dealer);





}