/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/13/19
 * Description:	Unit tests for getWinners() function
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

  int numPlayers = 3;
  int players[3];
  int player1 = 0;
  int player2 = 1;
  int player3 = 2;
  int seed = 1000;
  int handCount = 1;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G; //, preG;

  PutSeed(seed);        
       
//--------------------------------------------
// player1
//--------------------------------------------
  printf ("\n3 players tied, calling getWinners on player1 turn\n");
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.whoseTurn = player1;
  G.handCount[player1] = handCount;
  G.hand[player1][0] = estate;
  G.handCount[player2] = handCount;
  G.hand[player2][0] = estate;
  G.handCount[player3] = handCount;
  G.hand[player3][0] = estate;

  getWinners(players, &G);

  printf("Check that player1 is not winner:\n");
  if(!asserttrue(players[player1] == 0)) {
    printf("(player1 score = %d)\n", scoreFor(player1, &G));
  } 

  printf("Check that player2 is a winner:\n");
  if(!asserttrue(players[player2] == 1)) {
    printf("(player2 score = %d)\n", scoreFor(player2, &G));
  } 

  printf("Check that player3 is a winner:\n");
  if(!asserttrue(players[player3] == 1)) {
    printf("(player3 score = %d)\n", scoreFor(player3, &G));
  } 



         
//--------------------------------------------
// player2
//--------------------------------------------
  printf ("\n3 players tied, calling getWinners on player2 turn\n");
  //memset(&G, 0, sizeof(struct gameState)); // Clear game state
  //initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.whoseTurn = player2;
  
  getWinners(players, &G);

  printf("Check that player1 is not winner:\n");
  if(!asserttrue(players[player1] == 0)) {
    printf("(player1 score = %d)\n", scoreFor(player1, &G));
  } 

  printf("Check that player2 is not winner:\n");
  if(!asserttrue(players[player2] == 0)) {
    printf("(player2 score = %d)\n", scoreFor(player2, &G));
  } 

  printf("Check that player3 is a winner:\n");
  if(!asserttrue(players[player3] == 1)) {
    printf("(player3 score = %d)\n", scoreFor(player3, &G));
  } 

 
//--------------------------------------------
// player3
//--------------------------------------------
  printf ("\n3 players, player3 has most victory cards\n");
  //memset(&G, 0, sizeof(struct gameState)); // Clear game state
  //initializeGame(numPlayers, k, seed, &G); // Initialize new game
  G.whoseTurn = player1;
  G.hand[player3][0] = province;
  
  getWinners(players, &G);

  printf("Check that player1 is not winner:\n");
  if(!asserttrue(players[player1] == 0)) {
    printf("(player1 score = %d)\n", scoreFor(player1, &G));
  } 

  printf("Check that player2 is not winner:\n");
  if(!asserttrue(players[player2] == 0)) {
    printf("(player2 score = %d)\n", scoreFor(player2, &G));
  } 

  printf("Check that player3 is a winner:\n");
  if(!asserttrue(players[player3] == 1)) {
    printf("(player3 score = %d)\n", scoreFor(player3, &G));
  } 

//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
