/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/11/19
 * Description:	Unit tests for ambassadorAct function
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
  int player3 = 2;
  int k[10] = {minion, ambassador, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int handCount = 5;
  int hand[handCount];
  int ambassPos = 0; // Baron position in hand
  int cursePos = 1;
  int choice2, result, discardTest;
  struct gameState G; //, preG;
 
  PutSeed(seed);

  // Fill hand with minions
  printf("Setting Hand:\n");
  hand[0] = ambassador;
  printf("Card 0: %d\n", hand[0]);
  for (i = 1; i < handCount; i++){
    hand[i] = curse;
    printf("Card %d: %d\n", i, hand[i]);
  }
   
//--------------------------------------------
// Test return 2 curses choice
//--------------------------------------------
  printf ("\nTesting Ambassador: choosing return 2 Curses\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  // Call the function being tested; 
  choice2 = 2; // return 2 cards
  playCard(ambassPos, cursePos, choice2, 0, &G);

  printf("Testing that player1 hand size is 5 - 1 - 2 = 2:\n");
  if(!asserttrue(G.handCount[player1] == 2)) {
    printf("(hand size is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }
 
  printf("Testing that curse supply is 20 + 2 - 2 = 20:\n");
  if(!asserttrue(G.supplyCount[curse] == 20)) {
    printf("(supply count is %d)\n", G.supplyCount[curse]);
  }

  printf("Testing that Curse was gained to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == 0) {discardTest++;}
  }
  asserttrue(discardTest == 1);

  printf("Testing that Curse was gained to player3 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player3]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player3][i] == 0) {discardTest++;}
  }
  asserttrue(discardTest == 1);
   
//--------------------------------------------
// Test return 1 curse choice
//--------------------------------------------
  printf ("\nTesting Ambassador: choosing return 1 Curse\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  // Call the function being tested; 
  choice2 = 1; // return 1 card
  playCard(ambassPos, cursePos, choice2, 0, &G);

  printf("Testing that player1 hand size is 5 - 1 - 1 = 3:\n");
  if(!asserttrue(G.handCount[player1] == 3)) {
    printf("(hand size is %d)\n", G.handCount[player1]);
  }
 
  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that curse supply is 20 + 1 - 2 = 19:\n");
  if(!asserttrue(G.supplyCount[curse] == 19)) {
    printf("(supply count is %d)\n", G.supplyCount[curse]);
  }

  printf("Testing that Curse was gained to player2 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player2]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player2][i] == 0) {discardTest++;}
  }
  asserttrue(discardTest == 1);

  printf("Testing that Curse was gained to player3 discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player3]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player3][i] == 0) {discardTest++;}
  }
  asserttrue(discardTest == 1);

   
//--------------------------------------------
// Test return -30 curse choice
//--------------------------------------------
  printf ("\nTesting Ambassador: choosing return -30 Curses\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  // Call the function being tested; 
  choice2 = -30; // return -30 card
  result = playCard(ambassPos, cursePos, choice2, 0, &G);

  printf("Testing that function returns -1:\n");
  asserttrue(result == -1);

   
//--------------------------------------------
// Test return +30 curse choice
//--------------------------------------------
  printf ("\nTesting Ambassador: choosing return +30 Curses\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  // Call the function being tested; 
  choice2 = 30; // return 30 cards
  result = playCard(ambassPos, cursePos, choice2, 0, &G);

  printf("Testing that function returns -1:\n");
  asserttrue(result == -1);


//--------------------------------------------
// Test return played ambassador
//--------------------------------------------
  printf ("\nTesting Ambassador: choosing return played card\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  // Call the function being tested; 
  choice2 = 2; // return 2 cards
  result = playCard(ambassPos, ambassPos, choice2, 0, &G);

  printf("Testing that function returns -1:\n");
  asserttrue(result == -1);


//--------------------------------------------
// Test return 2 curses but only have 1
//--------------------------------------------
  printf ("\nTesting Ambassador: choosing 2 curses with only 1\n");
  // Only leave curse at position 1
  for (i = 2; i < handCount; i++){
    hand[i] = ambassador;
  }
 
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  // Call the function being tested; 
  choice2 = 2; // return 2 cards
  result = playCard(ambassPos, cursePos, choice2, 0, &G);

  printf("Testing that function returns -1:\n");
  asserttrue(result == -1);



//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
