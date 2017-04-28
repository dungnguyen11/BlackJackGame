#include <stdio.h>
#include <unistd.h>
#include "blackjack.h"
#include "blackjack.c"

int main() {
    struct playerInfo *player1 = createPlayer();
    struct dealerInfo *dealer1 = createDealer();

    displayTitle();
    askInfoPlayer(player1);
    setNewDeck(deck);

    char answer;
    int playAgain = 1;

    while (playAgain) {
//        srand(time(NULL));

        playerGetFirstCard(player1);
        sleep(1);
        //TODO: Second card get incorrectly
        playerGetSecondCard(player1);
        sleep(1);
        dealerGetFirstCard(dealer1);
        sleep(1);
        dealerGetSecondCard(dealer1);

        printf("Player: %d %d\n", player1->firstCard, player1->secondCard);
        printf("Player: %d %d\n", dealer1->firstCard, dealer1->secondCard);
        int length = sizeof(deck) / sizeof(int);
        for (int i = 0; i < length; ++i) {
            printf("Array %d : %d\n", i, deck[i]);
        }

        //Ask player if he/she want to play more
        while (playAgain) {
            printf("Do you want to play again?(y/n)\n");
            scanf("%c", &answer);

            if (answer == 'y') {
                break; //Continue the loop
            } else if (answer == 'n') {
                printf("inside no");
                playAgain = 0; //Change playAgain value to end while loop
            }

        }

    }



}