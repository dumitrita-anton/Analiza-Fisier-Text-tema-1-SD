/* Anton Dumitrita 324CB*/
#include "List.h"

List LAlloc(void* elem)
{
    List list = (List)malloc(sizeof(Cell));
    if (list) {
        list->info = elem;
        list->next = NULL;
    }
    return list;
}

int LRemData(List *list, int (*elPick)(void *, void *), void *data) {
    List cell = *list;
    List ant = NULL;
    if(cell) do {
        if(elPick(cell->info, data) == 0) break;
        ant = cell;
        cell = cell->next;
    } while(cell != NULL);

    if(cell == NULL) return 0;
    if(ant == NULL)
        *list = cell->next;
    else
        ant->next = cell->next;
    
    free(cell);
    return 1;
}

List LAddFirst(List* list, void* elem)
{
    List aux = LAlloc(elem);
    if(aux == NULL) return NULL;
    if(*list != NULL)
        aux->next = *list;
    *list = aux;
    return aux;
}

List LAddSorted(List* list, void* elem, int (*elemComp)(void *elem, void *ele)) {
    List aux = LAlloc(elem);
    List prev = NULL;
    List curr = *list;
    if(*list == NULL) *list = aux;
    for(; curr != NULL; prev = curr, curr = curr->next) {
        if(elemComp(curr->info, elem) > 0) {
            aux->next = curr;
            if(prev == NULL)
                *list = aux;
            else prev->next = aux;
            return aux;
        }
        if(curr->next == NULL) {
            curr->next = aux;
            return aux;
        }

    }
    return aux;
}




