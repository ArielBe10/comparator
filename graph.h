#pragma once

typedef struct
{
    int n;
    char **matrix;
} Graph;

Graph allocate_graph(int n);
void free_graph(Graph graph);