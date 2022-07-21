#include "Q2.h"

/* this function gets a list of positions, removes nodes from the list that appear 2 or more times (by removeNodeFromList function),
and prints an 8X8 array with indecies of the nodes of the new list */
void display(chessPosList* lst) {

	int row, col, count = 1;
	int tmpArray[BOARD_SIZE][BOARD_SIZE];
	int howManyNodes = 0;
	chessPosCell* curr_cell = lst->head, * prev_cell = NULL;


	for (row = 0; row < BOARD_SIZE; row++)
		for (col = 0; col < BOARD_SIZE; col++)
			tmpArray[row][col] = 0;

	while (curr_cell != NULL) {

		updateRowAndCol(curr_cell, &row, &col);

		
		if (tmpArray[row][col] == 0)
			tmpArray[row][col] = 1;
		else 
		{
			removeNodeFromList(lst, curr_cell, prev_cell);
			curr_cell = prev_cell;
		}

		prev_cell = curr_cell;
		curr_cell = curr_cell->next; 
	}


	curr_cell = lst->head;
	while (curr_cell != NULL) {

		updateRowAndCol(curr_cell, &row, &col);

		tmpArray[row][col] = count;
		count++;
		curr_cell = curr_cell->next;
	}

	printArray(tmpArray);

}

/* this function gets a node, a row and a col. the function calculates the row and the col, and converts them to integers.*/
void updateRowAndCol(chessPosCell* current, int* row, int* col) {

	*row = (int)((current->position)[0] - 'A'); 
	*col = (int)(((current->position)[1] - '0') - 1); 

}

/* this function removes nodes that appear more than one time in lst */
chessPosList* removeNodeFromList(chessPosList* lst, chessPosCell* node, chessPosCell* prev) {

	chessPosCell* current, * saver;
	current = prev;

	/* when we get here, we find the place in the list where the next value is node */
	if (lst->tail == node) {

		saver = lst->tail;
		//free(saver->position); // only if we used a dynamic allocation to create the list
		lst->tail = current;
		lst->tail->next = NULL;
		//free(saver); // only if we used a dynamic allocation to create the list

	}
	else {

		saver = current->next;
		current->next = saver->next;
		//free(saver->position); // only if we used a dynamic allocation to create the list
		//free(saver); // only if we used a dynamic allocation to create the list
	}

	return lst;
}

/* this function gets an 8X8 array, and prints it. */
void printArray(int array[][BOARD_SIZE])
{
	int i, j, k;

	for (k = 0; k <= BOARD_SIZE; k++)
	{
		if (k == 0)
			printf("       ");
		else {
			printf(" %2d  ", k);
			if (k == BOARD_SIZE)
				printf("\n");
		}
	}

	for (i = 0; i < BOARD_SIZE; i++)
	{
		printf("    %c |", (char)('A' + i));

		for (j = 0; j < BOARD_SIZE; j++)
		{
			if (array[i][j] == 0)
				printf("   |");
			else
				printf(" %2d |", array[i][j]);

			if (j == BOARD_SIZE - 1)
				printf("\n");
		}
	}


}