#include "rank.h"
#include "utils.h"

#include <stdlib.h>

double *get_ranks(const Graph graph)
{
    double *ranks = malloc(graph.n * sizeof(*ranks));
    ASSERT(ranks != NULL);
    for (int i = 0; i < graph.n; i++)
    {
        int sum = 0, count = 0;
        for (int j = 0; j < graph.n; j++)
        {
            if (graph.matrix[i][j] != 0)
            {
                sum += graph.matrix[i][j];
                count++;
            }
        }
        if (count == 0)
        {
            ranks[i] = 0.5;
        }
        else
        {
            ranks[i] = (double)sum / count;
        }
    }
    return ranks;
}

int *get_top_indexes(double *list, int count, int top_count)
{
    ASSERT(top_count <= count);

    int *top_indexes = calloc(top_count, sizeof(*top_indexes));
    ASSERT(top_indexes != NULL);

    double top_min_value = list[0];
    int top_min_index = 0;
    for (int i = 0; i < top_count; i++) {
        top_indexes[i] = i;
        if (list[i] < top_min_value)
        {
            top_min_index = i;
            top_min_value = list[i];
        }
    }

    for (int i = top_count; i < count; i++)
    {
        if (list[i] > top_min_value)
        {
            /* insert i to top indexes */
            top_indexes[top_min_index] = i;
            /* update top min value and index */
            top_min_value = list[i];
            for (int j = 0; j < top_count; j++)
            {
                if (list[top_indexes[j]] < top_min_value)
                {
                    top_min_index = j;
                    top_min_value = list[top_indexes[j]];
                }
            }
        }
    }
    return top_indexes;
}