/*
 * listEditFunctions.c
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

// in same header file
	void editList(ListPtr *currentPtr) //   TO DO
	{
		unsigned int userChoice;
		char name[MAX_SIZE];
		void (*menu[4])() = {editItem, addItem, deleteItem, returnToMenu };

			printf("Enter the name of the list to edit:\n");
			fflush(stdout);

			fgets(name, MAX_SIZE, stdin);
			size_t length = strlen(name);
			if (name[length - 1] == '\n') {
				name[length - 1] = '\0';
			}
			//options find list or cant find list
			userChoice = editListMenu();

			(*menu[userChoice - 1])();

		}
		unsigned int editListMenu() {
			unsigned int userChoice;
			do {
				printf("Options:\n"
						"1. Edit an Item\n"          // we load a premade file
						"2. Add a new item\n"// user gives filename
						"3. Delete an item\n"// editig the file
						"4. Return to main menu\n"
						"Enter your option:\n");
				fflush(stdout);
				scanf("%1u", &userChoice);
				while (getchar() != '\n')
					; // clearing scanf input buffer

				if ((userChoice < 1) || (userChoice > 4)) {

					printf("Please enter a valid number!\n");
					fflush(stdout);
				}

			} while ((userChoice < 1) || (userChoice > 4));

			return userChoice;
		}

		void editItem() {
		}
		void addItem() {
		}
		void deleteItem() {

		}
		void returnToMenu() {
			printf("Returning to main menu...\n");
			fflush(stdout);
			return;
		}
// end of header file

