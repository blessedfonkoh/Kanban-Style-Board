/*
 ============================================================================
 Name        : bk-Assignment3-eclipse.c
 Author      : Blessed
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listEditFunctions.h"
#include "structData.h"
#include "loadFromFile.h"
#include "boardEditFunctions.h"
/* to run on vs code
#include "listEditFunctions.c"
#include "loadFromFile.c"
#include "boardEditFunctions.c"
*/

#define MAX_SIZE 80


unsigned int menuOptions();
void printBoard(List *currentPtr);
void displayBoard(char fileName[80]);

void save();
void quit();

int main()

{
	ListPtr currentPtr = NULL;
	unsigned int choice;
	char fileName[MAX_SIZE] = "sampleBoard.txt";

	void (*menu[6])() = {displayBoard, load, editList, editBoard, save, quit };
		do {
			choice = menuOptions();

			switch (choice) {
				case 1: // displayBoard
				case 2: // load
					(*menu[choice - 1])(fileName);
					break;
				case 3: // edit list
					(*menu[choice - 1])(currentPtr);
					break;
				case 4:
				case 5:
				case 6:
					(*menu[choice - 1])();
					break;
				default:
					break;
			}
		} while (choice != 6);

		return 0;
	}

	unsigned int menuOptions() // done

	{

		unsigned int choice;

		do {
			printf("Menu:\n"
					"1. Display board\n"           // we load a premade file
					"2. Load board from a file\n" // user gives filename
					"3. Edit list\n"             // editig the file
					"4. Edit Board\n"
					"5. Save board to a file\n"
					"6. Quit\n"
					"Enter your choice (1-6):\n");
			fflush(stdout);
			scanf("%1u", &choice);
			while (getchar() != '\n')
				; // clearing scanf buffer

			if ((choice < 1) || (choice > 6)) {

				printf("Please enter a valid number!\n");
				fflush(stdout);
			}

		} while ((choice < 1) || (choice > 6));

		return choice;
	}
	void printBoard(List *ptr) // Function to print the list of lists

	{
		// Check if the list is empty
		if (ptr == NULL) {
			puts("List is empty.\n");
		} else {
			while (ptr != NULL) {
				printf("%s \n", ptr->listName); // Print the name of the current list
				fflush(stdout);

				// Print the names of the items within the current list
				Item *currentItem = ptr->firstItem;
				while (currentItem != NULL) {
					printf("\t%s \n", currentItem->itemName);
					fflush(stdout);

					currentItem = currentItem->nextItem;
				}

				ptr = ptr->nextList; // Move to the next list
			}

			printf("\n");
			fflush(stdout);
		}
	}
	void displayBoard(char fileName[80]) // done
	{
		// load file
		FILE *fPtr;
		List *firstList = NULL;
		// Item *firstItem = NULL;
		char info[MAX_SIZE]; // array to store each line of data read from file

		if ((fPtr = fopen(fileName, "r")) == NULL) {
			puts("ERROR: could not open file");
			return;
		}

		else {

			while (fgets(info, MAX_SIZE, fPtr) != NULL) // reads each line of the file
			{
				// remove newline
				size_t length = strlen(info);
				if (info[length - 1] == '\n') {
					info[length - 1] = '\0';
				}

				if ((info[strlen(info) - 1]) == ':') { // its a list
					List *newList = malloc(sizeof(List));
					// may need error hadnling if allocation fails
					strcpy(newList->listName, info);
					newList->nextList = firstList;
					newList->firstItem = NULL;
					// Update the firstList pointer to point to the new list

					firstList = newList;
				} else { // it's an item
						 // Allocate memory for a new item

					Item *newItem = malloc(sizeof(Item));
					// may need error handling if this fails
					strcpy(newItem->itemName, info);
					newItem->nextItem = NULL;
					// Find the last item in the current list and link the new item
					if (firstList != NULL) // Check if there is at least one list
					{
						Item *lastItem = firstList->firstItem; // Initialize pointer to the first item of the current list

						if (lastItem == NULL) // Check if the list is empty
						{
							// If the list is empty, set the firstItem pointer of the list to point to the new item
							firstList->firstItem = newItem;
						} else {
							// If the list is not empty, search the list to find the last item
							while (lastItem->nextItem != NULL) {
								lastItem = lastItem->nextItem; // Move to the next item in the list
							}

							// Once the last item is found, link the new item to it by updating the nextItem pointer
							lastItem->nextItem = newItem;
						}
					}
				}
			}
		}
		fclose(fPtr);
		printBoard(firstList);
	}



		void save() // TO DO POURIS BUT IM GONA GO
		{
		}
		void quit() // DONE
		{
			printf("Quitting...\n");
			fflush(stdout);
			return;
		}
