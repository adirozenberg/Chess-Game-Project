#ifndef Q6_H
#define Q6_H
#define THERE_IS_NO_LEGAL_PATH 1
#define THE_PATH_COVERS_ALL_BOARD 2
#define THE_PATH_DOESNT_COVERS_ALL_BOARD 3
#define THE_FILE_DOESNT_EXIST -1


#include "Q5.h"

int checkAndDisplayPathFromFile(char* file_name);
void extractPositionsFromFile(FILE* fp, chessPosList* lst);
bool CheckListValidMoves(chessPosList* lst);
bool IsValidMove(chessPosArray*** validMoves, chessPos curr, chessPos next);
int getListSize(chessPosList* lst);

#endif 
