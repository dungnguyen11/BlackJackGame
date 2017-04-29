//
// Created by Sam on 28-Apr-17.
//

#ifndef BLACKJACKGAME_BLACKJACK_H
#define BLACKJACKGAME_BLACKJACK_H

struct playerInfo {
    int playerMoney;
    int firstCard;
    int secondCard;
    int thirdCard;
    int fourthCard;
    int fifthCard;
};

struct dealerInfo {
    int dealerMoney;
    int firstCard;
    int secondCard;
    int thirdCard;
    int fourthCard;
    int fifthCard;
};

struct card {

};

struct playerInfo * createPlayer();
struct dealerInfo * createDealer();

void freePlayer(struct playerInfo * player);
void freeDealer(struct dealerInfo * dealer);

void displayTitle();

void askMoneyPlayer(struct playerInfo *player);

void play(struct playerInfo *player, struct dealerInfo *dealer, int *deck);

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck);

void setNewDeck(int *deck);

int checkCardIfAvailable(int card, int array[]);

int getCard(int *deck);

int getCardAndDisp(int *deck);

void displayCard(int card);

void dealerGetFirstCard(struct dealerInfo *dealer, int *deck);

void dealerGetSecondCard(struct dealerInfo *dealer, int *deck);

void playerGetFirstCard(struct playerInfo *player, int *deck);

void playerGetSecondCard(struct playerInfo *player, int *deck);

int getPointPlayer(struct playerInfo * player);

int getPointDealer(struct dealerInfo * dealer);

int getPlayerMoney(struct playerInfo *player);

char askPlayMore();

int isPlayerBlackJack(struct playerInfo *player);

int isPlayerBust(struct playerInfo *player);

void findWinner(struct playerInfo *player, struct dealerInfo *dealer);

#endif //BLACKJACKGAME_BLACKJACK_H
