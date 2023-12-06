#ifndef MAIN
#define MAIN

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stddef.h>
#include <unistd.h>
#include <sys/wait.h>
#include <libgen.h>

char *read_line(void);
char **tokenize_line(char *buffer);
void path_search(char **tokens);

#endif