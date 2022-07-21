#include "Q6.h"


/*
This function gets a name of binary file that contains a list of positions in the format of the previous question.
The function reads the list and performs the following actions:
* If the list does not contain a valid path of the knight, then the function terminates and returns the value 1.
* Otherwise (if the list contains a valid path of the knight) - the function removes from the path locations that the knight visits more than once (if any)
and prints a chessboard with the path using the function from question 2.
* If the path covers all the cells in the board, the function returns 2. Otherwise the function returns 3.
* If the file does not exist - the function returns -1
*/
int checkAndDisplayPathFromFile(char* file_name)
{
	FILE* fp = fopen(file_name, "rb");
	if (fp == NULL)
		return THE_FILE_DOESNT_EXIST;

	chessPosList lst;
	makeEmptyList(&lst);
	extractPositionsFromFile(fp, &lst);

	if (!CheckListValidMoves(&lst))
		return THERE_IS_NO_LEGAL_PATH;

	display(&lst);

	int amountCovered = getListSize(&lst);
	if (amountCovered == BOARD_SIZE * BOARD_SIZE)
		return THE_PATH_COVERS_ALL_BOARD;

	return THE_PATH_DOESNT_COVERS_ALL_BOARD;
}

/*This function goes through the binary file according to the format and creates the list of positions*/
void extractPositionsFromFile(FILE* fp, chessPosList* lst)
{
	int i;
	unsigned short positionsAmount;
	unsigned int tempInt;
	unsigned char tempChar1, tempChar2, tempChar3, tempChar4;
	int mask = 0xE0000000;
	unsigned int res;
	chessPos tmp;
	chessPosCell* node;
	fread(&positionsAmount, sizeof(unsigned short), 1, fp);
	for (i = 0; i < positionsAmount * 2; i++)
	{
		if (i % 8 == 0)
		{
			fread(&tempInt, sizeof(int), 1, fp);
			tempChar1 = tempInt;
			tempChar2 = tempInt >> 8;
			tempChar3 = tempInt >> 16;
			tempChar4 = tempInt >> 24;
			tempInt = 0;
			tempInt |= tempChar1;
			tempInt = tempInt << 8;
			tempInt |= tempChar2;
			tempInt = tempInt << 8;
			tempInt |= tempChar3;
			tempInt = tempInt << 8;
			tempInt |= tempChar4;
			fseek(fp, -1, SEEK_CUR);
		}
		res = tempInt & mask;
		res = res >> 29;
		if (i % 2 == 0)
		{
			res += 'A';
			tmp[0] = res;
		}
		else
		{
			res += '1';
			tmp[1] = res;
			node = createNewListNode(tmp, NULL);
			insertNodeToEndPosList(lst, node);
		}
		tempInt = tempInt << 3;
	}
}

/* This function checks for each pair of consecutive positions in the list whether the transition of the knight from the first to the second position is valid.
If all pairs of subsequent positions are valid the function returns true, otherwise the function returns false. */
bool CheckListValidMoves(chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	if (isEmptyList(lst))
		return true;
	chessPosArray*** arr = validKnightMoves();
	while ((curr->next != NULL))
	{
		if (!IsValidMove(arr, curr->position, curr->next->position))
			return false;
		curr = curr->next;
	}
	return true;
}

/* This function gets two positions on the board and returns whether the movement of the knight from the first position to the second position is valid.
The function uses the array we created in question 1 that contains all the locations to which a knight can move from a specific location */
bool IsValidMove(chessPosArray*** validMoves, chessPos curr, chessPos next)
{
	unsigned int i;
	chessPosArray* arr = validMoves[curr[0] - 'A'][curr[1] - '1'];
	for (i = 0; i < (arr->size); i++)
	{
		if (arr->positions[i][0] == next[0])
		{
			if (arr->positions[i][1] == next[1])
			{
				return true;
			}
		}
	}
	return false;
}

int getListSize(chessPosList* lst)
{
	chessPosCell* curr = lst->head;
	int count = 0;
	while (curr != NULL)
	{
		count++;
		curr = curr->next;
	}
	return count;
}