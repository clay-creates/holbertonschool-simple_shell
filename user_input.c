#include "main.h"

char *read_line(void);
char **tokenize_line(char *buffer);
void path_search(const char *executable_name, char *args);

/** Bug Check Note: shell seg faults (and dumps memory on first command call on open (consistently)). Works effectively after, but need to find source of segfault */

/**
 * main - entry point for shell, creates infinite loop to start shell process
 *
 * Return: Return 0 on success
 */

int main(void)
{
	while (!feof(stdin))
	{
		char *buffer = read_line();
		char **tokens = tokenize_line(buffer);
		if (tokens[0] == NULL)
		{
			perror("Error tokenizing line.");
			exit(1);
		}
		path_search(tokens[0], tokens[1]);
		free(tokens);
		free(buffer);
	}
	return 0;
}
