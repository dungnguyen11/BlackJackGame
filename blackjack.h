//
// Created by Sam on 28-Apr-17.
//

#ifndef BLACKJACKGAME_BLACKJACK_H
#define BLACKJACKGAME_BLACKJACK_H

struct playerInfo {
    int playerMoney;
    int firstCard;
    int secondCard;
};

struct dealerInfo {
    int dealerMoney;
    int firstCard;
    int secondCard;
};

struct card {

};

struct playerInfo * createPlayer();
struct dealerInfo * createDealer();

void freePlayer(struct playerInfo * player);
void freeDealer(struct dealerInfo * dealer);

void displayTitle();

void askInfoPlayer(struct playerInfo *player);

void initCards();

void setNewDeck(int array[]);

int checkCardIfAvailable(int card, int array[]);

void displayCard(int card);

void dealerGetFirstCard(struct dealerInfo * dealer);

void dealerGetSecondCard(struct dealerInfo * dealer);

void playerGetFirstCard(struct playerInfo * player);

void playerGetSecondCard(struct playerInfo * player);

int getPointPlayer(struct playerInfo * player);

int getPointDealer(struct dealerInfo * dealer);

int getTotalMoney(struct playerInfo * player);

void askPlayMore();

void findWinner();

#endif //BLACKJACKGAME_BLACKJACK_H
