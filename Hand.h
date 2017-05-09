//
// Created by Sam on 30-Apr-17.
//

//#include "blackjack.h"

#ifndef BLACKJACKGAME_PLAYER_H
#define BLACKJACKGAME_PLAYER_H

/**
 *
 */
struct handInfo {
    int totalMoney;
    int betMoney;
    int firstCard;
    int secondCard;
    int thirdCard;
    int fourthCard;
    int fifthCard;
};


struct handInfo *createHand();

void freeHand(struct handInfo *hand);


//For player only

void askMoney(struct handInfo *player);

int getTotalMoney(struct handInfo *player);

void setTotalMoney(int newMoney, struct handInfo *player);

void askBetMoney(struct handInfo *player);


int getBetMoney(struct handInfo *player);

//For both player and dealer

void setHandForNewGame(struct handInfo *hand);

void getFirstCard(struct handInfo *hand, int *deck);

void getSecondCard(struct handInfo *hand, int *deck);

void getNextCard(struct handInfo *hand, int *deck, int countCard);

void adjustValueOfCard(struct handInfo *hand);

int getPoint(struct handInfo *hand);

//void getPointAndDisp(struct handInfo *hand);

int isBlackJack(struct handInfo *hand);

int isBust(struct handInfo *hand);


#endif //BLACKJACKGAME_PLAYER_H
