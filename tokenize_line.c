#include "main.h"

/**
 * tokenize_line - uses strtok to create tokens from user input (saved in buffer)
 * @buffer: array holding user input (from read_line)
 *
 * Return: array of tokens created from user input
 */

char **tokenize_line(char *buffer)
{
    int i = 0;
    char **tokens = malloc(100 * sizeof(char *));
    if (tokens == NULL)
    {
        perror("Error tokenizing line");
        exit(1);
    }

    char *token = strtok(buffer, " \t\n\r");

    while (token != NULL)
    {
        tokens[i] = token;
        i++;
        token = strtok(NULL, " \t\n\r");
    }

    tokens[i] = NULL;

    return tokens;
}
