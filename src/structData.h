/*
 * structData.h
 *
 *  Created on: 5 Apr 2024
 *      Author: bless
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#ifndef STRUCTDATA_H_
#define STRUCTDATA_H_



#define MAX_SIZE 80

typedef struct list {
	char listName[MAX_SIZE]; // name stored in the node
	struct list *nextList;   // Pointer to the next node
	struct item *firstItem;  // pointer to first item

} List;
typedef List *ListPtr;

typedef struct item {
	char itemName[MAX_SIZE];
	struct item *nextItem; // pointer to next item
} Item;

#endif /* STRUCTDATA_H_ */
