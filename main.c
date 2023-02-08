#include "io.h"
#include "rank.h"
#include "graph.h"
#include "compare.h"
#include "utils.h"

#include <stdio.h>
#include <stdlib.h>

void compare_two_steps(char **names, int count, int sample, int top_count)
{
    Graph graph = compare_sample(names, count, sample);
    double *ranks = get_ranks(graph);
    int *top_indexes = get_top_indexes(ranks, count, top_count);

    char **top_names = malloc(top_count * sizeof(*top_names));
    ASSERT(top_names != NULL);
    for (int i = 0; i < top_count; i++)
    {
        top_names[i] = names[top_indexes[i]];
    }
    Graph top_graph = compare_all(top_names, top_count);
    double *top_ranks = get_ranks(top_graph);
    print_ranks(top_ranks, top_names, top_count);

    free_graph(graph);
    free(ranks);
    free(top_indexes);
    free(top_names);
    free_graph(top_graph);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: %s <input>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    char **names;
    int count;
    read_names(argv[1], &names, &count);
    compare_two_steps(names, count, 4, 5);

    for (int i = 0; i < count; i++)
    {
        free(names[i]);
    }
    free(names);
}