/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/13/19
 * Description:	Unit tests for shuffle() function
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

  int i, result, deckCount, deckTest;
  int numPlayers = 2;
  int player1 = 0;
  int seed = 1000;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G; //, preG;
 
  PutSeed(seed);
  
   
//--------------------------------------------
// shuffle: 0 cards
//--------------------------------------------
  printf ("\nShuffling 0 card deck should fail (return -1):\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  deckCount = 0;
  G.deckCount[player1] = deckCount;
  result = shuffle(player1, &G);
  if(!asserttrue(result == -1)){ 
    printf("Function did not exit with -1\n");
  }

   
//--------------------------------------------
// shuffle: 5 cards
//--------------------------------------------
  printf ("\nShuffling 5 card deck:\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  deckCount = 5;
  G.deckCount[player1] = deckCount;
  int deck[5] = {copper, estate, copper, curse, silver};
  memcpy(G.deck[player1], deck, sizeof(int) * deckCount);

  result = shuffle(player1, &G);
  printf("Shuffle did NOT exit with -1:\n");
  asserttrue(result != -1);

  printf("Check that shuffled deck has same number of cards:\n");
  asserttrue(deckCount == G.deckCount[player1]);

  printf("Check that shuffled deck is NOT in same order:\n");
  deckTest = 0;
  for (i = 1; i < deckCount; i++) {
    if (deck[i] != G.deck[player1][i]) {
      deckTest++;
    }
  }
  asserttrue(deckTest > 0);

  printf("Check that shuffled deck has same number of coppers:\n");
  deckTest = 0;
  for (i = 1; i < deckCount; i++) {
    if (G.deck[player1][i] == copper) {
      deckTest++;
    }
  }
  asserttrue(deckTest == 2);


//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
