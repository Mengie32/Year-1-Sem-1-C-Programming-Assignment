#ifndef DEFINITION_H
#define DEFINITION_H

	// Program now supports boards up to 26 columns and 19 rows, and up to 20 hidden word
	// (hidden words restriceted by number of words in dictionary)
	// (board dimensions restricted by no. of letters and terminal scrolling)
	
	
	#define ROWS 10
	#define COLUMNS 10
	#define AREA (ROWS*COLUMNS)
	
	#define WORDSTOCHOOSE 4
	
	#define MAXITERATIONS 50 // affects the chance of not finding a valid position for a word
	
	
	// Escape Codes:
	#define HIGHLIGHT  "\x1b[7m"
	#define REDBACK    "\x1b[41m"
	#define GRNBACK    "\x1b[42m"
	#define REDFORE    "\x1b[31m"
	#define GRNFORE    "\x1b[32m"
	#define BOLD	   "\x1b[1m"
	#define RESET      "\x1b[0m"
	#define CURSORPOS  "\x1b[%i;%iH"
	#define CURSORHOME "\x1b[H"
	#define CLEARFIELD "\x1b[0K"
	#define CLEARLINE  "\x1b[2K"
	#define CLRSCREEN  "\x1b[2J"CURSORHOME
	#define SAVEPOS	   "\x1b 7"
	#define RECALLPOS  "\x1b 8"

#endif // !DEFINITION_H

// Includes:

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


//Functions:

extern void displayWordBank();
extern void displayPuzzle();
extern void fillPuzzleWithWords();
extern void fillRandom();
extern void createBlankPuzzle();
extern void setBit(int* binaryValue, int position, int bool);
extern void printLine(int width);
extern void getWordBankSize();
extern void pauseTimer();
extern void resumeTimer();
extern void setCursorPos(int coords[2]);

extern int  game();
extern int  acceptAnswer();
extern int  userInput(int min, int max);
extern int  mainMenu();
extern int  pauseMenu();
extern int  endMenu();
extern int  getBit(int binaryValue, int position);
extern void refresh();
extern int searchBoard();
extern void win();
extern void newPuzzle();





