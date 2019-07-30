/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/12/19
 * Description:	Unit tests for tributeAct function
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
  int numPlayer = 3;
  int player1 = 0;
  int player2 = 1;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int handCount = 5;
  int hand[handCount];
  int tributePos = 0; // Position in hand
  int discardTest;
  struct gameState G; //, preG;
 
  PutSeed(seed);

  // Fill hand with minions
  printf("Setting Hand:\n");
  hand[0] = tribute;
  printf("Card 0: %d\n", hand[0]);
  for (i = 1; i < handCount; i++){
    hand[i] = curse;
    printf("Card %d: %d\n", i, hand[i]);
  }
   
//--------------------------------------------
// Test 2 coppers
//--------------------------------------------
  printf ("\nTesting Tribute: Next payer's deck has 2 Coppers\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
 
  // Set next player's deck
  G.deckCount[player2] = 2;
  G.deck[player2][0] = copper;
  G.deck[player2][1] = copper;

  // Call the function being tested; 
  playCard(tributePos, 0, 0, 0, &G);

  printf("Testing that player1 gained 2 coins:\n");
  if(!asserttrue(G.coins == 2)) {
    printf("(coins = %d)\n", G.coins);
  }

  printf("Testing that player1 hand count is 4:\n");
  if(!asserttrue(G.handCount[player1] == 4)) {
    printf("(hand count is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player2 discard count is 2:\n");
  if(!asserttrue(G.discardCount[player2] == 2)) {
    printf("(discard count is %d)\n", G.discardCount[player2]);
  }

  printf("Testing that 2 Ccppers were discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == copper) {discardTest++;}
  }
  asserttrue(discardTest == 2);
 
//--------------------------------------------
// Test 1 estate, 1 tribute
//--------------------------------------------
  printf ("\nTesting Tribute: Next payer's deck has 1 Estate and 1 Tribute\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
 
  // Set next player's deck
  G.deckCount[player2] = 2;
  G.deck[player2][0] = estate;
  G.deck[player2][1] = tribute;

  // Call the function being tested; 
  playCard(tributePos, 0, 0, 0, &G);

  printf("Testing that player1 gained 2 actions\n");
  asserttrue(G.numActions == 2);

  printf("Testing that player1 hand count is 5 - 1 + 2 = 6:\n");
  if(!asserttrue(G.handCount[player1] == 6)) {
    printf("(hand count is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player2 discard count is 2:\n");
  if(!asserttrue(G.discardCount[player2] == 2)) {
    printf("(discard count is %d)\n", G.discardCount[player2]);
  }

  printf("Testing that 1 Estate was discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == estate) {discardTest++;}
  }
  asserttrue(discardTest == 1);

  printf("Testing that 1 Tribute was discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == tribute) {discardTest++;}
  }
  asserttrue(discardTest == 1);

 
//--------------------------------------------
// Test 1 estate, 1 tribute in discard
//--------------------------------------------
  printf ("\nTesting Tribute: Next payer's discard pile has 1 Estate and 1 Tribute\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
 
  // Set next player's deck
  G.discardCount[player2] = 2;
  G.discard[player2][0] = estate;
  G.discard[player2][1] = tribute;

  // Call the function being tested; 
  playCard(tributePos, 0, 0, 0, &G);

  printf("Testing that player1 gained 2 actions\n");
  asserttrue(G.numActions == 2);

  printf("Testing that player1 hand count is 5 - 1 + 2 = 6:\n");
  if(!asserttrue(G.handCount[player1] == 6)) {
    printf("(hand count is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player2 discard count is 2:\n");
  if(!asserttrue(G.discardCount[player2] == 2)) {
    printf("(discard count is %d)\n", G.discardCount[player2]);
  }

  printf("Testing that 1 Estate was discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == estate) {discardTest++;}
  }
  asserttrue(discardTest == 1);

  printf("Testing that 1 Tribute was discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == tribute) {discardTest++;}
  }
  asserttrue(discardTest == 1);
 
//--------------------------------------------
// Test 1 estate in deck, 1 tribute in discard
//--------------------------------------------
  printf ("\nTesting Tribute: Next payer's deck has 1 Estate and discard has 1 Tribute\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
 
  // Set next player's deck
  G.deckCount[player2] = 1;
  G.deck[player2][0] = estate;
  G.discardCount[player2] = 1;
  G.discard[player2][0] = tribute;

  // Call the function being tested; 
  playCard(tributePos, 0, 0, 0, &G);

  printf("Testing that player1 gained 2 actions\n");
  asserttrue(G.numActions == 2);

  printf("Testing that player1 hand count is 5 - 1 + 2 = 6:\n");
  if(!asserttrue(G.handCount[player1] == 6)) {
    printf("(hand count is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player2 discard count is 2:\n");
  if(!asserttrue(G.discardCount[player2] == 2)) {
    printf("(discard count is %d)\n", G.discardCount[player2]);
  }

  printf("Testing that 1 Estate was discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == estate) {discardTest++;}
  }
  asserttrue(discardTest == 1);

  printf("Testing that 1 Tribute was discarded to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == tribute) {discardTest++;}
  }
  asserttrue(discardTest == 1);



//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
