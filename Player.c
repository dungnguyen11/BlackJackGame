//
// Created by Sam on 30-Apr-17.
//

#include "Player.h"

struct playerInfo *createPlayer() {
    struct playerInfo *player = malloc(sizeof(struct playerInfo));
    if (player == NULL) {
        return NULL;
    }
    player->totalMoney = 0;
    player->betMoney = 0;
    player->firstCard = 0;
    player->secondCard = 0;
    player->thirdCard = 0;
    player->fourthCard = 0;
    player->fifthCard = 0;
    return player;
}

void freePlayer(struct playerInfo *player) {
    free(player);
}

void askMoneyPlayer(struct playerInfo *player) {
    int money;
    printf("We hope you have a lucky day!\n");
    printf("Before you start, we would like to ask you a question: \n");
    printf("How much money do you want to play today?\n");

    while (scanf("%d", &money) != 1) {
        printf("Please enter your money.\n");
        scanf("%*s");
    }

    player->totalMoney = money;
//    printf("Your total money: $%i\n", getTotalMoney(player));
}

int getTotalMoney(struct playerInfo *player) {
    return player->totalMoney;
}

int askBetMoney(struct playerInfo *player) {
    int money = 0;
    printf("How much do you want to bet?\n");

    while (scanf("%d", &money) != 1) {
        printf("Please enter your money.\n");
        scanf("%*s");
    }

    while (money > getTotalMoney(player)) { //Do not let player bet if the amount of bet is larger than total money
        if (money > getTotalMoney(player)) {
            printf("\nYou do not have enough money!Please pick a smaller bet\n");
            clear();
            scanf("%d", &money);
        }
    }

    player->betMoney = money;
    printf("Your wager: $%d\n", getBetMoney(player));
}

int getBetMoney(struct playerInfo *player) {
    return player->betMoney;
}

void setTotalMoney(int newMoney, struct playerInfo *player) {
    player->totalMoney = newMoney;
}

void setPlayerForNewGame(struct playerInfo *player) {
    player->firstCard = 0;
    player->secondCard = 0;
    player->thirdCard = 0;
    player->fourthCard = 0;
    player->fifthCard = 0;
}

void playerGetFirstCard(struct playerInfo *player, int *deck) {
    int card = getCardAndDisp(deck);
    player->firstCard = card;
}

void playerGetSecondCard(struct playerInfo *player, int *deck) {
    int card = getCardAndDisp(deck);
    player->secondCard = card;
}


void playerGetNextCard(struct playerInfo *player, int *deck, int countCardPlayer) {

    int card = getCardAndDisp(deck); //Get random card, display it and assign it to card variable

    //Check which card it is (third? fourth? or fifth?)
    switch (countCardPlayer) {
        case 3:
            printf("\nPLAYER THIRD CARD: \n");
            player->thirdCard = card;
            break;
        case 4:
            printf("\nPLAYER THIRD CARD: \n");
            player->fourthCard = card;
            break;
        case 5:
            printf("\nPLAYER FIFTH CARD: \n");
            player->fifthCard = card;
            break;
    }
}

void adjustValueOfCardPlayer(struct playerInfo *player) {
    int jack = 12, queen = 13, king = 14;

    //Adjust value of jack, queen and king card to value 10
    //First card
    if (player->firstCard == jack || player->firstCard == queen || player->firstCard == king) {
        player->firstCard = 10;
    }
    //Second card
    if (player->secondCard == jack || player->secondCard == queen || player->secondCard == king) {
        player->secondCard = 10;
    }
    //Third card
    if (player->thirdCard == jack || player->thirdCard == queen || player->thirdCard == king) {
        player->thirdCard = 10;
    }
    //Fourth card
    if (player->fourthCard == jack || player->fourthCard == queen || player->fourthCard == king) {
        player->fourthCard = 10;
    }
    //Fifth card
    if (player->fifthCard == jack || player->fifthCard == queen || player->fifthCard == king) {
        player->fifthCard = 10;
    }
}

int getPointPlayer(struct playerInfo *player) {
    //Have to change value of jack, queen, king to 10 before get total point
    adjustValueOfCardPlayer(player);

    //After change value of jack, queen, and king, get correct total value
    int total = player->firstCard + player->secondCard +
                player->thirdCard + player->fourthCard + player->fifthCard;
    return total;
}

void getPointAndDispPlayer(struct playerInfo *player) {
    int playerTotalPoint = getPointPlayer(player);
    printf("\tTOTAL PLAYER POINT: %d\n", playerTotalPoint); //Get and display player total point
}



int isPlayerBlackJack(struct playerInfo *player) {
    int ace = 11, ten = 10, jack = 12, queen = 13, king = 14;

    //Just need to check the first card of player
    if (player->firstCard == ace) {//If the first card is Ace, check if the second card have value of 10 or not
        if (player->secondCard == ten || player->secondCard == jack ||
            player->secondCard == queen || player->secondCard == king) {
            return 1;
        }
    } else if (player->firstCard == ten || player->firstCard == jack ||
               player->firstCard == queen ||
               player->firstCard == king) { //If the first card have value 10, check if the second is Ace or not
        if (player->secondCard == ace) {
            return 1;
        }
    }
    return 0;
}

int isPlayerBust(struct playerInfo *player) {
    if (getPointPlayer(player) > 21) {
//        printf("\n\tBUST! YOU LOSE!\n\tGood luck next time!");
        return 1;
    }
    return 0;
}

