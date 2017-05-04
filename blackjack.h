//
// Created by Sam on 28-Apr-17.
//

#include "Player.h"
#include "Dealer.h"

#ifndef BLACKJACKGAME_BLACKJACK_H
#define BLACKJACKGAME_BLACKJACK_H

/**
 *
 */
void displayTitle();

void play(struct playerInfo *player, struct dealerInfo *dealer, int *deck);

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck);

int checkCardIfAvailable(int card, int array[]);

int getCard(int *deck);

int getCardAndDisp(int *deck);

void displayCard(int card);

char askHitOrStand(struct playerInfo *player);

int isPlayerWin(struct playerInfo *player, struct dealerInfo *dealer);

void printWinner(struct playerInfo *player, struct dealerInfo *dealer);

char askPlayAgain(struct playerInfo *player);

void clear();

int displayAskMenu();

void displayRules();


#endif //BLACKJACKGAME_BLACKJACK_H
