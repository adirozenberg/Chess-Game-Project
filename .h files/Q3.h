#ifndef Q3_H
#define Q3_H

#include "Q2.h"

typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode {
	chessPos position;
	treeNodeListCell* next_possible_positions;
} treeNode;

typedef struct _treeNodeListCell {
	treeNode* node;
	struct _treeNodeListCell* next;
}treeNodeListCell;

typedef struct _pathTree {
	treeNode* root;
} pathTree;


pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
treeNode* findAllPossibleKnightPathsHelper(chessPos startingPosition, chessPosArray*** mat, bool path[][BOARD_SIZE]);
void insertNodeToEndListCell(treeNodeListCell** head, treeNodeListCell* tail);
void insertDataToEndListCell(treeNodeListCell** head, treeNode* data);
treeNodeListCell* createNewTreeListNode(treeNode* data, treeNodeListCell* next);
treeNode* createNewTreeNode(chessPos position);


#endif