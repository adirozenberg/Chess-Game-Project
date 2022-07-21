#ifndef Q1_H
#define Q1_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h>

#define BOARD_SIZE 5

typedef char chessPos[2];

typedef struct _chessPosArray {
	unsigned int size;
	chessPos* positions;
} chessPosArray;

chessPosArray*** validKnightMoves();
chessPosArray* curr_posArray(int row, int col);
void updateCurrPosition(chessPos* curr_positions, int row, int col, int* logical_size);
void copyChessPosArray(chessPos* curr_positions, chessPos* temp, int logical_size);
void check_allocation1(void* ptr, char* msg);
void check_allocation2(void** ptr, char* msg);
void check_allocation3(void*** ptr, char* msg);

#endif
