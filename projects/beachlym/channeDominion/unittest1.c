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

  int i, j;
  int seed = 1000;
  int numPlayer = 2;
  int player1 = 0;
  int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int handCount = 5;
  int hand[handCount];
  int baronPos = handCount - 1; // Baron position in hand
  int choice1; // 0 = no discard, 1 = discard estate
  int handTest, discardTest;
  struct gameState G; //, preG;
 
  PutSeed(seed);

  // Fill hand with non-estate cards (barons)
  printf("Setting Hand:\n");
  for (i = 0; i < handCount; i++){
    hand[i] = baron;
    printf("Card %d: %d\n", i, hand[i]);
  }
   
//--------------------------------------------
// Test hand with no estate cards
//--------------------------------------------
  for (choice1 = 0; choice1 < 2; choice1++) 
  {
    if (choice1 == 0) {printf("\nTesting Baron with no Estate card in hand: choosing gain\n");}
    else {printf("\nTesting Baron with no Estate card in hand: choosing discard\n");}

    memset(&G, 0, sizeof(struct gameState)); // Clear game state
    initializeGame(numPlayer, k, seed, &G); // Initialize new game
    G.handCount[player1] = handCount; // Set number of cards in hand
    // Copy hand with 1 Estate card
    memcpy(G.hand[player1], hand, sizeof(int) * handCount);
    // Save the previous game state before testing function
    //memcpy(&preG, &G, sizeof(struct gameState));

    // Call the function being tested
    playCard(baronPos, choice1, 0, 0, &G); // 1 for discard

    printf("Testing that player has 2 buys:\n");
    asserttrue(G.numBuys == 2);

    printf("Testing that player hand size is 4:\n");
    if(!asserttrue(G.handCount[player1]==4)) {
      printf("(player hand size is %d)\n", G.handCount[player1]);
    }

    printf("Testing that no Estate is in hand:\n");
    handTest = -1;
    for (j = 0; j < G.handCount[player1]; j++) {
      // Is there still an estate card in hand?
      if (G.hand[player1][j] == estate) {handTest = j;}
    }
    if (!asserttrue(handTest == -1)){
      printf("(Estate is in hand at position %d)\n", handTest);
    }

    printf("Testing that Estate was gained to player's discard pile:\n");
    discardTest = 0;
    for (j = 0; j < G.discardCount[player1]; j++) {
      // Is there an estate in the discard?
      if (G.discard[player1][j] == estate) {discardTest++;}
    }
    asserttrue(discardTest);

    printf("Testing that discard count is 2:\n");
    if(!asserttrue(G.discardCount[player1] == 2)) {
      printf("(discard count is %d)\n", G.discardCount[player1]);
    }

    printf("Testing that player received 0 coins:\n");
    if (!asserttrue(G.coins == 0)) {
      printf("(player received %d coins)\n", G.coins);
    }
  }

 
//--------------------------------------------
// Test one estate card at each hand position
//--------------------------------------------
  for (i = 0; i < handCount; i++) {
   printf ("\nTesting Baron with one Estate card at hand position %d\n", i);
   hand[i] = estate; // 1 = estate card
    if (i > 0) { // Remove previous estate card
      hand[i-1] = baron; // 15 = baron
    }

    memset(&G, 0, sizeof(struct gameState)); // Clear game state
    initializeGame(numPlayer, k, seed, &G); // Initialize new game
    G.handCount[player1] = handCount; // Set number of cards in hand
    // Copy hand with 1 Estate card
    memcpy(G.hand[player1], hand, sizeof(int) * handCount);
    // Save the previous game state before testing function
    //memcpy(&preG, &G, sizeof(struct gameState));

    if (i == baronPos) {baronPos = 0;}
    // Call the function being tested
    choice1 = 1; // Discard estate
    playCard(baronPos, choice1, 0, 0, &G);

    printf("Testing that player has 2 buys:\n");
    asserttrue(G.numBuys == 2);

    printf("Testing that player hand size is 3:\n");
    if(!asserttrue(G.handCount[player1]==3)) {
      printf("(player hand size is %d)\n", G.handCount[player1]);
    }

    printf("Testing that Estate is no longer in hand:\n");
    handTest = -1;
    for (j = 0; j < G.handCount[player1]; j++) {
      // Is there still an estate card in hand?
      if (G.hand[player1][j] == 1) {handTest = j;}
    }
    if (!asserttrue(handTest == -1)){
      printf("(Estate is still in hand at position %d)\n", handTest);
    }

    printf("Testing that Estate is in player's discard pile:\n");
    discardTest = -1;
    for (j = 0; j < G.discardCount[player1]; j++) {
      // Is there an estate in the discard?
      if (G.discard[player1][j] == 1) {discardTest = j;}
    }
    asserttrue(discardTest != -1);

    printf("Testing that discard count is 2:\n");
    if(!asserttrue(G.discardCount[player1] == 2)) {
      printf("(discard count is %d)\n", G.discardCount[player1]);
    }

    printf("Testing that player received 4 coins:\n");
    if (!asserttrue(G.coins == 4)) {
      printf("(player received %d coins)\n", G.coins);
    }
  }
   
//--------------------------------------------
// Test hand with two estate cards
//--------------------------------------------
  printf ("\nTesting Baron with two Estate cards in hand\n");

  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayer, k, seed, &G); // Initialize new game
  G.handCount[player1] = handCount; // Set number of cards in hand
  hand[3] = estate; // Positions 3 and 4 should have estate
 // Copy hand with 1 Estate card
  memcpy(G.hand[player1], hand, sizeof(int) * handCount);
  // Save the previous game state before testing function
  //memcpy(&preG, &G, sizeof(struct gameState));

  // Call the function being tested
  //baronAct(0, &G);
  baronPos = choice1 = 1; 
  playCard(baronPos, choice1, 0, 0, &G);

  printf("Testing that player has 2 buys:\n");
  asserttrue(G.numBuys == 2);

  printf("Testing that player hand size is 3:\n");
  if(!asserttrue(G.handCount[player1]==3)) {
    printf("(player hand size is %d)\n", G.handCount[player1]);
  }

  printf("Testing that 1 Estate is in hand:\n");
  handTest = 0;
  for (j = 0; j < G.handCount[player1]; j++) {
    // Is there still an estate card in hand?
    if (G.hand[player1][j] == 1) {handTest++;}
  }
  if (!asserttrue(handTest == 1)){
    printf("(%d Estate card(s) in hand)\n", handTest);
  }

  printf("Testing that Estate was discarded to player's discard pile:\n");
  discardTest = 0;
  for (j = 0; j < G.discardCount[player1]; j++) {
    // Is there an estate in the discard?
    if (G.discard[player1][j] == 1) {discardTest++;}
  }
  asserttrue(discardTest);

  printf("Testing that discard count is 2:\n");
  if(!asserttrue(G.discardCount[player1] == 2)) {
    printf("(discard count is %d)\n", G.discardCount[player1]);
  }

  printf("Testing that player received 4 coins:\n");
  if (!asserttrue(G.coins == 4)) {
    printf("(player received %d coins)\n", G.coins);
  }


  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
