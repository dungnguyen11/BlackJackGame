#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <memory.h>
#include <ctype.h>
#include "blackjack.h"
//#include "blackjack.c"
#include "Hand.h"
//#include "Hand.c"

int main() {
    //Create deck pointer
    int deck[15] = {0}; //52 cards is store in an array to check every time the player or dealer get a card

    //Create player and dealer for new game
    struct handInfo *player1 = createHand();
    struct handInfo *dealer1 = createHand();

    displayTitle(); //Display title
    askMoney(player1); //Get player money
    printf("\n\tPLAYER TOTAL MONEY: $%d\n\n", getTotalMoney(player1));
    //Loop for menu
    while (1) {
        int menuChoice = 0;
        menuChoice = displayAskMenu();

        if (menuChoice == 1) {
            char playAgain = 'y';
            if (getTotalMoney(player1) == 0) {
                printf("You do not have enough money to play. Please come back later.\n\n");
            } else {
                //Loop for playing
                while ((tolower(playAgain) == 'y') && getTotalMoney(player1) != 0) {
                    srand(time(NULL));

                    setHandForNewGame(player1); //Have to set value of cards to 0 every play
                    setHandForNewGame(dealer1); //Have to set value of cards to 0 every play

                    printf("\n\tPLAYER TOTAL MONEY: $%d\n", getTotalMoney(player1));

                    askBetMoney(player1); //Ask player for the amount of bet money

                    play(player1, dealer1, deck);

                    //Ask player if he/she want to play more
                    if (getTotalMoney(player1) == 0) { //Check if player have enough money to continue playing
                        printf("You do not have enough money to continue playing.\n\n");
                        playAgain = 'n';
                    } else {
                        playAgain = askPlayAgain(player1); //askPlayAgain function returns char 'y' or 'n'
                    }
                }
            }
        } else if (menuChoice == 2) {
            displayRules();
        } else if (menuChoice == 3) {
            displayCredits();
        } else {
            break;
        }
    }

    //Free allocated memory
    freeHand(player1);
    freeHand(dealer1);

    printf("\n\tTHANK YOU! WE HOPE TO SEE YOU SOON!\n\t\tHAVE A GOOD DAY!\n");
}