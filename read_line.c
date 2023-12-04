#include "main.h"

/**
 * read_line - uses getline to recieve and save user input in buffer variable
 *
 * Return: returns the buffer array, with user input saved
 */

char *read_line(void)
{
	size_t buffsize = 1024;
	char *buffer = malloc(buffsize * sizeof(char));
	if (buffer == NULL)
	{
		perror("Buffer allocation failed.");
		exit(1);
	}
	printf("$: ");
	int characters = getline(&buffer, &buffsize, stdin);
	if (characters == -1)
	{
		perror("Error reading line");
		exit(1);
	}
	return buffer;
}
