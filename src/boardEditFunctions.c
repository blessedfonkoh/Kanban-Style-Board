/*
 * boardEditFunctions.c
 *
 *  Created on: 5 Apr 2024
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "listEditFunctions.h"
#include "structData.h"
#include "mainMenu.h"

int editBoardMenu()
{
    int userChoice;
    do
    {
        printf("Options:\n"
               "1. Edit the name of a list\n" // we load a premade file
               "2. Add a new list\n"          // user gives filename
               "3. Delete a list\n"           // editig the file
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

void editBoard(ListPtr *currentPtr)
{
    int choice;
    char name[MAX_SIZE];
    bool found = false; // boolean for finding the list
    if (*currentPtr == NULL)
    {
        printf("No list loaded. Please load a list first.\n");
        fflush(stdout);
        return;
    }
    do
    {
        choice = editBoardMenu();

        // process user choice
        switch (choice)
        {
        case 1:

                printf("Enter the name of the list to edit:\n");
                fflush(stdout);

            fgets(name, MAX_SIZE, stdin);

            size_t length = strlen(name);
            if (name[length - 1] == '\n')
            {
                name[length - 1] = '\0';
            }

            // Check if the list is found
            ListPtr tempPtr = *currentPtr;
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
                editListName(&tempPtr);
            }
            break;
        case 2:
            addList(&tempPtr);
            break;
        case 3:
            deleteList(currentPtr);
            break;
        case 4:
            returnToMenu(currentPtr);
            break;
        default:
            break;
        }
    } while (choice != 4);
}

void editListName(ListPtr *currentPtr)
{
    char newName[MAX_SIZE];
    printf("Enter a new name for list '%s':\n", (*currentPtr)->listName);
    fflush(stdout);
    fgets(newName, MAX_SIZE, stdin);

    // remove newline
    size_t length = strlen(newName);
    if ((newName[length - 1]) == '\n')
    {
        newName[length - 1] = '\0';
    }
    strcpy((*currentPtr)->listName, newName);
}
void addList(ListPtr *currentPtr)
{
    char name[MAX_SIZE];

    printf("Enter the name of the new list:\n");
    fgets(name, MAX_SIZE, stdin);

    // remove newline character
    size_t length = strlen(name);
    if ((name[length - 1]) == '\n')
    {
        name[length - 1] = '\0';
    }

    ListPtr newList = malloc(sizeof(List)); // create new list

    if (newList != NULL)
    { // checking if space is available

        // place the new name in the list
        strcpy(newList->listName, name);
        newList->nextList = NULL; // the new list doesnt link to anything else

        ListPtr prevList = NULL;
        ListPtr currentList = *currentPtr;

        // find end of board
        while (currentList != NULL)
        {
            prevList = currentList;
            currentList = currentList->nextList;
        }

        // insert item at end of board
        prevList->nextList = newList;
        newList->nextList = NULL; // no next list as we are at the end of the board
    }
    else
    {
        printf("No memory available.\n");
        fflush(stdout);
    }
}
void deleteList(ListPtr *currentPtr)
{
    if (*currentPtr == NULL)
    {
        printf("List does not exist.\n");
        return;
    }
    char newName[MAX_SIZE];
    printf("Enter the name of the list to delete:\n");
    fflush(stdout);

    fgets(newName, MAX_SIZE, stdin);

    size_t length = strlen(newName);
    if (newName[length - 1] == '\n')
    {
        newName[length - 1] = '\0';
    }
    ListPtr prevList = NULL;
    ListPtr currentList = (*currentPtr);
    bool listFound = false;

    while (currentList != NULL)
    {

        if (strcmp(newName, currentList->listName) == 0)
        {
            listFound = true;
            break;
        }
        prevList = currentList;
        currentList = currentList->nextList;
    }
    // If we can't find the list
    if (!listFound)
    {
        printf("Can't find list\n");
        fflush(stdout);
        return;
    }

    if (prevList != NULL)
    {
        prevList->nextList = currentList->nextList;
    }
    else
    {
        *currentPtr = currentList->nextList; // updating the currentPtr to skip the list to be deleted
    }

    free(currentList); // freeing memory for the deleted list

    return;
}