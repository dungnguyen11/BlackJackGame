//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"

struct playerInfo * createPlayer() {
    struct playerInfo * player = malloc(sizeof(struct playerInfo));
    if (player == NULL) {
        return NULL;
    }
    player->playerMoney = 0;
    player->firstCard = 0;
    player->secondCard = 0;
}
struct dealerInfo * createDealer() {
    struct dealerInfo * dealer = malloc(sizeof(struct dealerInfo));
    if (dealer == NULL) {
        return NULL;
    }
    dealer->dealerMoney = 0;
    dealer->firstCard = 0;
    dealer->secondCard = 0;
}

void freePlayer(struct playerInfo * player) {
    free(player);
}
void freeDealer(struct dealerInfo * dealer) {
    free(dealer);
}

void displayTitle() {
    printf("\n\t\tWELCOME TO BLACKJACK GAME!\n\n");
}

void askInfoPlayer(struct playerInfo *player){
    int money = 0;
    printf("We hope you have a lucky day!\n");
    printf("Before you start, we would like to ask you some question: \n");
    printf("How much money do you want to play today?\n");
    scanf("%d", &money);

//    while (check == 0) {
//        printf("\nPlease enter your name.\n");
//        check = scanf("%s\n", player->name);
//    }
    player->playerMoney = money;
    printf("Your total: $%i\n", getTotalMoney(player));
}

void initCards() {
    printf("\nOk, let get started! Good luck!\n");

}


void displayCard(int card) {
    //Card from 2 to 10
    if (card <= 9) {
        printf("--------\n");
        printf("|%d    |\n", card);
        printf("|     |\n");
        printf("|    %d|\n", card);
        printf("--------\n");
    }

    if (card == 10) {
        printf("--------\n");
        printf("|%d    |\n", card);
        printf("|      |\n");
        printf("|    %d|\n", card);
        printf("--------\n");
    }

    //Ace Card
    if (card == 11) {
        printf("--------\n");
        printf("|%c    |\n", 'A');
        printf("|     |\n");
        printf("|    %c|\n", 'A');
        printf("--------\n");
    }

    //Jack Card
    if (card == 12) {
        printf("--------\n");
        printf("|%c    |\n", 'J');
        printf("|     |\n");
        printf("|    %c|\n", 'J');
        printf("--------\n");
    }

    //Queen Card
    if (card == 13) {
        printf("--------\n");
        printf("|%c    |\n", 'Q');
        printf("|     |\n");
        printf("|    %c|\n", 'Q');
        printf("--------\n");
    }

    //King Card
    if (card == 14) {
        printf("--------\n");
        printf("|%c    |\n", 'K');
        printf("|     |\n");
        printf("|    %c|\n", 'K');
        printf("--------\n");
    }
}

void dealerGetFirstCard(struct dealerInfo * dealer) {
    srand(time(NULL));
    int card = rand() % 12 + 2; //Get random card value from 2 to 14
    displayCard(card);
    dealer->firstCard = card;
}

void dealerGetSecondCard(struct dealerInfo * dealer) {
    srand(time(NULL));
    int card = rand() % 12 + 2; //Get random card value from 2 to 14
    displayCard(card);
    dealer->secondCard = card;
}

void playerGetFirstCard(struct playerInfo * player) {
    srand(time(NULL));
    int card = rand() % 12 + 2; //Get random card value from 2 to 14
    displayCard(card);
    player->firstCard = card;
}

void playerGetSecondCard(struct playerInfo * player) {
    srand(time(NULL));
    int card = rand() % 12 + 2; //Get random card value from 2 to 14
    displayCard(card);
    player->secondCard;
}

int getPointPlayer(struct playerInfo * player) {
    int total = player->firstCard + player->secondCard;
    return total;
}

int getPointDealer(struct dealerInfo * dealer) {
    int total = dealer->firstCard + dealer->secondCard;
    return total;
}

int getTotalMoney(struct playerInfo * player) {
    return player->playerMoney;
}

void askPlayMore();

void findWinner();
