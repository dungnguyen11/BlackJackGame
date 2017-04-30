//
// Created by Sam on 30-Apr-17.
//

#ifndef BLACKJACKGAME_PLAYER_H
#define BLACKJACKGAME_PLAYER_H

struct playerInfo {
    int playerMoney;
    int firstCard;
    int secondCard;
    int thirdCard;
    int fourthCard;
    int fifthCard;
};

struct playerInfo *createPlayer();


void freePlayer(struct playerInfo *player);

void playerGetFirstCard(struct playerInfo *player, int *deck);

void playerGetSecondCard(struct playerInfo *player, int *deck);

void playerGetNextCard(struct playerInfo *player, int *deck);

void adjustValueOfCardPlayer(struct playerInfo *player);

int getPointPlayer(struct playerInfo *player);

int getPlayerMoney(struct playerInfo *player);

void setPlayerMoney(int newMoney, struct playerInfo *player);

int isPlayerBlackJack(struct playerInfo *player);

int isPlayerBust(struct playerInfo *player);


#endif //BLACKJACKGAME_PLAYER_H
