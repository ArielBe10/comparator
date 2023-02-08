#include "compare.h"
#include "io.h"
#include "graph.h"
#include "utils.h"

#include <stdlib.h>

static void set_matrix(int choice, Graph graph, int i, int j)
{
    if (choice == 1)
    {
        graph.matrix[i][j] = 1;
        graph.matrix[j][i] = -1;
    }
    else
    {
        graph.matrix[i][j] = -1;
        graph.matrix[j][i] = 1;
    }
}

Graph compare_all(char **names, int count)
{
    Graph graph = allocate_graph(count);

    for (int i = 0; i < count; i++)
    {
        for (int j = 0; j < count; j++)
        {
            if (i != j && graph.matrix[i][j] == 0)
            {
                int choice = ask_choice(names, i, j);
                set_matrix(choice, graph, i, j);
            }
        }
    }
    return graph;
}

Graph compare_sample(char **names, int count, int sample)
{
    /* sample > count-1 is impossible */
    if (sample > count - 1)
    {
        sample = count - 1;
    }

    Graph graph = allocate_graph(count);

    int *compare_count = calloc(count, sizeof(*compare_count));
    ASSERT(compare_count != NULL);

    for (int i = 0; i < count; i++)
    {
        /* if there are not enough candidates to compare with, compare with previous names */
        int candidates = 0, allow_previous = 0;
        for (int j = i + 1; j < count; j++)
        {
            if (graph.matrix[i][j] == 0 && compare_count[j] < sample)
            {
                candidates++;
            }
        }
        if (candidates + compare_count[i] < sample)
        {
            allow_previous = 1;
        }

        while (compare_count[i] < sample)
        {
            int rand_min = i + 1, rand_max = count - 1;
            if (allow_previous)
            {
                rand_min = 0;
            }

            int j = rand_min + rand() % (rand_max - rand_min + 1);

            if ((compare_count[j] >= sample && !allow_previous) || graph.matrix[i][j] != 0 || i == j)
                continue;

            compare_count[i]++;
            compare_count[j]++;

            set_matrix(ask_choice(names, i, j), graph, i, j);
        }
    }
    free(compare_count);
    return graph;
}