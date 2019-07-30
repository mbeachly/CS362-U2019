/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/13/19
 * Description:	Unit tests for drawCard() function
 *************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Global Variables used by asserttrue function
int testsPassed = 0;
int testsFailed = 0;
 
/***************************************************
 *                   asserttrue
 * Takes: a true (non-0) or false (0) integer input
 * Prints: PASSED if true, FAILED if false
 * Modifies: increments global variables 
 *           testsPassed and testsFailed
 * Returns: 1 for true and 0 for false
 ***************************************************/
int asserttrue(int testResult) {
	if (testResult) {
		printf("PASSED\n");
		testsPassed++;
		return 1;
	}
	else {
		printf("FAILED\n");
		testsFailed++;
		return 0;
	}
}

int main () {

  int numPlayers = 2;
  int player1 = 0;
  int seed = 1000;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G; //, preG;

  PutSeed(seed);        
       
//--------------------------------------------
// Draw card from deck
//--------------------------------------------
  printf ("\nDraw card with 0 cards in hand, 1 card in deck\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.handCount[player1] = 0;
  G.deckCount[player1] = 1;
  G.deck[player1][0] = gold;
  drawCard(player1, &G);

  printf("Hand count = 1\n");
  if(!asserttrue(G.handCount[player1] == 1)) {
    printf("(hand count = %d)\n", G.handCount[player1]);
  } 

  printf("Deck count = 0\n");
  if(!asserttrue(G.deckCount[player1] == 0)) {
    printf("(deck count = %d)\n", G.deckCount[player1]);
  } 

       
//--------------------------------------------
// Draw card from discard (0 cards in deck)
//--------------------------------------------
  printf ("\nDraw card with 0 cards in hand, 0 cards in deck, 1 card in discard\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.handCount[player1] = 0;
  G.deckCount[player1] = 0;
  G.discardCount[player1] = 1;
  G.discard[player1][0] = gold;
  drawCard(player1, &G);

  printf("Hand count = 1\n");
  if(!asserttrue(G.handCount[player1] == 1)) {
    printf("(hand count = %d)\n", G.handCount[player1]);
  } 

  printf("Deck count = 0\n");
  if(!asserttrue(G.deckCount[player1] == 0)) {
    printf("(deck count = %d)\n", G.deckCount[player1]);
  } 

  printf("Discard count = 0\n");
  if(!asserttrue(G.discardCount[player1] == 0)) {
    printf("(discard count = %d)\n", G.discardCount[player1]);
  } 

   
//--------------------------------------------
// Draw card with 0 cards in deck or discard
//--------------------------------------------
  printf ("\nDraw card with 0 cards in hand, 0 cards in deck, 0 cards in discard\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.handCount[player1] = 0;
  G.discardCount[player1] = 0;
  G.deckCount[player1] = 0;
  drawCard(player1, &G);

  printf("Hand count = 0\n");
  if(!asserttrue(G.handCount[player1] == 0)) {
    printf("(hand count = %d)\n", G.handCount[player1]);
  } 

  printf("Deck count = 0\n");
  if(!asserttrue(G.deckCount[player1] == 0)) {
    printf("(deck count = %d)\n", G.deckCount[player1]);
  } 

  printf("Discard count = 0\n");
  if(!asserttrue(G.discardCount[player1] == 0)) {
    printf("(discard count = %d)\n", G.discardCount[player1]);
  } 


//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
