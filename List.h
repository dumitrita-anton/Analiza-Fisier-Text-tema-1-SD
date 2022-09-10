/* Anton Dumitrita 324CB*/
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdarg.h>
#include <ctype.h>

#ifndef TEMA_1_LIST_H
#define TEMA_1_LIST_H

#endif //TEMA_1_LIST_H

typedef struct SCell
{
    void *info;
    struct SCell *next;
} Cell, *List;

typedef struct {
    char * word;
    int count;
} Data;


int LInsert(List *list, void *elem, int (*elCompare)(void *, void *));
int LRemData(List *list, int (*elPick)(void *, void *), void *data);
List LAlloc(void*);
Cell* LAddFirst(List*, void*);
Cell* LAddLast(List*, void*);
Cell* LAddSorted(List* list, void* elem, int (*elemComp)(void *elem, void* ele));