//
// Created by Sam on 30-Apr-17.
//

//#include "blackjack.h"

#ifndef BLACKJACKGAME_PLAYER_H
#define BLACKJACKGAME_PLAYER_H

/**
 * A hand is a player
 * NOTE: dealer is also a hand (or in other words, dealer is also a player, but dealer
 *           is an AI player). And the word "player" is consider as a real person.
 */

/**
 * Hand (players) struct
 */
struct handInfo {
    int totalMoney; /**< total money of hand*/
    int betMoney; /**< bet money of hand*/
    int firstCard; /**< first card of hand*/
    int secondCard; /**< second card of hand*/
    int thirdCard; /**< third card of hand*/
    int fourthCard; /**< fourth card of hand*/
    int fifthCard; /**< fifth card of hand*/
};

/**
 * Create a new hand.
 * Will allocated on heap.
 * @return A pointer to new created hand. It will return NULL if any call to malloc inside
 *                                          return NULL.
 */
struct handInfo *createHand();

/**
 * Free the memory used by a hand.
 * @param hand a pointer to the hand to free
 */
void freeHand(struct handInfo *hand);

//For player only

/**
 * Display message and ask how much money that player want to play to day (total money).
 * @param player a pointer to a player.
 */
void askMoney(struct handInfo *player);

/**
 * Get total money of a player.
 * @param player a pointer to a player.
 * @return total money of player.
 */
int getTotalMoney(struct handInfo *player);

/**
 * Set total money of player to newMoney.
 * @param newMoney a new value of total money.
 * @param player a pointer to a player that want to set newMoney.
 */
void setTotalMoney(int newMoney, struct handInfo *player);

/**
 * Ask a player how much money the player want to bet
 * @param player a pointer to a player.
 */
void askBetMoney(struct handInfo *player);

/**
 * Get bet money from player (hand).
 * @param player a pointer to a player.
 * @return
 */
int getBetMoney(struct handInfo *player);

//For both player and dealer

/**
 * Set all cards of a hand to 0 for a new game.
 * @param hand a pointer to a hand.
 */
void setHandForNewGame(struct handInfo *hand);

/**
 * A hand get first card randomly in deck
 * @param hand a pointer to a hand.
 * @param deck a deck to get a random card from.
 */
void getFirstCard(struct handInfo *hand, int *deck);

/**
 * A hand get second card randomly in deck
 * @param hand a pointer to a hand.
 * @param deck a deck to get a random card from.
 */
void getSecondCard(struct handInfo *hand, int *deck);

/**
 * A hand get next card (the third, fourth, or the fifth card) randomly in deck
 * @param hand a pointer to a hand.
 * @param deck a deck to get a random card from.
 * @param countCard a variable to count the number
 */
void getNextCard(struct handInfo *hand, int *deck, int countCard);

/**
 * Adjust the value of Jack, Queen, and King card(s) (if a hand has) to value 10
 * @param hand a pointer to a hand to adjust card.
 */
void adjustValueOfCard(struct handInfo *hand);

/**
 * Get total point from total cards of hand
 * @param hand a pointer to a hand
 * @return the total point
 */
int getPoint(struct handInfo *hand);

/**
 * Check if a hand is blackjack or not
 * @param hand a pointer to a hand
 * @return 1 if hand is blackjack, and 0 if hand is not
 */
int isBlackJack(struct handInfo *hand);

/**
 * Check if a hand busts or not
 * @param hand a pointer to a hand
 * @return 1 if hand busts, and 0 if hand is not
 */
int isBust(struct handInfo *hand);


#endif //BLACKJACKGAME_PLAYER_H
