/*
 ============================================================================
 Name        : bk-assignment-3.c
 Author      : Blessed & Pouria
 Description : Kanban Style Board
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listEditFunctions.h"
#include "structData.h"
#include "mainMenu.h"
#include "boardEditFunctions.h"
/* to run on eclipse comment these out, leave in to run on vs code*/
#include "listEditFunctions.c"
#include "mainMenu.c"
#include "boardEditFunctions.c"
//*/

int main()

{
	ListPtr currentPtr = NULL;
	List *currentItem = NULL;
	int updated = 0; // tracker for uplode board or new board
	unsigned int choice;
	char fileName[MAX_SIZE] = "sampleBoard.txt";

	void (*menu[6])() = {displayBoard, load, editList, editBoard, save, quit};
	do
	{

		choice = menuOptions(); // function to display menu options and error handle

		switch (choice)
		{
		case 1: // displayBoard() display loaded board or default board
			if (updated != 0)
			{
				printBoard(currentPtr);
			}
			else
			{
				(*menu[choice - 1])(fileName, &currentPtr);
			}
			break;
		case 2: // load() board from file
			(*menu[choice - 1])(fileName, &currentPtr);
			break;
		case 3: // editList() item names

			updated++;
			if (currentPtr == NULL)
			{
				printf("No list loaded. Please load a list first.\n");
				fflush(stdout);
			}
			else
			{

				char name[MAX_SIZE];
				bool found = false;
				printf("Enter the name of the list to edit:\n");
				fflush(stdout);

				fgets(name, MAX_SIZE, stdin);

				size_t length = strlen(name);
				if (name[length - 1] == '\n')
				{
					name[length - 1] = '\0';
				}

				// Check if the list is found
				ListPtr tempPtr = currentPtr;
				while (tempPtr != NULL)
				{

					if (strcmp(name, tempPtr->listName) == 0)
					{
						found = true;
						break;
					}
					tempPtr = tempPtr->nextList;
				}
				// If we can't find the list
				if (!found)
				{
					printf("Can't find list\n");
					fflush(stdout);
					break;
				}
				else
				{
					(*menu[choice - 1])(tempPtr);
				}
			}
			break;
		case 4: // editBoard() List names
			updated++;
			(*menu[choice - 1])(&currentPtr);
			break;
		case 5: // save to file
			updated = 0;
			FILE *fPtr;
			char newFileName[MAX_SIZE];

			printf("Enter filename:\n");
			fflush(stdout);

			fgets(newFileName, MAX_SIZE, stdin);

			// remove newline character
			size_t length = strlen(newFileName);
			if (newFileName[length - 1] == '\n')
			{
				newFileName[length - 1] = '\0';
			}

			if ((fPtr = fopen(newFileName, "w")) == NULL)
			{
				printf("ERROR: could not open file %s\n", newFileName);
				fflush(stdout);
				break;
			}
			else
			{
				(*menu[choice - 1])(currentPtr, fPtr);
			}
			break;
		case 6:
			(*menu[choice - 1])();
			break;
		default:
			break;
		}
	} while (choice != 6);

	return 0;
}
