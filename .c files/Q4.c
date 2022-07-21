#include "Q4.h"



chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree) {

	chessPosList* list = (chessPosList*)malloc(sizeof(chessPosList));

	if (path_tree->root == NULL)
		return NULL;

	bool found = false;
	findKnightPathCoveringAllBoardHelper(path_tree->root, 1, list, &found);
	if (found)
	{
		insertDataToStartList(list, path_tree->root->position);
		return list;
	}
	else
	{
		free(list);
		return NULL;
	}

}

void findKnightPathCoveringAllBoardHelper(treeNode* root, int counter, chessPosList* lst, bool* found)
{
	treeNodeListCell* curr;

	if (counter == BOARD_SIZE * BOARD_SIZE)
	{
		makeEmptyList(lst);
		*(found) = true;
	}

	if (root == NULL)
		return;

	else
	{
		curr = root->next_possible_positions;
		while (curr != NULL)
		{

			findKnightPathCoveringAllBoardHelper(curr->node, counter + 1, lst, found);

			if ((*found) == true)
			{
				insertDataToStartList(lst, curr->node->position);
				return;
			}

			curr = curr->next;
		}

		return;
	}
}

void insertDataToStartList(chessPosList* lst, chessPos position)
{
	chessPosCell* newHead;
	newHead = createNewListNode(position, NULL);
	insertNodeToStartList(lst, newHead);
}

chessPosCell* createNewListNode(chessPos position, chessPosCell* next)
{
	chessPosCell* res;
	res = (chessPosCell*)malloc(sizeof(chessPosCell));
	check_allocation1(res, "createNewListNode");

	(res->position)[0] = position[0];
	(res->position)[1] = position[1];
	res->next = next;
	return res;

}

void insertNodeToStartList(chessPosList* lst, chessPosCell* head)
{
	if (isEmptyList(lst))
	{
		head->next = NULL;
		lst->head = lst->tail = head;
	}
	else
	{
		head->next = lst->head;
		lst->head = head;
	}
}

void makeEmptyList(chessPosList* lst)
{
	lst->head = lst->tail = NULL;
}

bool isEmptyList(chessPosList* lst)
{
	if (lst->head == NULL)
		return true;

	return false;
}

void insertNodeToEndPosList(chessPosList* lst, chessPosCell* add)
{
	if (isEmptyList(lst))
	{
		lst->head = lst->tail = add;
	}
	else
	{
		lst->tail->next = add;
		lst->tail = add;
	}
}
