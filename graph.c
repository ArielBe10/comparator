#include "graph.h"
#include "utils.h"

#include <stdlib.h>

Graph allocate_graph(int n)
{
    Graph graph;
    graph.n = n;
    graph.matrix = malloc(n * sizeof(graph.matrix[0]));
    ASSERT(graph.matrix != NULL);
    for (int i = 0; i < n; i++)
    {
        graph.matrix[i] = calloc(n, sizeof(graph.matrix[0][0]));
        ASSERT(graph.matrix[i] != NULL);
    }
    return graph;
}

void free_graph(Graph graph)
{
    for (int i = 0; i < graph.n; i++)
    {
        free(graph.matrix[i]);
    }
    free(graph.matrix);
}