#include "main.h"

/**
 * safe_malloc - helper function to allocate memory
 * @size: size to allocate memory for
 *
 * Return: returns pointer to allocated memory
 */

char *safe_malloc(size_t size)
{
	char *ptr = malloc(size);
	if (ptr == NULL)
	{
		perror("Memory allocation failed.");
		exit(1);
	}
	return ptr;
}

int main(void)
{
	return (0);
}
