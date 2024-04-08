/*
 * loadFromFile.c
 *
 *  Created on: 5 Apr 2024
 *      Author: bless
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "listEditFunctions.h"
#include "structData.h"
#include "mainMenu.h"
#define MAX_SIZE 80

unsigned int menuOptions() // done

{

	unsigned int choice;

	do
	{
		printf("Menu:\n"
			   "1. Display board\n"			 // we load a premade file
			   "2. Load board from a file\n" // user gives filename
			   "3. Edit list\n"				 // editig the file
			   "4. Edit Board\n"
			   "5. Save board to a file\n"
			   "6. Quit\n"
			   "Enter your choice (1-6):\n");
		fflush(stdout);
		scanf("%1u", &choice);
		while (getchar() != '\n')
			; // clearing scanf buffer

		if ((choice < 1) || (choice > 6))
		{

			printf("Please enter a valid number!\n");
			fflush(stdout);
		}

	} while ((choice < 1) || (choice > 6));

	return choice;
}

void printBoard(List *ptr) // Function to print the list of lists

{
	// Check if the list is empty for base case
	if (ptr == NULL)
	{
		return;
	}
	else
	{
		// recursively print the rest of the list first
		printBoard(ptr->nextList);

		printf("%s \n", ptr->listName); // Print the name of the current list
		fflush(stdout);

		// Print the names of the items within the current list
		Item *currentItem = ptr->firstItem;
		while (currentItem != NULL)
		{
			printf("\t%s \n", currentItem->itemName);
			fflush(stdout);

			currentItem = currentItem->nextItem;
		}

		ptr = ptr->nextList; // Move to the next list aka the previous one
	}
}

void displayBoard(char fileName[80], ListPtr *currentPtr) // done
{
	// load file
	FILE *fPtr;
	List *firstList = NULL;
	// Item *firstItem = NULL;
	char info[MAX_SIZE]; // array to store each line of data read from file

	if ((fPtr = fopen(fileName, "r")) == NULL)
	{
		printf("ERROR: could not open file");
		fflush(stdout);
		return;
	}

	else
	{

		while (fgets(info, MAX_SIZE, fPtr) != NULL) // reads each line of the file
		{
			// remove newline
			size_t length = strlen(info);
			if (info[length - 1] == '\n')
			{
				info[length - 1] = '\0';
			}

			if ((info[strlen(info) - 1]) == ':')
			{ // its a list
				List *newList = malloc(sizeof(List));
				// may need error hadnling if allocation fails
				strcpy(newList->listName, info);
				newList->nextList = firstList;
				newList->firstItem = NULL;
				// Update the firstList pointer to point to the new list

				firstList = newList;
			}
			else
			{ // it's an item
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
					}
					else
					{
						// If the list is not empty, search the list to find the last item
						while (lastItem->nextItem != NULL)
						{
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
	*currentPtr = firstList; // Update currentPtr to point to the loaded board
}

void load(char fileName[MAX_SIZE], ListPtr *currentPtr) // done
{
	FILE *fPtr;
	List *firstList = NULL;
	// Item *firstItem = NULL;
	char info[MAX_SIZE]; // array to store each line of data read from file

	printf("Enter filename:\n");
	fflush(stdout);

	fgets(fileName, MAX_SIZE, stdin);

	// remove newline
	size_t length = strlen(fileName);
	if (fileName[length - 1] == '\n')
	{
		fileName[length - 1] = '\0';
	}

	if ((fPtr = fopen(fileName, "r")) == NULL)
	{
		printf("ERROR: could not open file %s\n", fileName);
		fflush(stdout);

		return;
	}

	else
	{

		while (fgets(info, 80, fPtr) != NULL) // reads each line of the file
		{
			// remove newline
			size_t len = strlen(info);
			if (info[len - 1] == '\n')
			{
				info[len - 1] = '\0';
			}

			if ((info[strlen(info) - 1]) == ':')
			{ // its a list
				List *newList = malloc(sizeof(List));
				// may need error hadnling if allocation fails
				strcpy(newList->listName, info);
				newList->nextList = firstList;
				newList->firstItem = NULL;
				// Update the firstList pointer to point to the new list

				firstList = newList;
			}
			else
			{ // it's an item
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
					}
					else
					{
						// If the list is not empty, search the list to find the last item
						while (lastItem->nextItem != NULL)
						{
							lastItem = lastItem->nextItem; // Move to the next item in the list
						}

						// Once the last item is found, link the new item to it by updating the nextItem pointer
						lastItem->nextItem = newItem;
					}
				}
			}
		}
	}
	*currentPtr = firstList; // Update currentPtr to point to the loaded board
	fclose(fPtr);
	printf("\n"); // for formatting
	fflush(stdout);
}

void save(ListPtr currentPtr, FILE *fPtr)
{
	// Check if the list is empty for base case
	if (currentPtr == NULL)
	{
		printf("List is Empty\n");
	}
	else
	{
		// iterate through the board and write its contents to the file
		while (currentPtr != NULL)
		{
			fprintf(fPtr, "%s\n", currentPtr->listName); // write the list name to the file

			// iterate through the items within the current list and write their names to the file too
			Item *currentItem = currentPtr->firstItem;
			while (currentItem != NULL)
			{
				fprintf(fPtr, "%s\n", currentItem->itemName); // write the item name to the file
				currentItem = currentItem->nextItem;		  // move to the next item within that samne list
			}

			currentPtr = currentPtr->nextList; // move to the next list
		}
	}
	fclose(fPtr);
}

void quit() // DONE
{
	printf("Quitting...\n");
	fflush(stdout);
	return;
}
