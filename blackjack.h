//
// Created by Sam on 28-Apr-17.
//

#include "Hand.h"

#ifndef BLACKJACKGAME_BLACKJACK_H
#define BLACKJACKGAME_BLACKJACK_H

/**
 * Display welcome message to player.
 */
void displayTitle();

/**
 * Play function let player and dealer start playing.
 * @param player a pointer to a player.
 * @param dealer a pointer to a dealer.
 * @param deck a deck to get card from.
 */
void play(struct handInfo *player, struct handInfo *dealer, int *deck);

/**
 * Player get first 2 cards, and dealer get first card.
 * @param player a pointer to a player.
 * @param dealer a pointer to a dealer.
 * @param deck a deck to get card from.
 */
void initCards(struct handInfo *player, struct handInfo *dealer, int *deck);

/**
 * Check if a card is already drew or not.
 * @param card a card value.
 * @param deck a deck to check inside.
 * @return 1 if the card is not drew, and 0 if the card is already drew.
 */
int checkCardIfAvailable(int card, int *deck);

/**
 * Get a random card from deck.
 * @param deck a deck to get a card from.
 * @return the card.
 */
int getCard(int *deck);

/**
 * Change the value of card to Ascii code value to display.
 * @param card a card to change value.
 * @return a Ascii value of the card.
 */
int changeCharacter(int card);

/**
 * Display all the drawn card of a hand.
 * @param hand a pointer to a hand.
 */
void displayManyCards(struct handInfo *hand);

/**
 * Ask player to hit or stand.
 * @return character 'h' if player hits, and character 's' if player stands.
 */
char askHitOrStand();

/**
 * Check if the player (a person) win or not.
 * @param player a pointer to a player.
 * @param dealer a pointer to a dealer.
 * @return 0 if player lose, 1 if player win, and 2 if player and dealer push.
 */
int isPlayerWin(struct handInfo *player, struct handInfo *dealer);

/**
 * Print who is winner of a play.
 * @param player a pointer to a player.
 * @param dealer a pointer to a dealer.
 */
void printWinner(struct handInfo *player, struct handInfo *dealer);

/**
 * Ask player to continue play or not
 * @param player a pointer to a player.
 * @return character 'y' if player continue playing, and character 'n' if player stops
 */
char askPlayAgain(struct handInfo *player);

/**
 * Flush all junk character after an input from player.
 */
void clear();

/**
 * Display Menu for player to select.
 * @return the number of action that player choose from menu.
 */
int displayAskMenu();

/**
 * Display all the rules of this Blackjack game.
 */
void displayRules();

/**
 * Display credits.
 */
void displayCredits();

#endif //BLACKJACKGAME_BLACKJACK_H
