#pragma once

#include "graph.h"

double *get_ranks(const Graph graph);

int *get_top_indexes(double *list, int count, int top_count);