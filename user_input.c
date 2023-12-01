#include "main.h"

/***/

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

char *tokenize_line(char *buffer)
{
	char *token = strtok(buffer, " \t\n\r");
	if (token == NULL)
	{
		perror("Error tokenizing line");
		exit(1);
	}
	return token;
}

int main(void)
{
	while (!feof(stdin))
	{
		char *buffer = read_line();
		char *executable_name = tokenize_line(buffer);
		path_search(executable_name);
		free(buffer);
	}
	return 0;
}
