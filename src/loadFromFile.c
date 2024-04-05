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
#include "loadFromFile.h"
#define MAX_SIZE 80


void load(char fileName[MAX_SIZE]) // done
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
		if (fileName[length - 1] == '\n') {
			fileName[length - 1] = '\0';
		}

		if ((fPtr = fopen(fileName, "r")) == NULL) {
			printf("ERROR: could not open file %s\n", fileName);
			fflush(stdout);

			return;
		}

		else {

			while (fgets(info, 80, fPtr) != NULL) // reads each line of the file
			{
				// remove newline
				size_t len = strlen(info);
				if (info[len - 1] == '\n') {
					info[len - 1] = '\0';
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
		printf("\n"); // for formatting
		fflush(stdout);
	}


