/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/12/19
 * Description:	Unit tests for mineAct function
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

  int i, result;
  int seed = 1000;
  int numPlayer = 3;
  int player1 = 0;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int handCount = 5;
  int hand[handCount];
  int minePos = 0; // Position in hand
  int copperPos, estatePos;
  int discardTest, handTest;
  struct gameState G; //, preG;
 
  PutSeed(seed);

  // Fill hand 
  hand[minePos] = mine;
  for (i = 1; i < handCount; i++) {
    hand[i] = copper;
  }
  
   
//--------------------------------------------
// Test trashing copper for silver
//--------------------------------------------
  printf ("\nTesting Mine, 4 Coppers in hand, trashing 1, gaining Silver\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  copperPos = 4;
  // Call the function being tested; 
  result = playCard(minePos, copperPos, silver, 0, &G);

  printf("Function did not exit with -1\n");
  asserttrue(result != -1);

  printf("Testing that there are 4 - 1 = 3 coppers in hand:\n");
  handTest = 0;
  for(i = 0; i < G.handCount[player1]; i++) {
    if(G.hand[player1][i] == copper) {handTest++;}
  }
  if(!asserttrue(handTest == 3)) {
    printf("(%d Copper(s) in hand)\n", handTest);
  }
 
  printf("Testing that hand gained 1 silver:\n");
  handTest = 0;
  for(i = 0; i < G.handCount[player1]; i++) {
    if(G.hand[player1][i] == silver) {handTest++;}
  }
  if(!asserttrue(handTest ==  1)) {
    printf("(%d Silver(s) in hand)\n", handTest);
  } 

  printf("Testing that player1 hand count is 5 - 1 - 1 + 1 = 4:\n");
  if(!asserttrue(G.handCount[player1] == 4)) {
    printf("(hand count is %d)\n", G.handCount[player1]);
  }

  printf("Testing that player1 discard count is 1:\n");
  if(!asserttrue(G.discardCount[player1] == 1)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that 1 Mine is in discard pile:\n");
  discardTest = 0;
  for (i = 0; i < G.discardCount[player1]; i++) {
    // Is there an minion in the discard?
    if (G.discard[player1][i] == mine) {discardTest++;}
  }
  asserttrue(discardTest == 1);

  printf("Testing that Silver supply is 40 - 1 = 39:\n");
  if(!asserttrue(G.supplyCount[silver] == 39)) {
    printf("(silver supply is %d)\n", G.supplyCount[silver]);
  }

  // Fill hand 
  hand[minePos] = mine;
  hand[1] = estate;
  hand[2] = copper;
  hand[3] = copper;
  hand[4] = copper;

//--------------------------------------------
// Test trashing estate for silver
//--------------------------------------------
  printf ("\nTesting Mine, trashing 1 estate, gaining 1 silver:\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  estatePos = 1;
  // Call the function being tested; 
  result = playCard(minePos, estatePos, silver, 0, &G);
  
  printf ("Testing that the function detects invalid input, returning -1:\n");
  asserttrue(result == -1);

//--------------------------------------------
// Test trashing copper for estate
//--------------------------------------------
  printf ("\nTesting Mine, trashing 1 copper, gaining 1 estate:\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  copperPos = 4;
  // Call the function being tested; 
  result = playCard(minePos, copperPos, estate, 0, &G);
  
  printf ("Testing that the function detects invalid input, returning -1:\n");
  asserttrue(result == -1);


//--------------------------------------------
// Test trashing copper for gold
//--------------------------------------------
  printf ("\nTesting Mine, trashing 1 copper, gaining 1 gold:\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  // Copy hand
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);

  copperPos = 4;
  // Call the function being tested; 
  result = playCard(minePos, copperPos, gold, 0, &G);
  
  printf ("Testing that the function detects invalid input, returning -1:\n");
  asserttrue(result == -1);


//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
