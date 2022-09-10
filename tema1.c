/* Anton Dumitrita 324CB*/

#include "Hash.h"

int main(int argc, char *argv[])
{
    
    if(argc != 2) return 0;
    char *input_filename = argv[1];

    int M = 26;

    FILE *f;
    size_t len = 0;
    Hashtable *h = HInit(M, codHash);

    f = fopen(input_filename, "rt");
    if (f == NULL)
        return 0;

    char *lines[1000];
    int line_count = 0;
    while (1)
    {
        char *line = malloc(1000);
        lines[line_count++] = line;
        if (getline(&line, &len, f) == -1)
            break;

        char *command = strtok(line, " ");

        if (command[strlen(command) - 1] == '\n')
            command[strlen(command) - 1] = '\0';

        if (!strcmp(command, "insert"))
        {
            char *word = strtok(NULL, " ");

            while (word != NULL)
            {

                if (word[strlen(word) - 1] == '\n')
                    word[strlen(word) - 1] = '\0';
                 if (word[strlen(word) - 1] == '.' || word[strlen(word) - 1] == ',')
                    word[strlen(word) - 1] = '\0';

                if (strlen(word) >= 3)
                    HInsert(h, (void *)word);

                word = strtok(NULL, " ");
            }
        }
        else if (!strcmp(command, "print"))
        {
            char *p = strtok(NULL, " ");
            if (p == NULL)
            {
                HPrint(h, stdout);
            }
            else
            {
                char *first = p;
                char *second = strtok(NULL, " ");
                if (second != NULL)
                {
                    int length = atoi(second);
                    HPrintLen(h, first, length, stdout);
                } else {
                    int maxLen = atoi(first);
                   HPrintMax(h, maxLen, stdout);
                }
                      
            }
    }
    }

    int i;
    for (i = 0; i < line_count; i++)
        free(lines[i]);
    //HFree(h);
    fclose(f);
    return 0;
}