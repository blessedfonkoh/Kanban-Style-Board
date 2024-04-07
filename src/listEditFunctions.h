/*
 * listEditFunctions.h
 *
 *  Created on: 5 Apr 2024
 *      Author: bless
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "structData.h"
#include "mainMenu.h"


#define MAX_SIZE 80


#ifndef LISTEDITFUNCTIONS_H_
#define LISTEDITFUNCTIONS_H_

void editList(ListPtr *currentPtr);

unsigned int editListMenu();
void editItem(ListPtr *currentPtr);
void addItem(ListPtr *currentPtr);
void deleteItem(ListPtr *currentPtr);
void returnToMenu();
//

#endif /* LISTEDITFUNCTIONS_H_ */
