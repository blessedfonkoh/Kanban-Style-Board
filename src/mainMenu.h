/*
 * loadFromFile.h
 *
 *  Created on: 5 Apr 2024
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structData.h"
#define MAX_SIZE 80

#ifndef LOADFROMFILE_H_
#define LOADFROMFILE_H_

unsigned int menuOptions();
void printBoard(List *currentPtr);
void displayBoard(char fileName[80], ListPtr *currentPtr);
void load(char fileName[MAX_SIZE], ListPtr *currentPtr);

void save(ListPtr currentPtr,FILE *fPtr);
void quit();

#endif /* LOADFROMFILE_H_ */
