#ifndef Q7_H
#define Q7_H

#define EXIT 6
#include "Q6.h"


void Q7();
pathTree Option2(chessPos* startPos);
chessPosList* Option3(chessPos* startPos, pathTree* allPossiblePaths);
void Option4(chessPos* startPos, pathTree* allPossiblePaths, chessPosList* pathCovering);
void printMenu();
bool isValidPosition(chessPos position);
void switchOfReturnedValue(int value);
char* createNewFileName();


#endif