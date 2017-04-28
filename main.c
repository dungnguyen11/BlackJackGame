#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include "blackjack.h"
#include "blackjack.c"

int main() {
    srand(time(NULL));
    struct playerInfo * player1 = createPlayer();
    displayTitle();
//    askInfoPlayer(player1);
    playerGetFirstCard(player1);
    sleep(1);
    playerGetSecondCard(player1);


}