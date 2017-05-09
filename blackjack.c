//
// Created by Sam on 28-Apr-17.
//

#include "blackjack.h"
#include "Hand.h"
#include "Hand.c"
//#include "Dealer.h"
//#include "Dealer.c"
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


void play(struct handInfo *player, struct handInfo *dealer, int *deck) {
    int countCardPlayer = 3; //Variable is to count when player get third/fourth/fifth card
    int countCardDealer = 3; //Variable is to count when dealer get third/fourth/fifth card


    initCards(player, dealer, deck); //Get 2 cards of player and 1 card of dealer

    char hitStand = 'h'; //Initialize hitStand to 'h' to run the while loop

    //When player is not blackjack, ask for hit or stand

    if (!isBlackJack(player)) {
        while (hitStand == 'h' && countCardPlayer <= 5) {
            //Ask player to hit or stand
            hitStand = askHitOrStand(player);

            //If player choose Hit, pick next cards

            if (hitStand == 'h') {
                printf("\nPLAYER'S CARDS: \n");
                sleep(1);
                getNextCard(player, deck, countCardPlayer);
                displayManyCards(player);
                printf("Players: %d - %d - %d - %d - %d\n", player->firstCard, player->secondCard, player->thirdCard,
                       player->fourthCard, player->fifthCard);
                printf("\n\tTOTAL PLAYER POINT: %d\n", getPoint(player));
                countCardPlayer++;
            }

            //Do not let player hit another card if he/she busts
            if (isBust(player)) {
                printf("\n\t---->>PLAYER BUSTS!<<----\n");
                hitStand = 's';
                sleep(3);
            }
        }
    }

    //Dealer get second card after player get enough cards
    printf("\nNow is dealer's turn: \n");
    printf("\nDEALER'S CARDS: \n");
    sleep(1); //sleep to get different random card
    getSecondCard(dealer, deck);
    displayManyCards(dealer);
    printf("\tTOTAL DEALER POINT: %d\n", getPoint(dealer));

    if (isBlackJack(dealer)) { //If dealer get blackjack, display text say so, and find winner directly
        printf("\n\t-----BLACKJACK----\n");
    } else {
        while ((getPoint(dealer) <= 17 || (getPoint(dealer) < getPoint(player))) && countCardDealer <= 5) {
            printf("\nDealer hit one more card...\n");
            sleep(2);
            printf("\nDEALER'S CARDS: \n");
            sleep(1);
            getNextCard(dealer, deck, countCardDealer);
            displayManyCards(dealer);
            printf("Dealer: %d - %d - %d - %d - %d\n", dealer->firstCard, dealer->secondCard, dealer->thirdCard,
                   dealer->fourthCard, dealer->fifthCard);
            printf("\n\tTOTAL DEALER POINT: %d\n", getPoint(dealer));
            countCardDealer++;

            //Check if the dealer bust and terminate loop if true
            if (isBust(dealer)) {
                printf("\n\t---->>DEALER BUSTS!<<----\n");
                break;
            }
        }
    }

    printWinner(player, dealer);

}

void initCards(struct handInfo *player, struct handInfo *dealer, int *deck) {
    srand(time(NULL));
    printf("\nOk, let get started! Good luck!\n\n");

    //Get 2 cards of player
    sleep(1); //sleep to get different random card
    getFirstCard(player, deck); //Player get first card
    sleep(1);//sleep to get different random card
    getSecondCard(player, deck); //Player get second card

    //Display 2 cards of player
    printf("PLAYER'S CARDS: \n");
    displayManyCards(player);

    //Check if player got Blackjack, check before change value in getPoint
    if (isBlackJack(player)) {
        printf("\n\t----BLACKJACK!----\n");
    } else {
        printf("\n\tTOTAL PLAYER POINT: %d\n", getPoint(player));
    }

    //Get first card of dealer
    sleep(1);  //sleep to get different random card
    getFirstCard(dealer, deck); //Dealer get first card
    printf("DEALER'S FIRST CARD: \n");
    displayManyCards(dealer);
    printf("\n\tTOTAL DEALER POINT: %d\n", getPoint(dealer));
}

int changeCharacter(int card) {
    //Using Ascii code to display A, J, Q, K character
    switch (card) {
        case 10:
            card += 74;
            break;
        case 11:
            card += 54;
            break;
        case 12:
            card += 62;
            break;
        case 13:
            card += 68;
            break;
        case 14:
            card += 61;
            break;
        default:
            card += 48;
            break;
    }
    return card;
}


void displayManyCards(struct handInfo *hand) {
    short numCard = 0;

    //Get how many card that hand has
    if (hand->firstCard != 0) {
        numCard++;
    }
    if (hand->secondCard != 0) {
        numCard++;
    }
    if (hand->thirdCard != 0) {
        numCard++;
    }
    if (hand->fourthCard != 0) {
        numCard++;
    }
    if (hand->fifthCard != 0) {
        numCard++;
    }
    short temp1 = hand->firstCard, temp2 = hand->secondCard,
            temp3 = hand->thirdCard, temp4 = hand->fourthCard, temp5 = hand->fifthCard; //Variables to store value of cards

    switch (numCard) {
        case 1: //Display only 1 card
            temp1 = changeCharacter(temp1);
            printf("--------\n");
            printf("|%2c    |\n", temp1);
            printf("|      |\n");
            printf("|    %2c|\n", temp1);
            printf("--------\n");
            break;

        case 2: //Display 2 cards
            temp1 = changeCharacter(temp1);
            temp2 = changeCharacter(temp2);
            printf("--------   --------\n");
            printf("|%2c    |   |%2c    |\n", temp1, temp2);
            printf("|      |   |      |\n");
            printf("|    %2c|   |    %2c|\n", temp1, temp2);
            printf("--------   --------\n");
            break;

        case 3: //Display 3 cards
            temp1 = changeCharacter(temp1);
            temp2 = changeCharacter(temp2);
            temp3 = changeCharacter(temp3);
            printf("--------   --------   --------\n");
            printf("|%2c    |   |%2c    |   |%2c    |\n", temp1, temp2, temp3);
            printf("|      |   |      |   |      |\n");
            printf("|    %2c|   |    %2c|   |    %2c|\n", temp1, temp2, temp3);
            printf("--------   --------   --------\n");
            break;

        case 4: //Display 4 cards
            temp1 = changeCharacter(temp1);
            temp2 = changeCharacter(temp2);
            temp3 = changeCharacter(temp3);
            temp4 = changeCharacter(temp4);
            printf("--------   --------   --------   --------\n");
            printf("|%2c    |   |%2c    |   |%2c    |   |%2c    |\n", temp1, temp2, temp3, temp4);
            printf("|      |   |      |   |      |   |      |\n");
            printf("|    %2c|   |    %2c|   |    %2c|   |    %2c|\n", temp1, temp2, temp3, temp4);
            printf("--------   --------   --------   --------\n");
            break;

        case 5://Display 5 cards
            temp1 = changeCharacter(temp1);
            temp2 = changeCharacter(temp2);
            temp3 = changeCharacter(temp3);
            temp4 = changeCharacter(temp4);
            temp5 = changeCharacter(temp5);
            printf("--------   --------   --------   --------   --------\n");
            printf("|%2c    |   |%2c    |   |%2c    |   |%2c    |   |%2c    |\n", temp1, temp2, temp3, temp4, temp5);
            printf("|      |   |      |   |      |   |      |   |      |\n");
            printf("|    %2c|   |    %2c|   |    %2c|   |    %2c|   |    %2c|\n", temp1, temp2, temp3, temp4, temp5);
            printf("--------   --------   --------   --------   --------\n");
            break;
    }
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


char askHitOrStand(struct handInfo *player) {
    char answer;
    int check = 1;
    while (check) {
        if (answer != '\n') {
            printf("Do you want to hit(h) or stand(s)?\n");
            scanf("%s", &answer);
            if ((tolower(answer) == 'h') || (tolower(answer) == 's')) {
                return answer;
            } else {
                printf("Please choose 'h' for Hit or 's' for Stand\n");
            }
        }
        check = 1;
    }
}


int isPlayerWin(struct handInfo *player, struct handInfo *dealer) {
    if (((getPoint(player) > getPoint(dealer)) && isBust(player) == 0) || //Player is higher than Dealer
        ((isBust(player) == 0) && (isBust(dealer) == 1)) || //Dealer busts
        ((isBlackJack(player) == 1) && (isBlackJack(dealer) == 0))) { //Player get blackjack

        return 1; //For win

    } else if (((getPoint(player) < getPoint(dealer)) && isBust(dealer) == 0) || //Player is lower than Dealer
               ((isBust(player) == 1) && (isBust(dealer) == 0)) || //Player busts
               (isBlackJack(player) == 0 && (isBlackJack(dealer) == 1))) { //Dealer get blackjack

        return 0; //For lose

    } else if ((getPoint(player) == getPoint(dealer)) || //Player is equal to Dealer
               ((isBust(player) == 1) && (isBust(dealer) == 1)) || //Both player and dealer bust
               ((isBlackJack(player) == 1) && (isBlackJack(dealer) == 1))) { //Both player and dealer get blackjack

        return 2; //For Push

    } else {
        printf("This is exception. Fix this!");
        return 3; //exception
    }
}

void printWinner(struct handInfo *player, struct handInfo *dealer) {
    int newMoney = 0;
    if (isPlayerWin(player, dealer) == 1) { //Player win
        printf("\n\t-->>YOU WIN!<<--\n Your wager is doubled!\n\n");
        newMoney = getBetMoney(player) * 2 + getTotalMoney(player); //if win, double the bet and add to totalMoney
    } else if (isPlayerWin(player, dealer) == 0) { //Player lose
        printf("\n\t-->>YOU LOSE!<<--\n You lose your wager. Good luck next time!\n\n");
        newMoney = getTotalMoney(player) - getBetMoney(player); //if lose, total money subtract the bet
    } else if (isPlayerWin(player, dealer) == 2) { //Push
        printf("\n\t-->>PUSH! NO WINNER.<<--\n You will get your wager back.\n\n");
        newMoney = getTotalMoney(player); //if push, do not change the total money
    } else {
        printf("This is exception. Fix this!");
    }
    printf("\tPLAYER TOTAL MONEY: $%d\n\n", newMoney);
    setTotalMoney(newMoney, player); //Change the value of total money
}

char askPlayAgain(struct handInfo *player) {
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

    return answer;
//    switch (answer) {
//        case 1:
//            return 1;
//        case 2:
//            return 2;
//        case 3:
//            return 3;
//    }
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
    printf("\n     Because you are competing against the dealer, and dealer is also a player. You must beat his hand.");
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

