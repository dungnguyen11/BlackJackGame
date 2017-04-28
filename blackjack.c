//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"

//52 cards is store in an array to check every time the player or dealer get a card
int deck[14] = {0};

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
    setNewDeck(deck); //set new deck for new game
    printf("\n\t\tWELCOME TO BLACKJACK GAME!\n\n");
}

void askInfoPlayer(struct playerInfo *player){
    int money;
    printf("We hope you have a lucky day!\n");
    printf("Before you start, we would like to ask you some question: \n");
    printf("How much money do you want to play today?\n");

    while (scanf("%d", &money) != 1) {
        printf("Please enter your money.\n");
        scanf("%*s");
    }

    player->playerMoney = money;
    printf("Your total: $%i\n", getTotalMoney(player));
}

void initCards() {
    printf("\nOk, let get started! Good luck!\n");
}

void setNewDeck(int *array) {
    int length = (int) sizeof(array) / sizeof(int);
    for (int i = 0; i < length; ++i) {
        array[i] = 0;
    }
}

int checkCardIfAvailable(int card, int array[]) {
    if (array[card] > 4) {
        return 0;
    }
    return 1;
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
    int card;
    do {
        srand(time(NULL));
        card = rand() % 12 + 2; //Get random card value from 2 to 14
        if (checkCardIfAvailable(card, deck)) {
            deck[card]++;
            break;
        }
    } while (checkCardIfAvailable(card, deck));
    displayCard(card);
    dealer->firstCard = card;
}

void dealerGetSecondCard(struct dealerInfo * dealer) {
    int card;
    do {
        srand(time(NULL));
        card = rand() % 12 + 2; //Get random card value from 2 to 14
        if (checkCardIfAvailable(card, deck)) {
            deck[card]++;
            break;
        }
    } while (checkCardIfAvailable(card, deck));
    displayCard(card);
    dealer->secondCard = card;
}

void playerGetFirstCard(struct playerInfo * player) {
    int card;
    do {
        srand(time(NULL));
        card = rand() % 12 + 2; //Get random card value from 2 to 14
        if (checkCardIfAvailable(card, deck)) {
            deck[card]++;
            break;
        }
    } while (checkCardIfAvailable(card, deck));
    displayCard(card);
    player->firstCard = card;
}

void playerGetSecondCard(struct playerInfo * player) {
    int card;
    do {
        srand(time(NULL));
        card = rand() % 12 + 2; //Get random card value from 2 to 14
        if (checkCardIfAvailable(card, deck)) {
            deck[card]++;
            break;
        }
    } while (checkCardIfAvailable(card, deck));
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
