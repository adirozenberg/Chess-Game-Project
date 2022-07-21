#include "Q5.h"

/*This function gets as parameters a file name and a list of positions.
The function saves the positions in the list as follows:
At the beginning of the file a number will be kept that will contain the number of locations in the list.
The positions will then be stored in the order in the list, while each position represented by 6 bits -
The 3 left bits represented the line number minus 1
And the 3 right bits represented the column number minus 1
*/
void saveListToBinFile(char* file_name, chessPosList* pos_list)
{
	FILE* fp;
	unsigned short int numOfListNodes;
	int curr_byte;
	chessPosCell* curr_node;
	bool byte2, byte3;
	byte2 = byte3 = false;

	fp = fopen(file_name, "wb");
	checkIfOpeningSucceeded(fp);

	numOfListNodes = numOfNodes(pos_list);
	fwrite(&numOfListNodes, sizeof(unsigned short int), 1, fp);

	curr_node = pos_list->head;
	curr_byte = 1;

	/*The function writes the positions to the file in 3 Byte. Each Byte and each position inside the Byte has its own mask according to each
	position contains 6 bits. Each time we finish writing a Byte - we will write it to the file and update that we have progressed to the next Byte.
	The function is a cyclic function - every time we write to file 3 Bytes we go back to writing the first Byte.
	*/
	while (curr_node != NULL)
	{
		if (curr_byte == 1)
		{
			byte2 = writeToByte1(fp, curr_node);
			if (byte2) /*If there is another position, some of its bits should be written in the next Byte because there is no space left in that Byte*/
				curr_byte++;
			curr_node = curr_node->next;

		}
		if (curr_byte == 2)
		{
			byte3 = writeToByte2(fp, curr_node);
			if (byte3)
				curr_byte++;
			curr_node = curr_node->next;
		}
		if (curr_byte == 3)
		{
			writeToByte3(fp, curr_node);

			/*The function is a cyclic function. So after writing 3 Bytes we will go back to writing the first Byte because its masks are built
			accordingly (back to the "starting point").*/
			curr_byte = 1;
			byte2 = byte3 = false;
			curr_node = (curr_node->next)->next;

		}

	}
	fclose(fp);


}

/*This function counts the number of positions in the list and returns that number*/
unsigned short int numOfNodes(chessPosList* pos_list)
{
	unsigned short int counter = 0;
	chessPosCell* curr_node = pos_list->head;

	while (curr_node != NULL)
	{
		counter++;
		curr_node = curr_node->next;
	}

	return counter;
}


bool writeToByte1(FILE* file, chessPosCell* curr_node)
{
	BYTE currByteToWrite, mask1, mask2, mask3a;
	currByteToWrite = 0;

	mask1 = (((curr_node->position)[0]) - 'A') << 5;
	mask2 = ((((curr_node->position)[1]) - '0') - 1) << 2;

	currByteToWrite = currByteToWrite | mask1;
	currByteToWrite = currByteToWrite | mask2;

	curr_node = curr_node->next;
	if (curr_node != NULL) { /*If there is another position in the list*/
		mask3a = (((curr_node->position)[0]) - 'A') >> 1;
		currByteToWrite = currByteToWrite | mask3a;

		fwrite(&currByteToWrite, sizeof(BYTE), 1, file);
		return true;
	}
	else {

		fwrite(&currByteToWrite, sizeof(BYTE), 1, file);
		return false;
	}
}


bool writeToByte2(FILE* file, chessPosCell* curr_node)
{
	BYTE currByteToWrite, mask3b, mask4, mask5, mask6a;
	currByteToWrite = 0;

	mask3b = (((curr_node->position)[0]) - 'A') << 7;
	mask4 = ((((curr_node->position)[1]) - '0') - 1) << 4;
	currByteToWrite = currByteToWrite | mask3b;
	currByteToWrite = currByteToWrite | mask4;

	curr_node = curr_node->next;
	if (curr_node != NULL) {
		mask5 = ((curr_node->position)[0] - 'A') << 1;
		mask6a = (((curr_node->position)[1] - '0') - 1) >> 2;
		currByteToWrite = currByteToWrite | mask5;
		currByteToWrite = currByteToWrite | mask6a;

		fwrite(&currByteToWrite, sizeof(BYTE), 1, file);
		return true;
	}
	else {
		fwrite(&currByteToWrite, sizeof(BYTE), 1, file);
		return false;
	}

}

void writeToByte3(FILE* file, chessPosCell* curr_node)
{
	BYTE currByteToWrite, mask6b, mask7, mask8;
	currByteToWrite = 0;

	mask6b = (((curr_node->position)[1] - '0') - 1) << 6;
	currByteToWrite = currByteToWrite | mask6b;

	curr_node = curr_node->next;
	if (curr_node != NULL) {
		mask7 = ((curr_node->position)[0] - 'A') << 3;
		mask8 = ((((curr_node->position)[1]) - '0') - 1);
		currByteToWrite = currByteToWrite | mask7;
		currByteToWrite = currByteToWrite | mask8;
	}

	fwrite(&currByteToWrite, sizeof(BYTE), 1, file);
}

void checkIfOpeningSucceeded(FILE* fp)
{
	if (fp == NULL)
	{
		printf("Failed opening the file. Exiting!\n");
		exit(1);
	}
}