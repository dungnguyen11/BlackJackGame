//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"
#include <stdbool.h>


struct playerInfo * createPlayer() {
    struct playerInfo * player = malloc(sizeof(struct playerInfo));
    if (player == NULL) {
        return NULL;
    }
    player->playerMoney = 0;
    player->firstCard = 0;
    player->secondCard = 0;
    player->thirdCard = 0;
    player->fourthCard = 0;
    player->fifthCard = 0;
}
struct dealerInfo * createDealer() {
    struct dealerInfo * dealer = malloc(sizeof(struct dealerInfo));
    if (dealer == NULL) {
        return NULL;
    }
    dealer->dealerMoney = 0;
    dealer->firstCard = 0;
    dealer->secondCard = 0;
    dealer->thirdCard = 0;
    dealer->fourthCard = 0;
    dealer->fifthCard = 0;
}

void freePlayer(struct playerInfo * player) {
    free(player);
}
void freeDealer(struct dealerInfo * dealer) {
    free(dealer);
}

//TODO: implement set new deck in here, having error now
void setNewDeck(int *deck) {
    printf("in set");
//    int length = sizeof(deck)/ sizeof(int);
//    for (int i = 0; i < length; ++i) {
//       deck[i] = 0;
//    }
    memset(deck, 0, sizeof(deck));
}

void displayTitle() {
    printf("\n\t\tWELCOME TO BLACKJACK GAME!\n\n");
}

void askMoneyPlayer(struct playerInfo *player) {
    int money;
    printf("We hope you have a lucky day!\n");
    printf("Before you start, we would like to ask you some question: \n");
    printf("How much money do you want to play today?\n");

    while (scanf("%d", &money) != 1) {
        printf("Please enter your money.\n");
        scanf("%*s");
    }

    player->playerMoney = money;
    printf("Your total money: $%i\n", getPlayerMoney(player));
}

void play(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    initCards(player, dealer, deck);
}

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    srand(time(NULL));
    printf("\nOk, let get started! Good luck!\n");

    //Get 2 cards of player
    printf("PLAYER FIRST CARD: \n");
    playerGetFirstCard(player, deck); //Player get first card
    sleep(1);
    printf("PLAYER SECOND CARD: \n");
    playerGetSecondCard(player, deck); //Player get second card
//    if (isPlayerBlackJack(player)) {
//        printf("\nBLACKJACK!\n");
//    } else {
    int playerTotalPoint = getPointPlayer(player);
    printf("TOTAL PLAYER POINT: %d\n\n", playerTotalPoint); //Get and display player total point
//    }

    //Get card of dealer
    sleep(1);
    printf("DEALER FIRST CARD: \n");
    dealerGetFirstCard(dealer, deck); //Dealer get first card
    sleep(1);
    printf("DEALER SECOND CARD: \n");
    dealerGetSecondCard(dealer, deck); //Dealer get second card
    int dealerTotalPoint = getPointDealer(dealer);
    printf("TOTAL DEALER POINT: %d\n\n", dealerTotalPoint); //Get and display dealer total point
}


void displayCard(int card) {
    //Card from 2 to 10
    if (card <= 9) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|     |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    }
    if (card == 10) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|      |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    }

    //Ace Card
    if (card == 11) {
        printf("-------\n");
        printf("|%c    |\n", 'A');
        printf("|     |\n");
        printf("|    %c|\n", 'A');
        printf("-------\n");
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
        printf("-------\n");
        printf("|%c    |\n", 'Q');
        printf("|     |\n");
        printf("|    %c|\n", 'Q');
        printf("-------\n");
    }

    //King Card
    if (card == 14) {
        printf("-------\n");
        printf("|%c    |\n", 'K');
        printf("|     |\n");
        printf("|    %c|\n", 'K');
        printf("-------\n");
    }
}

int checkCardIfAvailable(int card, int *deck) {
    if (deck[card] >= 4) {
        return 0;
    }
    return 1;
}

int getCard(int *deck) {
    int card = 0;
    while (checkCardIfAvailable(card, deck)) {
        srand(time(NULL));
        card = (rand() % 13 + 2); //Get random card value from 2 to 14
        if (checkCardIfAvailable(card, deck) && card != 0) { //Check if the card is available or not
            deck[card]++;
            break;
        }
        card = 0;
    }
    return card;
}

int getCardAndDisp(int *deck) {
    int card = getCard(deck);
    displayCard(card);
    return card;
}

void dealerGetFirstCard(struct dealerInfo *dealer, int *deck) {
    int card = getCardAndDisp(deck);
    dealer->firstCard = card;
}

void dealerGetSecondCard(struct dealerInfo *dealer, int *deck) {
    int card = getCardAndDisp(deck);
    dealer->secondCard = card;
}

void playerGetFirstCard(struct playerInfo *player, int *deck) {
    int card = getCardAndDisp(deck);
    player->firstCard = card;
}

void playerGetSecondCard(struct playerInfo *player, int *deck) {
    int card = getCardAndDisp(deck);
    player->secondCard = card;
}

int countCard = 3;

void playerGetNextCard(struct playerInfo *player, int *deck) {

    int card = getCardAndDisp(deck);
    switch (countCard) {
        case 3:
            player->thirdCard = card;
            countCard++;
            break;
        case 4:
            player->fourthCard = card;
            countCard++;
            break;
        case 5:
            player->fifthCard = card;
            countCard++;
            break;
    }
}

void adjustValueOfCard(struct playerInfo *player) {
    int jack = 12, queen = 13, king = 14;
    printf("inside adjust\n");
    printf("first card: %d\n", player->firstCard);
    printf("second card: %d\n", player->secondCard);

    //TODO: fix the error that can not adjust value of jack, queen or king
    //Adjust value of jack, queen and king card to value 10
    if (player->firstCard == 12 || player->firstCard == 13 || player->firstCard == 14) { //First card
        player->firstCard == 10;
    } else if (player->secondCard == 12 || player->secondCard == 13 || player->secondCard == 14) { //Second card
        player->secondCard == 10;
    } else if (player->thirdCard == jack || player->thirdCard == queen || player->thirdCard == king) { //Third card
        player->thirdCard == 10;
    } else if (player->fourthCard == jack || player->fourthCard == queen || player->fourthCard == king) { //Fourth card
        player->fourthCard == 10;
    } else if (player->fifthCard == jack || player->fifthCard == queen || player->fifthCard == king) { //Fifth card
        player->fifthCard == 10;
    }
}

int getPointPlayer(struct playerInfo * player) {
    //TODO: need to set jack, queen and king back to 10 value
    //Have to change value of jack, queen, king to 10 before get total point
    adjustValueOfCard(player);

    //After change value of jack, queen, and king, get correct total value
    int total = player->firstCard + player->secondCard +
                player->thirdCard + player->fourthCard + player->fifthCard;
    return total;
}

int getPointDealer(struct dealerInfo * dealer) {
    //TODO: need to set jack, queen and king back to 10 value
    int total = dealer->firstCard + dealer->secondCard +
                dealer->thirdCard + dealer->fourthCard + dealer->fifthCard;
    return total;
}

int getPlayerMoney(struct playerInfo *player) {
    return player->playerMoney;
}

char askPlayMore() {
    char answer;
    int playAgain = 1;
    while (playAgain) {
        printf("Do you want to play again?(y/n)\n");
        scanf("%c", &answer);

        if (answer == 'y') {
            break; //Continue playing, break out the while loop
        } else if (answer == 'n') {
            printf("\tTHANKS FOR PLAYING!\n\tHAVE A GOOD DAY!\n");
            playAgain = 0; //Change playAgain value to end while loop
        }
    }
    return answer;
}

int isPlayerBlackJack(struct playerInfo *player) {
    int ace = 11, ten = 10, jack = 12, queen = 13, king = 14;

    //Just need to check the first card of player
    if (player->firstCard == ace) {//If the first card is Ace, check if the second card have value of 10 or not
        if (player->secondCard == ten || player->secondCard == jack ||
            player->secondCard == queen || player->secondCard == king) {
//            printf("\nBLACKJACK!\n");
            return 1;
        }
        return 0;
    } else if (player->firstCard == ten || player->firstCard == jack ||
               player->firstCard == queen || player->firstCard == king) { //If the first card have value 10,
        // check if the second is Ace or not
        if (player->secondCard == ace) {
//            printf("\nBLACKJACK!\n");
            return 1;
        }
        return 0;
    }

    //Check the second card of player
//    if (player->secondCard == ace) { //If the second card is Ace, check
//        if (player->firstCard == ten || player->firstCard == jack ||
//                player->firstCard == queen || player->firstCard == king) {
//            return 1;
//        }
//        return 0;
//    } else if (player->secondCard == ten || player->secondCard == jack ||
//            player->secondCard == queen || player->secondCard == king) {
//        if (player->firstCard == ace) {
//            return 1;
//        }
//        return 0;
//    }

}

int isPlayerBust(struct playerInfo *player) {
    if (getPointPlayer(player) > 21) {
        printf("\n\tBUST! YOU LOSE!\n\tGood luck next time!");
        return 1;
    }
    return 0;
}

void findWinner(struct playerInfo *player, struct dealerInfo *dealer) {
    //TODO: add blackjack case in here
    if (getPointPlayer(player) > getPointDealer(dealer)) {
        printf("\n\tYOU WIN!\n");
    } else if (getPointPlayer(player) < getPointDealer(dealer)) {
        printf("\n\tYOU LOSE!\n Good luck next time!\n");
    } else {
        printf("\n\tPUSH! NO WINNER.\n You will get your wager back.\n");
    }
}
