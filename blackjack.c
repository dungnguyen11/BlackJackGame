//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"
#include "Player.h"
#include "Player.c"
#include "Dealer.h"
#include "Dealer.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>



void displayTitle() {
    printf("      222          11\n");
    printf("    222 222      11111\n");
    printf("  222    222    11 111\n");
    printf(" 222     222   11  111\n");
    printf(" 222     222  11   111\n");
    printf("        222        111\n");
    printf("       222         111\n");
    printf("      222          111\n");
    printf("     222           111\n");
    printf("    222            111\n");
    printf("   222             111\n");
    printf("  222              111\n");
    printf(" 222               111\n");
    printf(" 2222222222    11111111111\n");
    printf(" 2222222222    11111111111\n");

    printf("\n\t\tWELCOME TO BLACKJACK GAME!\n\n");
}



void play(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    int countCardPlayer = 3; //Variable is to count if player get third/fourth/fifth card
    int countCardDealer = 3; //Variable is to count if dealer get third/fourth/fifth card

    initCards(player, dealer, deck); //Get 2 cards of player and 1 card of dealer

    char hitStand = 'h'; //Initialize hitStand to 'h' to run the while loop

    //When player is not blackjack, ask for hit or stand
    if (!isPlayerBlackJack(player)) {
        while (hitStand == 'h' && countCardPlayer <= 5) {
            //Ask player to hit or stand
            hitStand = askHitOrStand(player);

            //If player choose Hit, pick next cards
            if (hitStand == 'h') {
                sleep(1);
                playerGetNextCard(player, deck, countCardPlayer);
                countCardPlayer++;
                getPointAndDispPlayer(player);
            }

            //Do not let player hit another card if he/she busts
            if (isPlayerBust(player)) {
                printf("\n\t----PLAYER BUSTS!----\n");
                hitStand = 's';
            }
        }
    }

    //Dealer get second card after player get enough cards
    printf("\nNow is dealer's turn: \n");
    sleep(1); //sleep to get different random card
    printf("\nDEALER SECOND CARD: \n");
    dealerGetSecondCard(dealer, deck);

    if (isDealerBlackJack(dealer)) { //If dealer get blackjack, display text say so, and find winner directly
        printf("\n\t-----BLACKJACK----\n");
    } else {
        while (getPointDealer(dealer) <= 17 &&
               countCardDealer <= 5) {//Dealer have to hit another card if his total is smaller than 17
            sleep(1);
            dealerGetNextCard(dealer, deck, countCardDealer);
            countCardDealer++;
        }

        isDealerBustAndDisp(dealer); //Display total point and bust message if have of dealer
    }

    printWinner(player, dealer);

}

void initCards(struct playerInfo *player, struct dealerInfo *dealer, int *deck) {
    srand(time(NULL));
    printf("\nOk, let get started! Good luck!\n\n");

    //Get 2 cards of player
    sleep(1); //sleep to get different random card
    printf("PLAYER FIRST CARD: \n");
    playerGetFirstCard(player, deck); //Player get first card

    sleep(1);//sleep to get different random card
    printf("PLAYER SECOND CARD: \n");
    playerGetSecondCard(player, deck); //Player get second card

    //Check if player got Blackjack, check before change value in getPointPlayer
    if (isPlayerBlackJack(player)) {
        printf("\n\t----BLACKJACK!----\n");
    } else {
        getPointAndDispPlayer(player); //Get and display player total point
    }

    //Get first card of dealer
    sleep(1);  //sleep to get different random card
    printf("DEALER FIRST CARD: \n");
    dealerGetFirstCard(dealer, deck); //Dealer get first card
    getPointAndDispDealer(dealer);
}


void displayCard(int card) {

    //Card from 2 to 10
    if (card <= 9) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|     |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    } else if (card == 10) {
        printf("-------\n");
        printf("|%d    |\n", card);
        printf("|      |\n");
        printf("|    %d|\n", card);
        printf("-------\n");
    } else if (card == 11) { //Ace Card
        printf("-------\n");
        printf("|%c    |\n", 'A');
        printf("|     |\n");
        printf("|    %c|\n", 'A');
        printf("-------\n");
    } else if (card == 12) { //Jack Card
        printf("--------\n");
        printf("|%c    |\n", 'J');
        printf("|     |\n");
        printf("|    %c|\n", 'J');
        printf("--------\n");
    } else if (card == 13) { //Queen Card
        printf("-------\n");
        printf("|%c    |\n", 'Q');
        printf("|     |\n");
        printf("|    %c|\n", 'Q');
        printf("-------\n");
    } else if (card == 14) { //King Card
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
        card = (int) (rand() % 13 + 2); //Get random card value from 2 to 14
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

char askHitOrStand(struct playerInfo *player) {
    char answer;
    int check = 1;
    while (check) {
        if (answer != '\n') {
            printf("Do you want to hit(h) or stand(s)?\n");
            scanf("%s", &answer);
            if (answer == 'h' || answer == 's') {
                return answer;
            } else {
                printf("Please choose 'h' for Hit or 's' for Stand\n");
            }
        }
        check = 1;
    }
}

int isPlayerWin(struct playerInfo *player, struct dealerInfo *dealer) {
    if (((getPointPlayer(player) > getPointDealer(dealer)) && isPlayerBust(player) == 0) || //Player is higher than Dealer
        ((isPlayerBust(player) == 0) && (isDealerBust(dealer) == 1)) || //Dealer busts
        ((isPlayerBlackJack(player) == 1) && (isDealerBlackJack(dealer) == 0))) { //Player get blackjack

        return 1; //For win

    } else if (((getPointPlayer(player) < getPointDealer(dealer)) && isDealerBust(dealer) == 0) || //Player is lower than Dealer
               ((isPlayerBust(player) == 1) && (isDealerBust(dealer) == 0)) || //Player busts
               (isPlayerBlackJack(player) == 0 && (isDealerBlackJack(dealer) == 1))) { //Dealer get blackjack

        return 0; //For lose

    } else if ((getPointPlayer(player) == getPointDealer(dealer)) || //Player is equal to Dealer
               ((isPlayerBust(player) == 1) && (isDealerBust(dealer) == 1)) || //Both player and dealer bust
               ((isPlayerBlackJack(player) == 1) && (isDealerBlackJack(dealer) == 1))) { //Both player and dealer get blackjack

        return 2; //For Push

    } else {
        printf("This is exception. Fix this!");
    }
    return 3; //exception
}

void printWinner(struct playerInfo *player, struct dealerInfo *dealer) {
    int newMoney = 0;
    if (isPlayerWin(player, dealer) == 1) { //Player win
        printf("\n\t-->>YOU WIN!<<--\n Your wager is doubled!\n");
        newMoney = getBetMoney(player) * 2 + getTotalMoney(player); //if win, double the bet and add to totalMoney
    } else if (isPlayerWin(player, dealer) == 0) { //Player lose
        printf("\n\t-->>YOU LOSE!<<--\n You lose your wager. Good luck next time!\n");
        newMoney = getTotalMoney(player) - getBetMoney(player); //if lose, total money subtract the bet
    } else if (isPlayerWin(player, dealer) == 2) { //Push
        printf("\n\t-->>PUSH! NO WINNER.<<--\n You will get your wager back.\n");
        newMoney = getTotalMoney(player); //if push, do not change the total money
    } else {
        printf("This is exception. Fix this!");
    }
    printf("PLAYER TOTAL MONEY: $%d\n\n", newMoney);
    setTotalMoney(newMoney, player); //Change the value of total money
}

char askPlayAgain(struct playerInfo *player) {
    char answer = 0;
    int playAgain = 1;

    //Check if player have enough money to continue playing
    if (getTotalMoney(player) == 0) {
        printf("You do not have enough money to continue playing.\n\n");
        answer = 'n';
        return answer;
    } else {
        while (playAgain) {

            clear(); //Clear input of user
            printf("Do you want to play again?(y/n)\n");
            scanf("%c", &answer);

            if (answer == 'y') {
                break; //Continue playing, break out the while loop
            } else if (answer == 'n') {
                printf("\tTHANKS FOR PLAYING!\n\n");
                playAgain = 0; //Change playAgain value to end while loop
            }
        }
    }
    return answer;
}

void clear() {
    while (getchar() != '\n');
}

int displayAskMenu() {
//    system("cls");
    int answer = 0;
    printf("Enter 1 to Play\n");
    printf("Enter 2 to See the Rules.\n");
    printf("Enter 3 to Exit Game.\n");
    scanf("%d", &answer);

    while (answer != 1 && answer != 2 && answer != 3) {
        printf("\nIncorrect choice. Please enter 1, 2 or 3.\n");
        clear();
        scanf("%d", &answer);
    }

    switch (answer) {
        case 1:
            return 1;
        case 2:
            return 2;
        case 3:
            return 3;
    }
}

void displayRules() {
    printf("\n           RULES of BLACKJACK");
    printf("\n          ---------------------------");
    printf("\nI.");
    printf("\n      %c This program generates cards at random.", '*');
    printf("\n      %c If you keep losing, you are very unlucky!\n", '*');

    printf("\nII.");
    printf("\n     Each card has a value.");
    printf("\n      %c Number cards 1 to 10 hold a value of their number.", '*');
    printf("\n      %c J, Q, and K cards hold a value of 10.", '*');
    printf("\n      %c Ace cards hold a value of 11", '*');
    printf("\n     The goal of this game is to reach a card value total of 21 or having a Blackjack.\n");
    printf("\n     Blackjack is when you have an Ace card with a 10-value card. And Blackjack is strongest couple you could have.\n");

    printf("\nIII.");
    printf("\n     After the dealing of the first two cards, YOU must decide whether to HIT or STAY.");
    printf("\n      %c Staying will keep you safe, hitting will add a card.", '*');
    printf("\n     Because you are competing against the dealer, you must beat his hand.");
    printf("\n     When you lose?");
    printf("\n      %c If your total goes over 21 (known as \"busts\"), and dealer is not, you will LOSE!.", '*');
    printf("\n      %c If your total is smaller than dealer's, you will LOSE!.", '*');
    printf("\n      %c If dealer have Blackjack, and you do not, you will LOSE!.", '*');
    printf("\n      %c If you LOSE, you will lose your wager.", '*');
    printf("\n");
    printf("\n     When you win?");
    printf("\n      %c If dealer busts, and you do not, you will WIN!.", '*');
    printf("\n      %c If your total is bigger than dealer's, you will WIN!.", '*');
    printf("\n      %c If you have Blackjack, and dealer does not, you will WIN!.", '*');
    printf("\n      %c If you WIN, your wager will be doubled.", '*');
    printf("\n");
    printf("\n     When you have push?");
    printf("\n      %c If your total is equal to dealer's, you will have PUSH!.", '*');
    printf("\n      %c If both you and dealer bust, you will have PUSH!.", '*');
    printf("\n      %c If you have Blackjack, and dealer does too, you will have PUSH!.", '*');
    printf("\n      %c If you have PUSH, your wager will be return.", '*');
    printf("\n");
    printf("\n     After a play, and if you still have enough money, you can always play again.\n\n");
}

