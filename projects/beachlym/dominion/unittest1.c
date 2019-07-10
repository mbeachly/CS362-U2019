/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/9/19
 * Description:	Unit tests for baronAct function
 *************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

// Global Variables
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

  int i, j;
  int seed = 1000;
  int numPlayer = 2;
  int player1 = 0;
  int r;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int handCount = 5;
  int hand[5];
  int handTest = -1;
  struct gameState G, preG;
 
  PutSeed(seed);
  // Fill hand with non-estate cards (0 = curse card)
  memset(hand, 0, handCount * sizeof(int));

  // Test one estate card at each hand position
  for (i = 0; i < handCount; i++) {
   printf ("\nTesting baronAct() with one Estate card at hand position %d\n", i);
   hand[i] = 1; // 1 = estate card
    if (i > 0) { // Remove previous estate card
      hand[i-1] = 0; // curse card
    }

    memset(&G, 0, sizeof(struct gameState)); // Clear game state
    r = initializeGame(numPlayer, k, seed, &G); // Initialize new game
    G.handCount[player1] = handCount; // Set number of cards in hand
    // Copy hand with 1 Estate card
    memcpy(G.hand[player1], hand, sizeof(int) * handCount);
    // Save the previous game state before testing function
    memcpy(&preG, &G, sizeof(struct gameState));

    // Call the function being tested
    baronAct(i, &G); // Try to discard estate card 

    printf("Testing that Estate is no longer in hand:\n");
    for (j = 0; j < handCount; j++) {
      // Is there still an estate card in hand?
      if (G.hand[player1][j] == 1) {handTest = j;}
    }
    if (!asserttrue(handTest == -1)){
      printf("(Estate is still in hand at position %d)\n", handTest);
    }

    printf("Testing that Estate is on player's discard pile:\n");
    asserttrue(G.discard[player1][0] == 1);

    printf("Testing that player received 4 coins:\n");
    if (!asserttrue(G.coins == 4)) {
      printf("(player received %d coins)\n", G.coins);
    }
  }

  if (testsFailed) {printf("\nbaronAct() failed %d tests\n", testsFailed);}
  else {printf("\nbaronAct() passed all %d tests!\n", testsPassed);}

  return 0;
}
