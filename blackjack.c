//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"
#include "Player.h"
#include "Player.c"
#include "Dealer.h"
#include "Dealer.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>


//TODO: implement set new deck in here, having error now
void setNewDeck(int *deck) {
    //Set new deck for new game, set all element to 0
    memset(deck, 0, sizeof(deck) * 1);
}

void displayTitle() {
    printf("\n\t\tWELCOME TO BLACKJACK GAME!\n\n");
}

void askMoneyPlayer(struct playerInfo *player) {
    int money;
    printf("We hope you have a lucky day!\n");
    printf("Before you start, we would like to ask you some question: \n");
    printf("How much money do you want to play today?\n");

    while (scanf("%d", &money) != 1) {
        printf("Please enter your money.\n");
        scanf("%*s");
    }

    player->playerMoney = money;
    printf("Your total money: $%i\n", getPlayerMoney(player));
}

void play(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    int countCardPlayer = 3; //Variable is to count if player get third/fourth/fifth card
    int countCardDealer = 3; //Variable is to count if dealer get third/fourth/fifth card

    setPlayerForNewGame(player); //Have to set value of cards to 0 every play
    setDealerForNewGame(dealer); //Have to set value of cards to 0 every play

    initCards(player, dealer, deck); //Get 2 cards of player and 1 card of dealer


    char hitStand = 'h'; //Initialize hitStand to 'h' to run the while loop

    //When player is not blackjack, ask for hit or stand
    if (!isPlayerBlackJack(player)) {
        while (hitStand == 'h' && countCardPlayer <= 5) {
            hitStand = askHitOrStand(player);
            printf("Answer: %c\n", hitStand); //Testing
            //TODO: Implement this
            if (hitStand == 'h') {
                if (countCardPlayer == 3) {
                    printf("\nPLAYER THIRD CARD: \n");
                } else if (countCardPlayer == 4) {
                    printf("\nPLAYER THIRD CARD: \n");
                } else if (countCardPlayer == 5) {
                    printf("\nPLAYER FIFTH CARD: \n");
                }
                playerGetNextCard(player, deck, countCardPlayer);
                countCardPlayer++;
                printf("Player: %d %d %d %d %d\n", player->firstCard, player->secondCard, player->thirdCard, player->fourthCard, player->fifthCard);
                getPointAndDispPlayer(player);
            }

            //Not let player hit another card if he/she busts
            if (getPointPlayer(player) > 21) {
                printf("\n\tPLAYERBUST!\n");
                hitStand = 's';
            }
        }
    }

    //Dealer get second card after player get enough cards
    sleep(1); //sleep to get different random card
    printf("\nDEALER SECOND CARD: \n");
    dealerGetSecondCard(dealer, deck);

    if (isDealerBlackJack(dealer)) { //If dealer get blackjack, display text say so, and find winner directly
        printf("\nBLACKJACK\n");
    } else {
        //Dealer have to hit another card if his total is smaller than 17
        while (getPointDealer(dealer) < 17 && countCardDealer <= 5) {
            if (countCardDealer == 3) {
                printf("\nDEALER THIRD CARD: \n");
            } else if (countCardDealer == 4) {
                printf("\nDEALER THIRD CARD: \n");
            } else if (countCardDealer == 5) {
                printf("\nDEALER FIFTH CARD: \n");
            }
            sleep(1);
            dealerGetNextCard(dealer, deck, countCardDealer);
            countCardDealer++;
        }

        if (getPointDealer(dealer) > 21) { //Display bust if total of dealer is greater than 21
            printf("\n\tDEALER BUST!");
            getPointAndDispDealer(dealer);
        } else {
            getPointAndDispDealer(dealer); //Display total point after hit enough cards, and not bust
        }
    }

    //TODO: Error when print out result, do not process next
    printWinner(player, dealer);

}

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    srand(time(NULL));
    printf("\nOk, let get started! Good luck!\n\n");

    //Get 2 cards of player
    sleep(1); //sleep to get different random card
    printf("PLAYER FIRST CARD: \n");
    playerGetFirstCard(player, deck); //Player get first card
    sleep(1);//sleep to get different random card
    printf("PLAYER SECOND CARD: \n");
    playerGetSecondCard(player, deck); //Player get second card

    //Check if player got Blackjack, check before change value in getPointPlayer
    if (isPlayerBlackJack(player)) {
        printf("\nBLACKJACK!\n\n");
    } else {
        getPointAndDispPlayer(player); //Get and display player total point
    }

    //Get first card of dealer
    sleep(1);  //sleep to get different random card
    printf("DEALER FIRST CARD: \n");
    dealerGetFirstCard(dealer, deck); //Dealer get first card
    int dealerTotalPoint = getPointDealer(dealer);
    getPointAndDispDealer(dealer);
}


void displayCard(int card) {

    //Card from 2 to 10
    if (card <= 9) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|     |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    } else if (card == 10) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|      |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    } else if (card == 11) { //Ace Card
        printf("-------\n");
        printf("|%c    |\n", 'A');
        printf("|     |\n");
        printf("|    %c|\n", 'A');
        printf("-------\n");
    } else if (card == 12) { //Jack Card
        printf("--------\n");
        printf("|%c    |\n", 'J');
        printf("|     |\n");
        printf("|    %c|\n", 'J');
        printf("--------\n");
    } else if (card == 13) { //Queen Card
        printf("-------\n");
        printf("|%c    |\n", 'Q');
        printf("|     |\n");
        printf("|    %c|\n", 'Q');
        printf("-------\n");
    } else if (card == 14) { //King Card
        printf("-------\n");
        printf("|%c    |\n", 'K');
        printf("|     |\n");
        printf("|    %c|\n", 'K');
        printf("-------\n");
    }
}

int checkCardIfAvailable(int card, int *deck) {
    if (deck[card] >= 4) {
        return 0;
    }
    return 1;
}

int getCard(int *deck) {
    int card = 0;
    while (checkCardIfAvailable(card, deck)) {
        srand(time(NULL));
        card = (int) (rand() % 13 + 2); //Get random card value from 2 to 14
        if (checkCardIfAvailable(card, deck) && card != 0) { //Check if the card is available or not
            deck[card]++;
            break;
        }
        card = 0;
    }
    return card;
}

int getCardAndDisp(int *deck) {
    int card = getCard(deck);
    displayCard(card);
    return card;
}

char askHitOrStand(struct playerInfo *player) {
    char answer;
    int check = 1;
    while (check) {
        if (answer != '\n') { //Do not need to ask for hit or stand for blackjack cards
            printf("Do you want to hit(h) or stand(s)?\n");
            scanf("%s", &answer);
            if (answer == 'h' || answer == 's') {
                return answer;
            } else {
                printf("Please choose 'h' for Hit or 's' for Stand\n");
            }
        }
        check = 1;
    }
}

//TODO:this function is incorrectly, fix it
int isPlayerWin(struct playerInfo *player, struct dealerInfo *dealer) {
    if (((getPointPlayer(player) > getPointDealer(dealer)) && isPlayerBust(player) == 0) || //Player is higher than Dealer
        ((isPlayerBust(player) == 0) && (isDealerBust(dealer) == 1)) || //Dealer busts
        ((isPlayerBlackJack(player) == 1) && (isDealerBlackJack(dealer) == 0))) { //Player get blackjack

        return 1; //For win

    } else if (((getPointPlayer(player) < getPointDealer(dealer)) && isDealerBust(dealer) == 0) || //Player is lower than Dealer
               ((isPlayerBust(player) == 1) && (isDealerBust(dealer) == 0)) || //Player busts
               (isPlayerBlackJack(player) == 0 && (isDealerBlackJack(dealer) == 1))) { //Dealer get blackjack

        return 0; //For lose

    } else if ((getPointPlayer(player) == getPointDealer(dealer)) || //Player is equal to Dealer
               ((isPlayerBust(player) == 1) && (isDealerBust(dealer) == 1)) || //Both player and dealer bust
               ((isPlayerBlackJack(player) == 1) && (isDealerBlackJack(dealer) == 1))) { //Both player and dealer get blackjack

        return 2; //For Push

    } else {
        printf("This is exception. Fix this!");
    }
    return 3; //exception
}

void printWinner(struct playerInfo *player, struct dealerInfo *dealer) {
    //TODO: add blackjack case in here
    if (isPlayerWin(player, dealer) == 1) { //Player win
        printf("\n\tYOU WIN!\n Your wager is doubled!\n");
    } else if (isPlayerWin(player, dealer) == 0) { //Player lose
        printf("\n\tYOU LOSE!\n You lose your wager. Good luck next time!\n");
    } else if (isPlayerWin(player, dealer) == 2) { //Push
        printf("\n\tPUSH! NO WINNER.\n You will get your wager back.\n");
    } else {
        printf("This is exception. Fix this!");
    }
}

char askPlayAgain() {
    char answer;
    int playAgain = 1;
    while (playAgain) {
        if (answer != '\n') { //omit when player type answer + Enter, because it also count '\n'
            continue;
        }

        printf("Do you want to play again?(y/n)\n");
        scanf("%c", &answer);

        if (answer == 'y') {
            break; //Continue playing, break out the while loop
        } else if (answer == 'n') {
            printf("\tTHANKS FOR PLAYING!\n\tHAVE A GOOD DAY!\n");
            playAgain = 0; //Change playAgain value to end while loop
        }
    }
    return answer;
}

