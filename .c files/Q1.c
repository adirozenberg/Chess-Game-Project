#include "Q1.h"

chessPosArray*** validKnightMoves()
{
	int row, col;
	chessPosArray*** chessArray;
	chessArray = (chessPosArray***)malloc(BOARD_SIZE * sizeof(chessPosArray**));
	check_allocation3(chessArray, "validKnightMoves");

	for (row = 0; row < BOARD_SIZE; row++) {
		chessArray[row] = (chessPosArray**)malloc(BOARD_SIZE * sizeof(chessPosArray*));
		check_allocation2(chessArray[row], "validKnightMoves");
	}

	for (row = 0; row < BOARD_SIZE; row++)
	{
		for (col = 0; col < BOARD_SIZE; col++)
		{
			chessArray[row][col] = (chessPosArray*)malloc(sizeof(chessPosArray));
			check_allocation1(chessArray[row][col], "validKnightMoves");

			chessArray[row][col] = curr_posArray(row, col);
		}
	}

	return chessArray;

}

chessPosArray* curr_posArray(int row, int col)
{
	chessPosArray* res;
	res = (chessPosArray*)malloc(sizeof(chessPosArray));
	check_allocation1(res, "curr_posArray");

	chessPos* curr_positions, * temp = NULL;

	int logical_size = 0, pysical_size = 8;
	curr_positions = (chessPos*)malloc(pysical_size * sizeof(chessPos));
	check_allocation1(curr_positions, "curr_posArray");

	if ((row - 2) >= 0)
	{
		if (col + 1 <= BOARD_SIZE - 1)
			updateCurrPosition(curr_positions, row - 2, col + 1, &logical_size);

		if (col - 1 >= 0)
			updateCurrPosition(curr_positions, row - 2, col - 1, &logical_size);

	}

	if ((row + 2) <= BOARD_SIZE - 1)
	{
		if (col + 1 <= BOARD_SIZE - 1)
			updateCurrPosition(curr_positions, row + 2, col + 1, &logical_size);

		if (col - 1 >= 0)
			updateCurrPosition(curr_positions, row + 2, col - 1, &logical_size);
	}

	if ((col + 2) <= BOARD_SIZE - 1)
	{
		if (row - 1 >= 0)
			updateCurrPosition(curr_positions, row - 1, col + 2, &logical_size);

		if (row + 1 <= BOARD_SIZE - 1)
			updateCurrPosition(curr_positions, row + 1, col + 2, &logical_size);
	}

	if ((col - 2) >= 0)
	{
		if (row - 1 >= 0)
			updateCurrPosition(curr_positions, row - 1, col - 2, &logical_size);

		if (row + 1 <= BOARD_SIZE - 1)
			updateCurrPosition(curr_positions, row + 1, col - 2, &logical_size);
	}

	if (logical_size < pysical_size)
	{
		temp = (chessPos*)malloc(logical_size * sizeof(chessPos));
		check_allocation1(temp, "curr_posArray");

		copyChessPosArray(curr_positions, temp, logical_size);
		free(curr_positions);

		res->positions = temp;
	}
	else
		res->positions = curr_positions;

	res->size = logical_size;
	return res;

}
void updateCurrPosition(chessPos* curr_positions, int row, int col, int* logical_size)
{
	curr_positions[*logical_size][0] = (char)('A' + row);
	curr_positions[*logical_size][1] = (char)('0' + (col + 1));
	(*logical_size)++;
}

void copyChessPosArray(chessPos* curr_positions, chessPos* temp, int logical_size)
{
	int i;

	for (i = 0; i < logical_size; i++)
	{
		temp[i][0] = curr_positions[i][0];
		temp[i][1] = curr_positions[i][1];
	}
}

void check_allocation1(void* ptr, char* msg)
{
	if (ptr == NULL)
	{
		printf("Allocation failure: %s\n", msg);
		exit(1);
	}
}

void check_allocation2(void** ptr, char* msg)
{
	if (ptr == NULL)
	{
		printf("Allocation failure: %s\n", msg);
		exit(1);
	}
}

void check_allocation3(void*** ptr, char* msg)
{
	if (ptr == NULL)
	{
		printf("Allocation failure: %s\n", msg);
		exit(1);
	}
}