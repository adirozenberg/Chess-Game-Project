#include "Q3.h"


/* this function gets a starting position (a cell in the chess table), and calculates all of the possible paths the knight can go from that position,
until he arrived to a cell without any possible moves.
the function creates a tree from that paths, and also makes a list from the children of each cell. */
pathTree findAllPossibleKnightPaths(chessPos* startingPosition) {

	pathTree tr;
	int i, j;
	bool path[BOARD_SIZE][BOARD_SIZE];
	chessPosArray*** mat = validKnightMoves(); 

	for (i = 0; i < BOARD_SIZE; i++)
		for (j = 0; j < BOARD_SIZE; j++)
			path[i][j] = false;

	tr.root = findAllPossibleKnightPathsHelper(*startingPosition, mat, path); 
	return tr;
}

/* this recursive function gets a starting position, a mat array with all of the possible moves of the knight, and a boolean array
that symbolized each cell and if we walked at that cell or didn't yet.
the function calculates all of the paths that the knight can go through, and creates a tree of them, and also creates lists from the
children of each cell. */
treeNode* findAllPossibleKnightPathsHelper(chessPos startingPosition, chessPosArray*** mat, bool path[][BOARD_SIZE]) {

	treeNode* currnode;
	treeNode* curRoot = createNewTreeNode(startingPosition); 
	int row, col, curRow, curCol;
	chessPos* curPositions;
	
	row = (int)(startingPosition[0] - 'A');
	col = (int)((startingPosition[1] - '0') - 1);

	curPositions = mat[row][col]->positions; 
	for (unsigned int i = 0; i < mat[row][col]->size; i++) { 

	
		curRow = (int)(curPositions[i][0] - 'A');
		curCol = (int)((curPositions[i][1] - '0') - 1);

		if (!path[curRow][curCol])
		{
			path[row][col] = true; 

			
			currnode = findAllPossibleKnightPathsHelper(curPositions[i], mat, path);

			path[row][col] = false; 

			insertDataToEndListCell(&(curRoot->next_possible_positions), currnode); 
		}
	}

	return curRoot;
}


/* this function gets a head of a list and a node, then check if the list is empty, then insert the node to the head,
else- going through the list until we got to the end, and insert the node there */
void insertNodeToEndListCell(treeNodeListCell** head, treeNodeListCell* tail)
{
	treeNodeListCell* current = *head;
	if (*head == NULL)
		*head = tail;
	else
	{
		while (current->next != NULL)
			current = current->next;

		current->next = tail;
	}

	tail->next = NULL;
}

/* this function gets a head and a data (the data is a subtree of possible knight's paths), and create a new node and then insert it to the list's end */
void insertDataToEndListCell(treeNodeListCell** head, treeNode* data)
{
	treeNodeListCell* newTail;
	newTail = createNewTreeListNode(data, NULL);
	insertNodeToEndListCell(head, newTail);
}


/* this function gets a data and a pointer to the next node in the list (list of children), then create a new list node
by dynamic allocation, updates the data of the new list node and returns it. */
treeNodeListCell* createNewTreeListNode(treeNode* data, treeNodeListCell* next)
{
	treeNodeListCell* res;
	res = (treeNodeListCell*)malloc(sizeof(treeNodeListCell));
	check_allocation1(res, "createNewTreeListNode");

	res->node = data;
	res->next = next;
	return res;
}

treeNode* createNewTreeNode(chessPos position) {

	treeNode* newRoot;
	newRoot = (treeNode*)malloc(sizeof(treeNode));
	check_allocation1(newRoot, "createNewTreeNode");

	newRoot->position[0] = position[0];
	newRoot->position[1] = position[1];
	newRoot->next_possible_positions = NULL;

	return newRoot;

}
