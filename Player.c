//
// Created by Sam on 30-Apr-17.
//

#include "Player.h"

struct playerInfo *createPlayer() {
    struct playerInfo *player = malloc(sizeof(struct playerInfo));
    if (player == NULL) {
        return NULL;
    }
    player->playerMoney = 0;
    player->firstCard = 0;
    player->secondCard = 0;
    player->thirdCard = 0;
    player->fourthCard = 0;
    player->fifthCard = 0;
}

void freePlayer(struct playerInfo *player) {
    free(player);
}


void playerGetFirstCard(struct playerInfo *player, int *deck) {
    int card = getCardAndDisp(deck);
    player->firstCard = card;
}

void playerGetSecondCard(struct playerInfo *player, int *deck) {
    int card = getCardAndDisp(deck);
    player->secondCard = card;
}

int countCard = 3;

void playerGetNextCard(struct playerInfo *player, int *deck) {

    int card = getCardAndDisp(deck);
    switch (countCard) {
        case 3:
            player->thirdCard = card;
            countCard++;
            break;
        case 4:
            player->fourthCard = card;
            countCard++;
            break;
        case 5:
            player->fifthCard = card;
            countCard++;
            break;
    }
}

void adjustValueOfCardPlayer(struct playerInfo *player) {
    int jack = 12, queen = 13, king = 14;

    //Adjust value of jack, queen and king card to value 10
    if (player->firstCard == jack || player->firstCard == queen || player->firstCard == king) { //First card
        player->firstCard = 10;
    } else if (player->secondCard == jack || player->secondCard == queen || player->secondCard == king) { //Second card
        player->secondCard = 10;
    } else if (player->thirdCard == jack || player->thirdCard == queen || player->thirdCard == king) { //Third card
        player->thirdCard = 10;
    } else if (player->fourthCard == jack || player->fourthCard == queen || player->fourthCard == king) { //Fourth card
        player->fourthCard = 10;
    } else if (player->fifthCard == jack || player->fifthCard == queen || player->fifthCard == king) { //Fifth card
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
    printf("TOTAL PLAYER POINT: %d\n\n", playerTotalPoint); //Get and display player total point
}

int getPlayerMoney(struct playerInfo *player) {
    return player->playerMoney;
}

void setPlayerMoney(int newMoney, struct playerInfo *player) {
    player->playerMoney = newMoney;
}

int isPlayerBlackJack(struct playerInfo *player) {
    int ace = 11, ten = 10, jack = 12, queen = 13, king = 14;

    //Just need to check the first card of player
    if (player->firstCard == ace) {//If the first card is Ace, check if the second card have value of 10 or not
        if (player->secondCard == ten || player->secondCard == jack ||
            player->secondCard == queen || player->secondCard == king) {
//            printf("\nBLACKJACK!\n");
            return 1;
        }
    } else if (player->firstCard == ten || player->firstCard == jack ||
               player->firstCard == queen ||
               player->firstCard == king) { //If the first card have value 10, check if the second is Ace or not
        if (player->secondCard == ace) {
//            printf("\nBLACKJACK!\n");
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

