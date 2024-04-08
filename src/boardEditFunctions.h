/*
 * boardEditFunctions.h
 *
 *  Created on: 5 Apr 2024
 *
 */

#ifndef BOARDEDITFUNCTIONS_H_
#define BOARDEDITFUNCTIONS_H_

unsigned int editBoardMenu();
void editBoard(ListPtr *currentPtr);
void editListName(ListPtr *currentPtr);
void addList(ListPtr *currentPtr);
void deleteList(ListPtr *currentPtr);

#endif /* BOARDEDITFUNCTIONS_H_ */
