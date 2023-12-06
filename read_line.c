#include "main.h"

/**
 * read_line - uses getline to recieve and save user input in buffer variable
 *
 * Return: returns the buffer array, with user input saved
 */

char *read_line(void)
{
    size_t buffsize = 0;
    char *buffer = NULL;
    getline(&buffer, &buffsize, stdin);

    if (buffer == NULL)
    {
        perror("Buffer allocation failed.");
        exit(1);
    }

    return buffer;
}
