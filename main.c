#include "main.h"

/** Bug Check Note: shell seg faults (and dumps memory on first command call on open (consistently)). Works effectively after, but need to find source of segfault */

/**
 * main - entry point for shell, creates infinite loop to start shell process
 *
 * Return: Return 0 on success
 */

int main(void)
{
	while (1)
	{
		printf("$: ");
		char *buffer = read_line();
		char **tokens = tokenize_line(buffer);

		if (tokens[0] != NULL)
		{
			path_search(tokens);
		}

		free(tokens);
		free(buffer);
	}
	return 0;
}
