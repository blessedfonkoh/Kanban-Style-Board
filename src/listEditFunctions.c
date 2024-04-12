/*
 * listEditFunctions.c
 *
 *  Created on: 5 Apr 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listEditFunctions.h"
#include "structData.h"
#include "mainMenu.h"

#define MAX_SIZE 80

int editListMenu()
{
	int userChoice;
	do
	{
		printf("Options:\n"
			   "1. Edit an Item\n"	 // we load a premade file
			   "2. Add a new item\n" // user gives filename
			   "3. Delete an item\n" // editig the file
			   "4. Return to main menu\n"
			   "Enter your option:\n");
		fflush(stdout);
		scanf("%1d", &userChoice);
		while (getchar() != '\n')
			; // clearing scanf input buffer

		if ((userChoice < 1) || (userChoice > 4))
		{

			printf("Please enter a valid number!\n");
			fflush(stdout);
		}

	} while ((userChoice < 1) || (userChoice > 4));

	return userChoice;
}
void editList(ListPtr *currentPtr) //   TO DO
{
	int userChoice;
	char name[MAX_SIZE];

	do
	{
		userChoice = editListMenu();

		switch (userChoice)
		{
		case 1:									  // edit item in list
			editItem(currentPtr);
			break;
		case 2:									  // add item to list
			addItem(currentPtr);
			break;		
		case 3:									  // delete item from list
			deleteItem(currentPtr); // Pass a pointer to the list
			break;
		case 4: // return to main menu
			returnToMenu();
			break;
		default:
			break;
		}
	} while (userChoice != 4); // Continue until user chooses to return to main menu
}
void editItem(ListPtr *currentPtr) // done
{
	char itemName[MAX_SIZE];
	char newName[MAX_SIZE];

	printf("Enter the name of the item to edit:\n");
	fflush(stdout);

	fgets(itemName, MAX_SIZE, stdin);

	// remove newline
	size_t length = strlen(itemName);
	if ((itemName[length - 1]) == '\n')
	{
		itemName[length - 1] = '\0';
	}

	// stcpy new name into spot where old item was
	Item *currentItem = (*currentPtr)->firstItem; // Start with the first item in the current list
	bool itemFound = false;						  // boolean  to track if the item is found

	while (currentItem != NULL)
	{
		if (strcmp(itemName, currentItem->itemName) == 0)
		{
			itemFound = true; // Set the boolean to true when the item is found
			break;			  // Exit the loop once the item is updated
		}
		currentItem = currentItem->nextItem;
	}

	if (!itemFound) // If the item is not found, print the message
	{
		printf("Item '%s' not found\n", itemName);
		return;
	}
	else
	{
		printf("Enter a new name for the item '%s':\n", itemName);
		fflush(stdout);

		fgets(newName, MAX_SIZE, stdin);

		// remove newline character
		length = strlen(newName);
		if ((newName[length - 1]) == '\n')
		{
			newName[length - 1] = '\0';
		}
		strcpy(currentItem->itemName, newName);
	}
}

void addItem(ListPtr *currentPtr)
{
	char name[MAX_SIZE];

	printf("Enter the name of the new item:\n");
	fgets(name, MAX_SIZE, stdin);

	// remove newline character
	size_t length = strlen(name);
	if ((name[length - 1]) == '\n')
	{
		name[length - 1] = '\0';
	}
	// create new item in list
	Item *newItem = malloc(sizeof(Item)); // create space for item

	if (newItem != NULL)
	{ // checking if space is available

		// place the new name in the list
		strcpy(newItem->itemName, name);
		newItem->nextItem = NULL; // the new item doesnt link to anything else

		Item *previousItem = NULL;
		Item *currentItem = (*currentPtr)->firstItem;

		// loop to find the end location of the list
		while (currentItem != NULL)
		{
			previousItem = currentItem;
			currentItem = currentItem->nextItem;
		}
		// insert new item at end of list
		previousItem->nextItem = newItem;
		newItem->nextItem = NULL; // no next item
	}
	else
	{
		printf("No memory available.\n");
		fflush(stdout);
	}
}
void deleteItem(ListPtr *currentPtr) // done
{
	if (*currentPtr == NULL || (*currentPtr)->firstItem == NULL)
	{
		printf("List is empty.\n");
		return;
	}

	char itemName[MAX_SIZE];

	printf("Enter the name of the item to delete:\n");
	fflush(stdout);

	fgets(itemName, MAX_SIZE, stdin);

	// remove newline
	size_t length = strlen(itemName);
	if ((itemName[length - 1]) == '\n')
	{
		itemName[length - 1] = '\0';
	}

	Item *previousItem = NULL;
	Item *currentItem = (*currentPtr)->firstItem; // Start with the first item in the current list
	bool itemFound = false;						  // boolean  to track if the item is found

	while (currentItem != NULL)
	{
		if (strcmp(itemName, currentItem->itemName) == 0)
		{
			itemFound = true; // Set the boolean to true when the item is found
			break;			  // Exit the loop once the item is updated
		}
		previousItem = currentItem;
		currentItem = currentItem->nextItem;
	}

	if (!itemFound) // If the item is not found, print the message
	{
		printf("Item '%s' not found\n", itemName);
		return;
	}
	if (previousItem != NULL)
	{
		previousItem->nextItem = currentItem->nextItem;
	}
	else
	{
		(*currentPtr)->firstItem = currentItem->nextItem; // Update the first item pointer if the deleted item was the first one
	}

	free(currentItem); // Free the memory of the deleted item
}

void returnToMenu()
{
	printf("Returning to main menu...\n");
	fflush(stdout);
	return;
}
