//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"
#include "Player.h"
#include "Player.c"
#include "Dealer.h"
#include "Dealer.c"
#include <stdbool.h>


//TODO: implement set new deck in here, having error now
void setNewDeck(int *deck) {
    printf("in set");
//    int length = sizeof(deck)/ sizeof(int);
//    for (int i = 0; i < length; ++i) {
//       deck[i] = 0;
//    }
    memset(deck, 0, sizeof(deck));
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
    initCards(player, dealer, deck);
}

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    srand(time(NULL));
    printf("\nOk, let get started! Good luck!\n");

    //Get 2 cards of player
    printf("PLAYER FIRST CARD: \n");
    playerGetFirstCard(player, deck); //Player get first card
    sleep(1);
    printf("PLAYER SECOND CARD: \n");
    playerGetSecondCard(player, deck); //Player get second card

    //Check if player got Blackjack, check before change value in getPointPlayer
    if (isPlayerBlackJack(player)) {
        printf("\nBLACKJACK!\n");
    } else {
        int playerTotalPoint = getPointPlayer(player);
        printf("TOTAL PLAYER POINT: %d\n\n", playerTotalPoint); //Get and display player total point
    }

    //Get first card of dealer
    sleep(1);
    printf("DEALER FIRST CARD: \n");
    dealerGetFirstCard(dealer, deck); //Dealer get first card
//    sleep(1);
//    printf("DEALER SECOND CARD: \n");
//    dealerGetSecondCard(dealer, deck); //Dealer get second card
//    int dealerTotalPoint = getPointDealer(dealer);
//    printf("TOTAL DEALER POINT: %d\n\n", dealerTotalPoint); //Get and display dealer total point
}


void displayCard(int card) {
    //Card from 2 to 10
    if (card <= 9) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|     |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    }
    if (card == 10) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|      |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    }

    //Ace Card
    if (card == 11) {
        printf("-------\n");
        printf("|%c    |\n", 'A');
        printf("|     |\n");
        printf("|    %c|\n", 'A');
        printf("-------\n");
    }

    //Jack Card
    if (card == 12) {
        printf("--------\n");
        printf("|%c    |\n", 'J');
        printf("|     |\n");
        printf("|    %c|\n", 'J');
        printf("--------\n");
    }

    //Queen Card
    if (card == 13) {
        printf("-------\n");
        printf("|%c    |\n", 'Q');
        printf("|     |\n");
        printf("|    %c|\n", 'Q');
        printf("-------\n");
    }

    //King Card
    if (card == 14) {
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
        card = (rand() % 13 + 2); //Get random card value from 2 to 14
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

char askPlayAgain() {
    char answer;
    int playAgain = 1;
    while (playAgain) {
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

//TODO: work incorrectly, maybe the same error as adjustValue function


void findWinner(struct playerInfo *player, struct dealerInfo *dealer) {
    //TODO: add blackjack case in here
    if (getPointPlayer(player) > getPointDealer(dealer)) { //Player is higher than Dealer
        printf("\n\tYOU WIN!\n");
    } else if (getPointPlayer(player) < getPointDealer(dealer)) { //Player is lower than Dealer
        printf("\n\tYOU LOSE!\n Good luck next time!\n");
    } else if (getPointPlayer(player) == getPointDealer(dealer)) { //Player is equal to Dealer
        printf("\n\tPUSH! NO WINNER.\n You will get your wager back.\n");
    } else if (isPlayerBust(player) && !isDealerBust(dealer)) { //Player busts
        printf("\n\tYOU LOSE!\n Good luck next time!\n");
    } else if (!isPlayerBust(player) && isDealerBust(dealer)) { //Dealer busts
        printf("\n\tYOU WIN!\n");
    } else if (isPlayerBust(player) && isDealerBust(dealer)) { //Player and dealer bust
        printf("\n\tPUSH! NO WINNER.\n You will get your wager back.\n");
    }
}

