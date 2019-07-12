/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/10/19
 * Description:	Unit tests for minionAct function
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

  int i;
  int seed = 1000;
  int numPlayer = 4;
  int player1 = 0;
  int player2 = 1;
  int player3 = 2;
  int player4 = 3;
  int k[10] = {minion, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int handCount = 5;
  int hand[handCount];
  int minionPos = 0; // Baron position in hand
  int choice = 1;
  int discardTest;
  struct gameState G; //, preG;
 
  PutSeed(seed);

  // Fill hand with minions
  printf("Setting Hand:\n");
  for (i = 0; i < handCount; i++){
    hand[i] = minion;
    printf("Card %d: %d\n", i, hand[i]);
  }
   
//--------------------------------------------
// Test +2 coins choice
//--------------------------------------------
  printf ("\nTesting Minion: choosing +2 coins\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand with minion card
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
  // Save the previous game state before testing function
  //memcpy(&preG, &G, sizeof(struct gameState));

  // Call the function being tested; 
  playCard(minionPos, choice, 0, 0, &G);

  printf("Testing that player1 hand size is 4:\n");
  if(!asserttrue(G.handCount[player1]==4)) {
    printf("(hand size is %d)\n", G.handCount[player1]);
  }

  printf("Testing that Minion was discarded to player1's discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player1]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player1][i] == 17) {discardTest++;}
  }
  asserttrue(discardTest);

  printf("Testing that discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player1 received 2 coins:\n");
  if (!asserttrue(G.coins == 2)) {
    printf("(received %d coins)\n", G.coins);
  }
   
//--------------------------------------------
// Test discard hand choice
//--------------------------------------------
  printf ("\nTesting Minion: choosing discard hand and draw 4\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  G.handCount[player2] = 5;
  G.handCount[player3] = 5;
  G.handCount[player4] = 4;
 // Copy hand with minion card
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
  memcpy(G.hand[player2], hand, sizeof(int) * handCount);
  // Save the previous game state before testing function
  //memcpy(&preG, &G, sizeof(struct gameState));

  // Call the function being tested; 
  playCard(minionPos, 0, choice, 0, &G);

  printf("Testing that Minion was discarded to player1's discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player1]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player1][i] == 17) {discardTest++;}
  }
  asserttrue(discardTest);

  printf("Testing that player1 hand size is 4:\n");
  if(!asserttrue(G.handCount[player1]==4)) {
    printf("(hand size is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 5:\n");
  if(!asserttrue(G.discardCount[player1] == 5)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player1 received 0 coins:\n");
  if (!asserttrue(G.coins == 0)) {
    printf("(received %d coins)\n", G.coins);
  }

  printf("Testing that player2 hand size is 4:\n");
  if(!asserttrue(G.handCount[player2]==4)) {
    printf("(hand size is %d)\n", G.handCount[player2]);
  }

  printf("Testing that player2 discard count is 5:\n");
  if(!asserttrue(G.discardCount[player2] == 5)) {
    printf("(discard count is %d)\n", G.discardCount[player2]);
  }

  printf("Testing that player3 hand size is 4:\n");
  if(!asserttrue(G.handCount[player3]==4)) {
    printf("(hand size is %d)\n", G.handCount[player3]);
  }

  printf("Testing that player3 discard count is 5:\n");
  if(!asserttrue(G.discardCount[player3] == 5)) {
    printf("(discard count is %d)\n", G.discardCount[player3]);
  }

  printf("Testing that player4 hand size is 4:\n");
  if(!asserttrue(G.handCount[player4]==4)) {
    printf("(hand size is %d)\n", G.handCount[player4]);
  }

  printf("Testing that player4 discard count is 0:\n");
  if(!asserttrue(G.discardCount[player4] == 0)) {
    printf("(discard count is %d)\n", G.discardCount[player4]);
  }


//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
