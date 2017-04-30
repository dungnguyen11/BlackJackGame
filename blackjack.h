//
// Created by Sam on 28-Apr-17.
//

#include "Player.h"
#include "Dealer.h"

#ifndef BLACKJACKGAME_BLACKJACK_H
#define BLACKJACKGAME_BLACKJACK_H

void displayTitle();

void askMoneyPlayer(struct playerInfo *player);

void play(struct playerInfo *player, struct dealerInfo *dealer, int *deck);

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck);

void setNewDeck(int *deck);

int checkCardIfAvailable(int card, int array[]);

int getCard(int *deck);

int getCardAndDisp(int *deck);

void displayCard(int card);

char askPlayAgain();

void findWinner(struct playerInfo *player, struct dealerInfo *dealer);

#endif //BLACKJACKGAME_BLACKJACK_H
