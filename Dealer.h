//
// Created by Sam on 30-Apr-17.
//

//#include "blackjack.h"

#ifndef BLACKJACKGAME_DEALER_H
#define BLACKJACKGAME_DEALER_H

struct dealerInfo {
    int dealerMoney;
    int firstCard;
    int secondCard;
    int thirdCard;
    int fourthCard;
    int fifthCard;
};

struct dealerInfo *createDealer();

void freeDealer(struct dealerInfo *dealer);

void setDealerForNewGame(struct dealerInfo *dealer);

void dealerGetFirstCard(struct dealerInfo *dealer, int *deck);

void dealerGetSecondCard(struct dealerInfo *dealer, int *deck);

void dealerGetNextCard(struct dealerInfo *dealer, int *deck, int countCardDealer);

void adjustValueOfCardDealer(struct dealerInfo *dealer);

int getPointDealer(struct dealerInfo *dealer);

void getPointAndDispDealer(struct dealerInfo *dealer);

int isDealerBlackJack(struct dealerInfo *dealer);

int isDealerBust(struct dealerInfo *dealer);

#endif //BLACKJACKGAME_DEALER_H
