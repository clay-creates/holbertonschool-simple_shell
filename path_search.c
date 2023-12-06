#include "main.h"

/**
 * path_search - calls get_path and search_in_path to find executables in path and execute them
 * @tokens: array of tokenized user input
 */

void path_search(char **tokens)
{
    char *path = get_path();
    search_in_path(path, tokens);
    free(path);
}
