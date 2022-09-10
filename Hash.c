/* Anton Dumitrita 324CB*/
#include "Hash.h"

Data *DInit(char *word, int count) {
    
    Data *p = (Data *)malloc(sizeof(Data));
    p->word = word;
    p->count = count;
    return p;
}

void DAct(Data *data) {
    data->count++;
}

int LenCompare(Cell *cell1, Cell *cell2) {
    int len1 = *(int *)cell1->info;
    int len2 = *(int *)cell2->info;
    if (len1 < len2)
        return -1;
    else if (len1 > len2)
        return 1;
    return 0;
}

int DataCompare(Data *data1, Data *data2) {
    if (strcmp(data1->word, data2->word) == 0)
        return 0;
    else if (data1->count < data2->count)
        return 1;
    else if (data1->count > data2->count)
        return -1;
    else if (data1->count == data2->count)
        return strcmp(data1->word, data2->word);
    return 0;
}

int codHash(void *element) {
    char *word = (char *)element;
    int cod;
    if (isupper(word[0]))
        cod = *word - 'A';
    else
        cod = *word - 'a';
    return cod;
}

Hashtable *HInit(int M, TFHash fh){
    
    Hashtable *h = (Hashtable *)malloc(sizeof(Hashtable));
    if (!h) {
        printf("eroare alocare hash\n");
        return NULL;
    }

    h->buckets = (List *)malloc(M * sizeof(List));
    if (!h->buckets) {
        printf("eroare alocare vector de pointeri TLG in hash\n");
        free(h);
        return NULL;
    }

    h->M = M;
    h->fh = fh;
    return h;
}

void HInsert(Hashtable *h, void *word) {
    
    //initializeaza un element de tip data
    Data *data = (Data *)DInit(word, 1);
    
    //creeaza celula de lista ce contine lungimea cuvintelor
    int *len = (int *)malloc(sizeof(int));
    *len = strlen((char *)word);
    Cell *link = LAlloc(len);

    //calculeaza codul hash pentru cuvantul input
    int cod = h->fh(word);
    List *bucket = &h->buckets[cod];

    //adaugare la inceput de bucket a celulei link
    //inserare data in sublista
    if (*bucket == NULL){
        LAddFirst(bucket, link);
        InsSublist(&(link->next), data);
        return;
    }

    //cauta lista corespunzatoare cu lungimea cuvantului
    List p = *bucket;
    if (p)
        do {
            if (LenCompare(p->info, link) == 0) {
                List aux = (List)p->info;
                InsSublist(&(aux->next), data);
                return;
            }
            p = p->next;
        } while (p != NULL);

    //insereaza lungimea si elementul data in sublista 
    InsSublist(&(link->next), data);
    LAddSorted(bucket, link, (int (*)(void *, void *))LenCompare);
}

void InsSublist(List *bucket, Data *data) {
    
    /* verifica daca cuvantul este deja in lista 
    in caz afirmativ actualizeza frecventa cuvantului*/
    List cell = *bucket;
    if (cell)
        do {
            if (DataCompare(cell->info, data) == 0) {
                DAct(cell->info);
                data = cell->info;
                break;
            }
            cell = cell->next;
        } while (cell != NULL);

    /*sterge celula ce contine data neactualizata cu frecventa*/
    LRemData(bucket, (int (*)(void *, void *))DataCompare, data);
    /*insereaza celula actualizata pentru a pastra sublista sortata*/
    LAddSorted(bucket, data, (int (*)(void *, void *))DataCompare);
}



/*Print */
void DataPrint(Data *p, FILE *file) {
    fprintf(file, "%s/%d", p->word, p->count);
}

void HPrint_Sublist(List bucket, FILE *file) {
    if (!bucket)
        fprintf(file, "VIDA");

    List cell = bucket;
    
    if (cell)
        do {

            DataPrint(cell->info, file);
            cell = cell->next;
            if (cell != NULL) fprintf(file, ", ");

        } while (cell != NULL);
}

void LenPrint(Cell *cell, FILE *file) {
    fprintf(file, "%d:", *(int *)(cell->info));
    HPrint_Sublist(cell->next, file);
}

void HPrint_Bucket(List bucket, FILE *file) {
    if (!bucket)
        fprintf(file, "VIDA");

    List cell = bucket;
    if (cell)
        do {
            fprintf(file, "(");
            LenPrint(cell->info, file);
            fprintf(file, ")");
            cell = cell->next;
        } while (cell != NULL);

    fprintf(file, "\n");
}

void HPrint(Hashtable *h, FILE *file) {
    int indx;
    for (indx = 0; indx < h->M; indx++) {
        List bucket = h->buckets[indx];
        if (bucket) {
            fprintf(file, "pos %d: ", indx);
            HPrint_Bucket(h->buckets[indx], file);
        }
    }
}


/*Print c n*/
void HPrintLen(Hashtable *h, char *c, int len, FILE *file)
{
    int cod = h->fh(c);
    List bucket = h->buckets[cod];

    int *length = (int *)malloc(sizeof(int));
    *length = len;
    Cell *link = LAlloc(length);
    
    List p = bucket;
    if (p)
        do {
            if (LenCompare(p->info, link) == 0){
                fprintf(file, "(");
                LenPrint(p->info, file);
                fprintf(file, ")\n");
                return;
            }
            p = p->next;
        } while (p != NULL);
}
 

/*Print n*/
int searchList(List list, int maxLen) {
    List p = list;
        if (p)
            do {
                Data * data = (Data*)(p->info);
                if(data->count <= maxLen) return 1;
                p = p->next;
            } while (p != NULL);
    return 0;
}

int DataPrintmaxLen(Data *p, FILE *file, int maxLen) {
    if (p->count > maxLen)
        return 0;
    fprintf(file, "%s/%d", p->word, p->count);
    return 1;
}

void HPrint_Sublist_maxLen(List bucket, FILE *file, int maxLen) {
    if (!bucket)
        fprintf(file, "VIDA");

    List cell = bucket;
    if (cell)
        do
        {
            int done = 0;
            if (((Data *)cell->info)->count <= maxLen) done = DataPrintmaxLen(cell->info, file, maxLen);
            
            cell = cell->next;
            
            if (cell != NULL && done != 0) fprintf(file, ", ");
        } while (cell != NULL);
}

void LenPrintmaxLen(Cell *cell, FILE *file, int maxLen) {
    if(searchList(cell->next, maxLen)) {
    fprintf(file, "%d: ", *(int *)(cell->info));
    HPrint_Sublist_maxLen(cell->next, file, maxLen);}
}

void HPrintMax(Hashtable *h, int maxLen, FILE *file) {
    int indx;
    int ok = 0;
    for (indx = 0; indx < h->M; indx++) {
        List bucket = h->buckets[indx];
        if (bucket) {
            List check = bucket;
            if (check)
                do {
                    List aux = (List)check->info;
                    ok = searchList(aux->next, maxLen);
                    if (ok == 1)
                        break;
                    check = check->next;
                } while (check != NULL);

            if (ok != 0) {
                fprintf(file, "pos%d: ", indx);

                List cell = bucket;
                if (cell)
                    do {
                        List aux = (List)cell->info;
                        if ((searchList(aux->next, maxLen)) == 1) {
                            fprintf(file, "(");
                            LenPrintmaxLen(cell->info, file, maxLen);
                            fprintf(file, ")");
                        }
                        cell = cell->next;
                    } while (cell != NULL);
                fprintf(file, "\n");
            }
        }
    }
}

void HFree(Hashtable **ah, TF elib_elem)
{
    List *p, el, aux;

    for (p = (*ah)->buckets; p < (*ah)->buckets + (*ah)->M; p++)
    {
        for (el = *p; el != NULL;)
        {
            aux = el;
            el = el->next;
            elib_elem(aux->info);
            free(aux);
        }
    }
    free((*ah)->buckets);
    free(*ah);
    *ah = NULL;
}