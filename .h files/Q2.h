#ifndef Q2_H
#define Q2_H

#include "Q1.h"
#define ChessPosComp(x,y) {x[0]=y[0];x[1]=y[1];}

typedef struct _chessPosCell {
	chessPos position;
	struct _chessPosCell* next;
} chessPosCell;

typedef struct _chessPosList {
	chessPosCell* head;
	chessPosCell* tail;
} chessPosList;


void display(chessPosList* lst);
chessPosList* removeNodeFromList(chessPosList* lst, chessPosCell* node, chessPosCell* prev);
void updateRowAndCol(chessPosCell* current, int* row, int* col);
void printArray(int array[][BOARD_SIZE]);


#endif
