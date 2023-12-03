#include "main.h"

/**
 * tokenize_line - uses strtok to create tokens from user input (saved in buffer)
 * @buffer: array holding user input (from read_line)
 *
 * Return: array of tokens created from user input
 */

char **tokenize_line(char *buffer)
{
	char **tokens = malloc(2 * sizeof(char *));
	tokens[0] = strtok(buffer, " \t\n\r");
	tokens[1] = strtok(NULL, " \t\n\r");
	if (tokens == NULL)
	{
		perror("Error tokenizing line");
		exit(1);
	}
	return tokens;
}
