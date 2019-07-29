/*************************************************************
 * Author:	Matt Beachly
 * Date:	7/26/19
 * Description:	Random tests for minionAct function
 *************************************************************/

#include "dominion.h"
#include "dominion_helpers.h"
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <math.h>
#include <time.h>
//#include "rngs.h"

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
  int seed = rand();
  int i, test;
  int numPlayer = 2;
  int player1 = 0;
  int player2 = 1;
  int k[10] = {minion, tribute, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};
  int tributePos; // Baron position in hand
  int numHand, numDeck;
  int card, numTreasure, numAction, numVictory;
  int numTest = 500; // How many random tests to run
  struct gameState G, preG;

  // Run random tests
  for (test = 0; test < numTest; test++){
//-------------------------------------------
// Set up random hand and action choice
//-------------------------------------------
    // Initialize game
    memset(&G, 0, sizeof(struct gameState)); // Clear game state
    initializeGame(numPlayer, k, seed, &G); // Initialize new game
   
    // Randomly select player1 hand
    numHand = (rand() % 5) + 1;
    G.handCount[player1] = numHand;
    tributePos = rand() % numHand;
    G.hand[tributePos][i] = tribute;
     
    // Randomly select player 1 deck
    G.deckCount[player1] = rand() % 5;
    printf("Setting Player2 Discard, %d card(s)\n", G.deckCount[player1]);


    // Randomly select player 2 deck
    numDeck = rand() % 5;
    G.deckCount[player2] = numDeck;
    printf("Setting Player2 Deck, %d card(s):", numDeck);
    for (i = 0; i < numDeck; i++){
      // Randomly select cards in hand (there are 27 different cards)
      G.deck[player2][i] = rand() % 27;
      printf(" %d", G.deck[player2][i]);
    }
    printf("\n");
    numVictory = numTreasure = numAction = 0;
    for (i = numDeck - 2; i < numDeck; i++){
      card = G.deck[player2][i];
      // If top card matches 2nd-to-top card it is ignored
      if (i == (numDeck - 1) && card == G.deck[player2][i-1]){
        break;
      }
      if (card == estate || card == duchy || card == province ||
          card == gardens || card == great_hall){ 
        numVictory++;
      } 
      else if (copper <= card && card <= gold){
        numTreasure++;
      } 
      else {
        numAction++;
      }
    }
     
    // Randomly select player 1 discard
    G.discardCount[player1] = rand() % 5;
    printf("Setting Player1 Discard, %d card(s)\n", G.discardCount[player1]);

    // Randomly select player 2 discard
    G.discardCount[player2] = rand() % 5;
    printf("Setting Player2 Discard, %d card(s)\n", G.discardCount[player2]);

//--------------------------------------------
// Run test
//--------------------------------------------
    // Save the previous game state before testing function
    memcpy(&preG, &G, sizeof(struct gameState));

    // Call the function being tested
    playCard(tributePos, 0, 0, 0, &G); // 1 for discard

//--------------------------------------------
// Oracle
//--------------------------------------------

    printf("Checking that p1 gained %d actions:\n", numAction * 2);
    // One action was lost playing card
    asserttrue(G.numActions == preG.numActions - 1 + (numAction * 2));

    printf("Checking that p1 gained %d coins:\n", numTreasure * 2);
    asserttrue(G.coins == preG.coins + (numTreasure * 2));

    printf("Checking that p1 drew %d cards:\n", numVictory * 2);
    // Played tribute card should be discarded
    asserttrue(G.handCount[player1] == preG.handCount[player1] + (numVictory * 2) - 1);

    printf("Checking that p2 revealed 2 cards:\n");
    asserttrue(G.deckCount[player2] == preG.deckCount[player2] - 2);
  }

  if (testsFailed) {printf("\nFAILED %d tests\n", testsFailed);}
  else {printf("\nPASSED all %d tests\n", testsPassed);}

  return 0;
}
