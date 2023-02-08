#include "io.h"
#include "utils.h"

#include <stdio.h>
#include <string.h>
#include <ctype.h>

char *trim(const char *str)
{
    if (str == NULL)
    {
        return NULL;
    }

    int start = 0, end = strlen(str);
    while (isspace((unsigned char)str[start]))
    {
        start++;
    }
    while (end > 0 && isspace((unsigned char)str[end - 1]))
    {
        end--;
    }

    char *new_str = malloc(end - start + 1);
    ASSERT(new_str != NULL);
    for (int i = 0; i < end - start; i++)
    {
        new_str[i] = str[start + i];
    }
    new_str[end - start] = '\0';
    return new_str;
}

void read_names(const char *filename, char ***pnames, int *pcount)
{
    FILE *fp;
    size_t line_size;
    int count = 0;
    char **names;
    char *line;

    names = malloc(sizeof(char *));
    ASSERT(names != NULL);
    fp = fopen(filename, "r");
    ASSERT(fp != NULL);

    while (getline(&line, &line_size, fp) != -1)
    {
        names[count] = trim(line);
        count++;
        names = realloc(names, (count + 1) * sizeof(char *));
        ASSERT(names != NULL);
    }
    free(line);
    fclose(fp);

    *pnames = names;
    *pcount = count;
}

int ask_choice(char **names, int option1, int option2)
{
    int choice = 0;
    char *line = NULL;
    size_t line_size = 0;

    printf("Choose:\n");
    printf("1. %s\n", names[option1]);
    printf("2. %s\n", names[option2]);

    while (1)
    {
        ASSERT(getline(&line, &line_size, stdin) != -1);
        if (strcmp(line, "1\n") == 0)
        {
            choice = 1;
            break;
        }
        if (strcmp(line, "2\n") == 0)
        {
            choice = 2;
            break;
        }
        printf("Choice should be 1 or 2 only.\n");
    }
    free(line);
    return choice;
}

void print_ranks(const double *ranks, char **names, int count)
{
    printf("Results:\n");
    for (int i = 0; i < count; i++)
    {
        int rank = (ranks[i] + 1) / 2 * 100 + 0.5;
        printf("%s: %d%%\n", names[i], rank);
    }
}