//
// Created by Sam on 28-Apr-17.
//

#include "Hand.h"

#ifndef BLACKJACKGAME_BLACKJACK_H
#define BLACKJACKGAME_BLACKJACK_H

/**
 *
 */
void displayTitle();

void play(struct handInfo *player, struct handInfo *dealer, int *deck);

void initCards(struct handInfo *player, struct handInfo *dealer, int *deck);

int checkCardIfAvailable(int card, int array[]);

int getCard(int *deck);

//int getCardAndDisp(int *deck);

void displayManyCards(struct handInfo *hand);

void displayCard(int card);

char askHitOrStand(struct handInfo *player);

int isPlayerWin(struct handInfo *player, struct handInfo *dealer);

void printWinner(struct handInfo *player, struct handInfo *dealer);

char askPlayAgain(struct handInfo *player);

void clear();

int displayAskMenu();

void displayRules();


#endif //BLACKJACKGAME_BLACKJACK_H
