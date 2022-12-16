#include "Definitions.h"

extern char puzzle[ROWS][COLUMNS];
extern char wordBank[WORDSTOCHOOSE][10];
extern int wordBankSize;
extern int ansField[2];
extern int logField[2];
extern int found;
int coord[4]; // startRow, startColumn, endRow, endColumn
extern int* orientationToOffsets(orientation);

//returns 1 if the string is a letter followed by some numbers, else retuns 0.
int isValidInput(char input[10]) {
	int i;
	int letter = input[0];

	//test for starting letter
	binaryWrite(&letter, 5, 0); // ignore case by converting to uppercase
	if (letter < 65 || letter > 90) {
		return 0;
	}

	// test for following numbers
	for (i = 1; i < strlen(input); i++) {
		if (input[i] < 48 || input[i] > 57) {
			return 0;
		}
	}
	return 1;
}

void acceptAnswer() {
	char answer[10];
	char* token;
	char* context;
	gets(answer);
	if (!answer[0]) { // prevent crash if user enters a blank answer
		setCursorPos(logField);
		printf(EMPTYFIELD REDFORE"Cannot leave field blank"RESET);
		return 0;
	}
	// start coordinate:
	token = strtok_s(answer, " ",&context);
	if (!isValidInput(token)) {
		return 0;
	}
	//start row no.
	binaryWrite(token, 5, 0); // ignore case by converting to uppercase
	coord[0] = *token - 65;
	//start column no.
	token += 1;
	coord[1] = atoi(token) - 1;

	//end row no.
	token = strtok_s(NULL, " ", &context);
	if (!isValidInput(token)) {
		return 0;
	}
	binaryWrite(token, 5, 0); // ignore case by converting to uppercase
	coord[2] = *token - 65;
	//end column no.
	token += 1;
	coord[3] = atoi(token) - 1;

	
	//printf("\n\n (%c,%c) -> (%c,%c)", answer[0], answer[1], answer[3], answer[4]);
	//printf("\n\n (%i,%i) -> (%i,%i)",coord[0],coord[1], coord[2], coord[3]);
}									 
									 
//returns relative orientation of coordinates. returns -1 if orientation is invlaid
int cardinalDirection() {
	int colDiff = coord[2] - coord[0];
	int rowDiff = coord[3] - coord[1];
	if (colDiff < 0 || rowDiff < 0) {
		return -1;
	}
	return !rowDiff ? 0 : rowDiff == colDiff ? 1 : !colDiff ? 2 : -1;
}

void searchBoard() {
	int orientation = cardinalDirection();
	int* offsets = orientationToOffsets(orientation);
	int yo = *offsets, xo = *(offsets + 1);
	int x = 0, y = 0, i;
	char word[10] = " ";
	char letter;
	char* bankWord = NULL;
	if (orientation == -1) {
		setCursorPos(logField);
		printf(EMPTYFIELD REDFORE"Invalid Orientation, words may be vertical, horizontal, or diagonal only."RESET);
		return 0;
	}
	x = coord[0]; // column
	y = coord[1]; // row
	i = 0;
	do {
		if (i >= 10) {
			setCursorPos(logField);
			printf(EMPTYFIELD REDFORE"Words cannot be longer than 10 letters."RESET);
			strcpy_s(word, 10, "");
			break;
		}
		letter = puzzle[y][x];
		binaryWrite(&letter, 5, 0); // remove highlight data from letter
		word[i] = letter;
		i++;
		x += xo;
		y += yo;
	} while (!(x > coord[2] || y > coord[3]));

	if (!word) {
		return 0;
	}

	for (i = 0; i < wordBankSize; i++) {
		bankWord = wordBank[i];
		if (strcmp(bankWord, word) == 0) {
			if (binaryRead(found, i)) {
				setCursorPos(logField);
				printf(EMPTYFIELD"You already found %s.", word);
				return 0;
			}
			binaryWrite(&found,i,1);
			displayWordBank();
			x = coord[0];
			y = coord[1];
			do {
				binaryWrite(&puzzle[y][x],5,1);
				x += xo;
				y += yo;
			} while (!(x > coord[2] || y > coord[3]));
			displayPuzzle();
			setCursorPos(logField);
			printf(EMPTYFIELD GRNFORE"You Found %s!"RESET, word);
			return 1;
		}
	}
	setCursorPos(logField);
	printf(EMPTYFIELD REDFORE"%s is not in the word bank."RESET, word);
	
}




