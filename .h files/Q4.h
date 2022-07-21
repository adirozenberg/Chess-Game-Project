#ifndef Q4_H
#define Q4_H

#include "Q3.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree* path_tree);
void findKnightPathCoveringAllBoardHelper(treeNode* root, int counter, chessPosList* lst, bool* found);

void insertDataToStartList(chessPosList* lst, chessPos position);
chessPosCell* createNewListNode(chessPos position, chessPosCell* next);
void insertNodeToStartList(chessPosList* lst, chessPosCell* head);
void insertNodeToEndPosList(chessPosList* lst, chessPosCell* add);
void makeEmptyList(chessPosList* lst);
bool isEmptyList(chessPosList* lst);

#endif