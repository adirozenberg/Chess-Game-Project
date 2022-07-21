#include "Q7.h"

// global variables
bool haveStartPos = false;
bool havePaths = false;
bool havePathCovering = false;

void Q7()
{
	int choice, res;
	char* name;
	chessPos startPos;
	pathTree allPossiblePaths;
	chessPosList* pathCovering = NULL;

	printMenu();
	scanf("%d", &choice);
	while (choice != EXIT)
	{
		switch (choice)
		{
		case 1:
			scanf("\n%c %c", &startPos[0], &startPos[1]);
			if (!isValidPosition(startPos))
			{
				printf("Please enter a valid position");
				haveStartPos = false;
			}
			else
			{
				haveStartPos = true;
				havePaths = false;
				havePathCovering = false;
			}
			break;
		case 2:
			allPossiblePaths = Option2(&startPos);
			break;
		case 3:
			pathCovering = Option3(&startPos, &allPossiblePaths);
			break;
		case 4:
			Option4(&startPos, &allPossiblePaths, pathCovering);
			break;
		case 5:
			printf("Please enter a file name to load from: ");
			name = createNewFileName();
			res = checkAndDisplayPathFromFile(name);
			switchOfReturnedValue(res);
			break;
		default:
			printf("Please enter a valid option");
			break;
		}
		printf("\n-------------------------\n");
		printMenu();
		scanf("%d", &choice);
	}
	if (havePathCovering)
		free(pathCovering);

	printf("Goodbye!");
}

/* this function prints the manu to the screen */
void printMenu() {

	printf("1. Enter a knight's starting position\n2. Create all possible knight paths\n3. Find a knight path covering all board\n");
	printf("4.Save knight path covering all board\n5.Load and display path from file\n6.Exit\n");
}

/* this function check if the entered position is valid (row between A-H and col between 1-8).
if it is, the function returns true, else - return false. */
bool isValidPosition(chessPos position) {

	if (position[0] - 'A' >= 0 && position[0] - 'A' < BOARD_SIZE)
		if (position[1] - '0' >= 0 && position[1] - '0' < BOARD_SIZE)
			return true;
	return false;
}

/* this function gets a value from checkAndDisplayPathFromFile function, and prints a correct message to the screen */
void switchOfReturnedValue(int value) {

	switch (value)
	{
	case 1:
		printf("the knight's path is invalid\n");
		break;
	case 2:
		printf("the knight's path is covering all board\n");
		break;
	case 3:
		printf("the knight's path is not covering all board\n");
		break;
	case -1:
		printf("file was not found\n");
		break;
	}
}

/* this function creates a file name, and returns it */
char* createNewFileName() {

	char ch, getFirstEnter;
	char* string;
	int logicalSize = 0, physicalSize = 1;

	string = (char*)malloc(physicalSize * sizeof(char));
	check_allocation1(string, "read polynom String- first allocation");
	getFirstEnter = getchar();

	ch = getchar();

	while (ch != '\n')
	{
		if (logicalSize == physicalSize)
		{
			physicalSize = physicalSize * 2 + 1;
			string = (char*)realloc(string, physicalSize * sizeof(char));
			check_allocation1(string, "read polynom String - resizing the polynom string");
		}
		string[logicalSize] = ch;
		logicalSize++;
		ch = getchar();
	}
	string = (char*)realloc(string, (logicalSize + 1) * sizeof(char));
	check_allocation1(string, "read polynom String - returns the string to its logical size");

	string[logicalSize] = '\0';
	return string;
}

/* this function activates when the user choose option 2 from the manu.
the function check if the user already entered a position. if not, then a correct message appears on the screen.
if it has a position, the function updates havePaths to true, and returns a tree from findAllPossibleKnightPaths function */
pathTree Option2(chessPos* startPos)
{
	if (!haveStartPos)
	{
		printf("Please enter a starting position first");
		return;
	}
	else
	{
		havePaths = true;
		return findAllPossibleKnightPaths(startPos);
	}
}

/* this function activates when the user choose option 3 from the manu.
the function check if the user have a tree with all possible paths.
if it hasn't, then activates option2.
if it has paths, then creates a list of path that covering all board.
then check if the list is null, then there are no path like that, else returns that  list */
chessPosList* Option3(chessPos* startPos, pathTree* allPossiblePaths)
{
	chessPosList* tmp;
	if (!havePaths)
		*allPossiblePaths = Option2(startPos);
	if (havePaths)
	{
		tmp = findKnightPathCoveringAllBoard(allPossiblePaths);
		if (tmp == NULL)
			printf("No path covering all board");
		else
			havePathCovering = true;
		return tmp;
	}
}

/* this function activates when the user choose option 4 from the manu.
the function check if the user has a path that covering all board.
if it hasn't, then the function activaes option3 function.
if it has, the function asks the user to enter a file name, and then save the list at this file */
void Option4(chessPos* startPos, pathTree* allPossiblePaths, chessPosList* pathCovering)
{
	if (!havePathCovering)
	{
		pathCovering = Option3(startPos, allPossiblePaths);
	}
	if (havePathCovering)
	{
		printf("Please enter a file name to save into: ");
		char* name = createNewFileName();
		saveListToBinFile(name, pathCovering);
	}
}