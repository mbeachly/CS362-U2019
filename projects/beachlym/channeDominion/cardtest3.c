/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/13/19
 * Description:	Unit tests for endTurn() function
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
  int player2 = 1;
  int seed = 1000;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int discard[3] = {silver, silver, mine};
  int hand[3] = {estate, curse, copper};
  struct gameState G; //, preG;
 
  PutSeed(seed);
  
     
//--------------------------------------------
// player1
//--------------------------------------------
  printf ("\nEnding player1 turn with 3 cards in hand and 3 cards in discard\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.discardCount[player1] = 3;
  memcpy(G.discard[player1], discard, sizeof(int) * 3);
  G.handCount[player1] = 3;
  memcpy(G.hand[player1], hand, sizeof(int) * 3);
  G.coins = 1;

  endTurn(&G);

  printf("Check that current player is player 2:\n");
  asserttrue(G.whoseTurn == 1);

  printf("Check that player1 hand has 5 cards:\n");
  if(!asserttrue(G.handCount[player1] == 5)) {
    printf("(%d cards in hand)\n", G.handCount[player1]);
  }

  printf("Check that player1 discard has 6 cards:\n");
  asserttrue(G.discardCount[player1] == 6);

  printf("Check that player1 deck has 0 cards:\n");
  if(!asserttrue(G.deckCount[player1] == 0)) {
    printf("(%d cards in deck)\n", G.deckCount[player1]);
  }
     
//--------------------------------------------
// player2
//--------------------------------------------
  printf ("\nEnding player2 turn with 3 cards in hand and 3 cards in discard\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.discardCount[player2] = 3;
  memcpy(G.discard[player2], discard, sizeof(int) * 3);
  G.handCount[player2] = 3;
  memcpy(G.hand[player2], hand, sizeof(int) * 3);
  G.coins = 1;
  G.whoseTurn = player2;

  endTurn(&G);

  printf("Check that current player is player 1:\n");
  asserttrue(G.whoseTurn == 0);

  printf("Check that player2 hand has 5 cards:\n");
  if(!asserttrue(G.handCount[player2] == 5)) {
    printf("(%d cards in hand)\n", G.handCount[player2]);
  }

  printf("Check that player2 discard has 6 cards:\n");
  asserttrue(G.discardCount[player2] == 6);

  printf("Check that player2 deck has 5 cards:\n");
  if(!asserttrue(G.deckCount[player2] == 5)) {
    printf("(%d cards in deck)\n", G.deckCount[player2]);
  }


//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
