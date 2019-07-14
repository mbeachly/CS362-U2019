/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/13/19
 * Description:	Unit tests for initializeGame() function
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

  int result, numPlayers;
  int seed = 1000;
  int k[10] = {minion, ambassador, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  struct gameState G; //, preG;
 
  PutSeed(seed);
  
   
//--------------------------------------------
// initializeGame: 1 player
//--------------------------------------------
  printf ("\nInitializing Game with 1 player should fail (return -1):\n");
  numPlayers = 1;
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  result = initializeGame(numPlayers, k, seed, &G); // Initialize new game
  if(!asserttrue(result == -1)){ 
    printf("Function did not exit with -1\n");
  }

 
//--------------------------------------------
// initializeGame: 7 players
//--------------------------------------------
  printf ("\nInitializing Game with 7 players should fail:\n");
  numPlayers = 7;
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  result = initializeGame(numPlayers, k, seed, &G); // Initialize new game
  if(!asserttrue(result == -1)){ 
    printf("Function did not exit with -1\n");
  }

    
//--------------------------------------------
// initializeGame: 2 player, duplicate kingdom cards
//--------------------------------------------
  printf ("\nInitializing Game with duplicate kingdom cards should fail:\n");
  int kBad[10] = {minion, minion, tribute, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  numPlayers = 2;
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  result = initializeGame(numPlayers, kBad, seed, &G); // Initialize new game
  if(!asserttrue(result == -1)){ 
    printf("Function did not exit with -1\n");
  }


//--------------------------------------------
// initializeGame: 2 players
//--------------------------------------------
  printf ("\nInitializing Game with 2 players\n"); 
  numPlayers = 2;
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  result = initializeGame(numPlayers, k, seed, &G); // Initialize new game
  printf("Testing that function does NOT return error code:\n");
  if(!asserttrue(result != -1)){ 
    printf("Function exited with -1\n");
  }

  printf("Testing curse supply = 10:\n");
  if(!asserttrue(G.supplyCount[curse] == 10)){
    printf("(supply = %d)\n", G.supplyCount[curse]);
  }

  printf("Testing estate supply = 8:\n");
  if(!asserttrue(G.supplyCount[estate] == 8)){
    printf("(supply = %d)\n", G.supplyCount[estate]);
  }

  printf("Testing duchy supply = 8:\n");
  if(!asserttrue(G.supplyCount[duchy] == 8)){
    printf("(supply = %d)\n", G.supplyCount[duchy]);
  }

  printf("Testing province supply = 8:\n");
  if(!asserttrue(G.supplyCount[province] == 8)){
    printf("(supply = %d)\n", G.supplyCount[province]);
  }

  printf("Testing copper supply = 46:\n");
  if(!asserttrue(G.supplyCount[copper] == 46)){
    printf("(supply = %d)\n", G.supplyCount[copper]);
  }

  printf("Testing silver supply = 40:\n");
  if(!asserttrue(G.supplyCount[silver] == 40)){
    printf("(supply = %d)\n", G.supplyCount[silver]);
  }

  printf("Testing gold supply = 30:\n");
  if(!asserttrue(G.supplyCount[gold] == 30)){
    printf("(supply = %d)\n", G.supplyCount[gold]);
  }

  printf("Testing minion supply = 10:\n");
  if(!asserttrue(G.supplyCount[minion] == 10)){
    printf("(supply = %d)\n", G.supplyCount[minion]);
  }

  printf("Testing gardens supply = 8:\n");
  if(!asserttrue(G.supplyCount[gardens] == 8)){
    printf("(supply = %d)\n", G.supplyCount[gardens]);
  }


//--------------------------------------------
// initializeGame: 3 players
//--------------------------------------------
  printf ("\nInitializing Game with 3 players\n"); 
  numPlayers = 3;
  memset(&G, 0, sizeof(struct gameState)); // Clear game state
  result = initializeGame(numPlayers, k, seed, &G); // Initialize new game
  printf("Testing that function does NOT return error code:\n");
  if(!asserttrue(result != -1)){ 
    printf("Function exited with -1\n");
  }

  printf("Testing curse supply = 20:\n");
  if(!asserttrue(G.supplyCount[curse] == 20)){
    printf("(supply = %d)\n", G.supplyCount[curse]);
  }

  printf("Testing estate supply = 12:\n");
  if(!asserttrue(G.supplyCount[estate] == 12)){
    printf("(supply = %d)\n", G.supplyCount[estate]);
  }

  printf("Testing duchy supply = 12:\n");
  if(!asserttrue(G.supplyCount[duchy] == 12)){
    printf("(supply = %d)\n", G.supplyCount[duchy]);
  }

  printf("Testing province supply = 12:\n");
  if(!asserttrue(G.supplyCount[province] == 12)){
    printf("(supply = %d)\n", G.supplyCount[province]);
  }

  printf("Testing copper supply = 46:\n");
  if(!asserttrue(G.supplyCount[copper] == 39)){
    printf("(supply = %d)\n", G.supplyCount[copper]);
  }

  printf("Testing silver supply = 40:\n");
  if(!asserttrue(G.supplyCount[silver] == 40)){
    printf("(supply = %d)\n", G.supplyCount[silver]);
  }

  printf("Testing gold supply = 30:\n");
  if(!asserttrue(G.supplyCount[gold] == 30)){
    printf("(supply = %d)\n", G.supplyCount[gold]);
  }

  printf("Testing minion supply = 10:\n");
  if(!asserttrue(G.supplyCount[minion] == 10)){
    printf("(supply = %d)\n", G.supplyCount[minion]);
  }

  printf("Testing gardens supply = 12:\n");
  if(!asserttrue(G.supplyCount[gardens] == 12)){
    printf("(supply = %d)\n", G.supplyCount[gardens]);
  }


//----------------------------------------------
// Final test results
//----------------------------------------------
  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
