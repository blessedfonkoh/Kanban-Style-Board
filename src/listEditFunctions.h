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
#include "loadFromFile.h"


#define MAX_SIZE 80


#ifndef LISTEDITFUNCTIONS_H_
#define LISTEDITFUNCTIONS_H_

void editList(ListPtr *currentPtr);

unsigned int editListMenu();
void editItem();
void addItem();
void deleteItem();
void returnToMenu();
//

#endif /* LISTEDITFUNCTIONS_H_ */
