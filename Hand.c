//
// Created by Sam on 30-Apr-17.
//

#include "Hand.h"

struct handInfo *createHand() {
    struct handInfo *hand = malloc(sizeof(struct handInfo));
    if (hand == NULL) {
        return NULL;
    }
    hand->totalMoney = 0;
    hand->betMoney = 0;
    hand->firstCard = 0;
    hand->secondCard = 0;
    hand->thirdCard = 0;
    hand->fourthCard = 0;
    hand->fifthCard = 0;
    return hand;
}

void freeHand(struct handInfo *hand) {
    free(hand);
}

//For player only

void askMoney(struct handInfo *player) {
    int money;
    printf("We hope you have a lucky day!\n");
    printf("Before you start, we would like to ask you a question: \n");
    printf("How much money do you want to play today?\n");

    while (scanf("%d", &money) != 1) {
        printf("Your money is invalid!\nPlease enter your money.\n");
//        scanf("%*s");
    }

    while (money < 0) {
        printf("Your money is invalid!\nPlease enter correct money.\n");
        clear();
        scanf("%d", &money);
    }

    player->totalMoney = money;
}

int getTotalMoney(struct handInfo *player) {
    return player->totalMoney;
}

void setTotalMoney(int newMoney, struct handInfo *player) {
    player->totalMoney = newMoney;
}

void askBetMoney(struct handInfo *player) {
    int money = 0;
    printf("How much do you want to bet?\n");

    while (scanf("%d", &money) != 1) {
        clear();
        printf("Your bet is invalid!\nPlease enter your money.\n");
        scanf("%d", &money);
    }

    while (money < 0) {
        printf("Your bet is invalid!\nPlease enter correct money.\n");
        clear();
        scanf("%d", &money);
    }

    while (money > getTotalMoney(player)) { //Do not let player bet if the amount of bet is larger than total money
//        if (money > getTotalMoney(player)) {
            printf("\nYou do not have enough money! Please pick a smaller bet.\n");
            clear();
            scanf("%d", &money);
//        }
    }

    player->betMoney = money;
    printf("Your wager: $%d\n", getBetMoney(player));
}

int getBetMoney(struct handInfo *player) {
    return player->betMoney;
}

//For both player and dealer

void setHandForNewGame(struct handInfo *hand) {
    hand->firstCard = 0;
    hand->secondCard = 0;
    hand->thirdCard = 0;
    hand->fourthCard = 0;
    hand->fifthCard = 0;
}


void getFirstCard(struct handInfo *hand, int *deck) {
    int card = getCard(deck);
    hand->firstCard = card;
}

void getSecondCard(struct handInfo *hand, int *deck) {
    int card = getCard(deck);
    hand->secondCard = card;
}


void getNextCard(struct handInfo *hand, int *deck, int countCard) {
    int card = getCard(deck); //Get random card, display it and assign it to card variable

    //Check which card it is (third? fourth? or fifth?)
    switch (countCard) {
        case 3:
            hand->thirdCard = card;
            break;
        case 4:
            hand->fourthCard = card;
            break;
        case 5:
            hand->fifthCard = card;
            break;
    }
}

void adjustValueOfCard(struct handInfo *hand) {
    int jack = 12, queen = 13, king = 14;

    //Adjust value of jack, queen and king card to value 10
    //First card
    if (hand->firstCard == jack || hand->firstCard == queen || hand->firstCard == king) {
        hand->firstCard = 10;
    }
    //Second card
    if (hand->secondCard == jack || hand->secondCard == queen || hand->secondCard == king) {
        hand->secondCard = 10;
    }
    //Third card
    if (hand->thirdCard == jack || hand->thirdCard == queen || hand->thirdCard == king) {
        hand->thirdCard = 10;
    }
    //Fourth card
    if (hand->fourthCard == jack || hand->fourthCard == queen || hand->fourthCard == king) {
        hand->fourthCard = 10;
    }
    //Fifth card
    if (hand->fifthCard == jack || hand->fifthCard == queen || hand->fifthCard == king) {
        hand->fifthCard = 10;
    }
}

int getPoint(struct handInfo *hand) {
    //Have to change value of jack, queen, king to 10 before get total point
    adjustValueOfCard(hand);

    //After change value of jack, queen, and king, get correct total value
    int total = hand->firstCard + hand->secondCard +
                hand->thirdCard + hand->fourthCard + hand->fifthCard;
    return total;
}
//
//void getPointAndDispPlayer(struct handInfo *player) {
//    int playerTotalPoint = getPointPlayer(player);
//    printf("\tTOTAL PLAYER POINT: %d\n", playerTotalPoint); //Get and display player total point
//}



int isBlackJack(struct handInfo *hand) {
    int ace = 11, ten = 10, jack = 12, queen = 13, king = 14;

    //Just need to check the first card of player
    if (hand->firstCard == ace) {//If the first card is Ace, check if the second card have value of 10 or not
        if (hand->secondCard == ten || hand->secondCard == jack ||
            hand->secondCard == queen || hand->secondCard == king) {
            return 1;
        }
    } else if (hand->firstCard == ten || hand->firstCard == jack ||
               hand->firstCard == queen ||
               hand->firstCard == king) { //If the first card have value 10, check if the second is Ace or not
        if (hand->secondCard == ace) {
            return 1;
        }
    }
    return 0;
}

int isBust(struct handInfo *hand) {
    if (getPoint(hand) > 21) {
//        printf("\n\tBUST! YOU LOSE!\n\tGood luck next time!");
        return 1;
    }
    return 0;
}

