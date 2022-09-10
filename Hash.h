/* Anton Dumitrita 324CB*/
#include "List.h"

#ifndef TEMA_1_HASH_H
#define TEMA_1_HASH_H

#endif //TEMA_1_HASH_H 

typedef int (*TFElem)(void*);     /* functie prelucrare element */
typedef int (*TFCmp)(void*, void*); /* functie de comparare doua elemente */
typedef void (*TF)(void*);     /* functie afisare/eliberare un element */
typedef int (*TFHash)(void*);


typedef struct
{
    int M;
    TFHash fh;
    List *buckets;
} Hashtable;

int codHash(void * element);
Hashtable* HInit(int bucketCount, TFHash fh);
void HFree(Hashtable** h, TF fe);
int DataLexCompare(Data *Data1, Data *Data2);
int CompInt (Cell * el1, Cell * el2);
Data* PInit(char *word, int count);
void HInsert(Hashtable *h, void * word);
void DataPrint(Data *p, FILE *file);
void HPrint_Bucket(List bucket, FILE *file);
void HPrint(Hashtable *h, FILE *file);
void InsSublist(List* bucket, Data* Data);
void LenPrint(Cell * cell,  FILE *file);
void HPrintLen(Hashtable *h, char* c, int len, FILE * outFisier);
void HPrintMax(Hashtable *h, int maxLen, FILE * out);
