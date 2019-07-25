/*****************************************************
 * CS362 Random Testing Quiz
 * Matthew Beachly
 *
 * Modified inputChar() and inputString() functions
 * in order to run random tests with the goal of 
 * reaching over 85% branch coverage in testme()
 *****************************************************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>

char inputChar()
{
    // Pick a random ASCII character between
    // 32 (Space) and 126 (~)
    char c = (char)((rand() % 95) + 32);
    return c;
}

//char* globalString = (char*)malloc(sizeof(char) * 16);

//char* inputString()
// Changed this so that string could be passed in and modified
void inputString(char* string)
{   // Randomly select size between 0 and 10
    int size = (rand() % 11); 
    
    // 0 will be special case string for final IF statement
    if (size == 0){
      strcpy(string, "reset");
    } 
    else {
      int i;
      for (i = 0; i < size - 1; i++){
        string[i] = inputChar();
      }
      string[size - 1] = 0; // Last character must terminate string (null)
   }
}

void testme()
{
  int tcCount = 0;
  //char* s;
  // Added this so string would hold plenty of characters
  char* s = (char*)malloc(sizeof(char) * 16);
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    //s = inputString();
    inputString(s); // Changed this so pointer could be passed in
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' '&& state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      free(s);
      exit(200);
    }
  }
  free(s); // Added this to free allocated memory
}


int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}
