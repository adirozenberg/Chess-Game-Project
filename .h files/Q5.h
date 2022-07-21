#ifndef Q5_H
#define Q5_H

#include "Q4.h"

typedef unsigned char BYTE;

void saveListToBinFile(char* file_name, chessPosList* pos_list);
unsigned short int numOfNodes(chessPosList* pos_list);
bool writeToByte1(FILE* file, chessPosCell* curr_node);
bool writeToByte2(FILE* file, chessPosCell* curr_node);
void writeToByte3(FILE* file, chessPosCell* curr_node);
void checkIfOpeningSucceeded(FILE* fp);

#endif
