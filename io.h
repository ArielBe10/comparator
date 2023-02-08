#pragma once

void read_names(const char *filename, char ***pnames, int *pcount);

int ask_choice(char **names, int option1, int option2);

void print_ranks(const double *ranks, char **names, int count);

char *trim(const char *str);