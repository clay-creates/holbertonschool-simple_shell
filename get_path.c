#include "main.h"

/**
 * get_path - finds the PATH environment
 *
 * Return: returns a null terminated string containing the PATH
 */

char *get_path(void)
{
	extern char **environ;
	char *path = NULL;
	int i;

	for (i = 0; environ[i] != NULL; i++)
	{
		if (strncmp(environ[i], "PATH=", 5) == 0)
		{
			path = strdup(__environ[i] + 5);
			break;
		}
	}

	if (path == NULL)
	{
		perror("PATH not found");
		exit(EXIT_FAILURE);
	}

	return (path);
}

int main(void)
{
	return (0);
}