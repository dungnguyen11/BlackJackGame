//
// Created by Sam on 30-Apr-17.
//

#include "Dealer.h"

struct dealerInfo *createDealer() {
    struct dealerInfo *dealer = malloc(sizeof(struct dealerInfo));
    if (dealer == NULL) {
        return NULL;
    }
    dealer->dealerMoney = 0;
    dealer->firstCard = 0;
    dealer->secondCard = 0;
    dealer->thirdCard = 0;
    dealer->fourthCard = 0;
    dealer->fifthCard = 0;
    return dealer;
}

void freeDealer(struct dealerInfo *dealer) {
    free(dealer);
}

void setDealerForNewGame(struct dealerInfo *dealer) {
    dealer->firstCard = 0;
    dealer->secondCard = 0;
    dealer->thirdCard = 0;
    dealer->fourthCard = 0;
    dealer->fifthCard = 0;
}


void dealerGetFirstCard(struct dealerInfo *dealer, int *deck) {
    int card = getCardAndDisp(deck);
    dealer->firstCard = card;
}

void dealerGetSecondCard(struct dealerInfo *dealer, int *deck) {
    int card = getCardAndDisp(deck);
    dealer->secondCard = card;
}

//int countCardDealer = 3;

void dealerGetNextCard(struct dealerInfo *dealer, int *deck, int countCardDealer) {

    int card = getCard(deck);

    switch (countCardDealer) {
        case 3:
            printf("\nDEALER THIRD CARD: \n");
            dealer->thirdCard = card;
            break;
        case 4:
            printf("\nDEALER FOURTH CARD: \n");
            dealer->fourthCard = card;
            break;
        case 5:
            printf("\nDEALER FIFTH CARD: \n");
            dealer->fifthCard = card;
            break;
    }
    displayCard(card);
}

void adjustValueOfCardDealer(struct dealerInfo *dealer) {
    int jack = 12, queen = 13, king = 14;

    //Adjust value of jack, queen and king card to value 10
    //First card
    if (dealer->firstCard == jack || dealer->firstCard == queen || dealer->firstCard == king) {
        dealer->firstCard = 10;
    }
    //Second card
    if (dealer->secondCard == jack || dealer->secondCard == queen || dealer->secondCard == king) {
        dealer->secondCard = 10;
    }
    //Third card
    if (dealer->thirdCard == jack || dealer->thirdCard == queen || dealer->thirdCard == king) {
        dealer->thirdCard = 10;
    }
    //Fourth card
    if (dealer->fourthCard == jack || dealer->fourthCard == queen || dealer->fourthCard == king) {
        dealer->fourthCard = 10;
    }
    //Fifth card
    if (dealer->fifthCard == jack || dealer->fifthCard == queen || dealer->fifthCard == king) {
        dealer->fifthCard = 10;
    }
}


int getPointDealer(struct dealerInfo *dealer) {

    //Have to change value of jack, queen, king to 10 before get total point
    adjustValueOfCardDealer(dealer);

    //After change value of jack, queen, and king, get correct total value
    int total = dealer->firstCard + dealer->secondCard +
                dealer->thirdCard + dealer->fourthCard + dealer->fifthCard;
    return total;
}

void getPointAndDispDealer(struct dealerInfo *dealer) {
    int dealerTotalPoint = getPointDealer(dealer);
    printf("\tTOTAL DEALER POINT: %d\n", dealerTotalPoint);
}

int isDealerBlackJack(struct dealerInfo *dealer) {
    int ace = 11, ten = 10, jack = 12, queen = 13, king = 14;

    //Just need to check the first card of player
    if (dealer->firstCard == ace) {//If the first card is Ace, check if the second card have value of 10 or not
        if (dealer->secondCard == ten || dealer->secondCard == jack ||
            dealer->secondCard == queen || dealer->secondCard == king) {
            return 1;
        }
    } else if (dealer->firstCard == ten || dealer->firstCard == jack ||
               dealer->firstCard == queen ||
               dealer->firstCard == king) { //If the first card have value 10, check if the second is Ace or not
        if (dealer->secondCard == ace) {
            return 1;
        }
    }
    return 0;
}

int isDealerBust(struct dealerInfo *dealer) {
    if (getPointDealer(dealer) > 21) {
        return 1;
    }
    return 0;
}

int isDealerBustAndDisp(struct dealerInfo *dealer) {
    getPointAndDispDealer(dealer);
    if (getPointDealer(dealer) > 21) {
        printf("\n\t----DEALER BUSTS!----\n");
    }
}