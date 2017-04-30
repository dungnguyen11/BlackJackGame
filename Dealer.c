//
// Created by Sam on 30-Apr-17.
//

#include "Dealer.h"

struct dealerInfo *createDealer() {
    struct dealerInfo *dealer = malloc(sizeof(struct dealerInfo));
    if (dealer == NULL) {
        return NULL;
    }
    dealer->dealerMoney = 0;
    dealer->firstCard = 0;
    dealer->secondCard = 0;
    dealer->thirdCard = 0;
    dealer->fourthCard = 0;
    dealer->fifthCard = 0;
}

void freeDealer(struct dealerInfo *dealer) {
    free(dealer);
}


void dealerGetFirstCard(struct dealerInfo *dealer, int *deck) {
    int card = getCardAndDisp(deck);
    dealer->firstCard = card;
}

void dealerGetSecondCard(struct dealerInfo *dealer, int *deck) {
    int card = getCardAndDisp(deck);
    dealer->secondCard = card;
}

void dealerGetNextCard(struct dealerInfo *dealer, int *deck) {

}

void adjustValueOfCardDealer(struct dealerInfo *dealer) {
    int jack = 12, queen = 13, king = 14;

    //Adjust value of jack, queen and king card to value 10
    if (dealer->firstCard == jack || dealer->firstCard == queen || dealer->firstCard == king) { //First card
        dealer->firstCard = 10;
    } else if (dealer->secondCard == jack || dealer->secondCard == queen || dealer->secondCard == king) { //Second card
        dealer->secondCard = 10;
    } else if (dealer->thirdCard == jack || dealer->thirdCard == queen || dealer->thirdCard == king) { //Third card
        dealer->thirdCard = 10;
    } else if (dealer->fourthCard == jack || dealer->fourthCard == queen || dealer->fourthCard == king) { //Fourth card
        dealer->fourthCard = 10;
    } else if (dealer->fifthCard == jack || dealer->fifthCard == queen || dealer->fifthCard == king) { //Fifth card
        dealer->fifthCard = 10;
    }
}


int getPointDealer(struct dealerInfo *dealer) {

    //Have to change value of jack, queen, king to 10 before get total point
    adjustValueOfCardDealer(dealer);

    //After change value of jack, queen, and king, get correct total value
    int total = dealer->firstCard + dealer->secondCard +
                dealer->thirdCard + dealer->fourthCard + dealer->fifthCard;
    return total;
}

int isDealerBlackJack(struct dealerInfo *dealer) {
    return 0;
}

int isDealerBust(struct dealerInfo *dealer) {
    if (getPointDealer(dealer) > 21) {
        return 1;
    }
    return 0;
}