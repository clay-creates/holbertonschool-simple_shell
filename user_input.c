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

void print_words(char *token)
{
	while (token != NULL)
	{
		printf("%s\n", token);
		token = strtok(NULL, " \t\n\r");
	}
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

/**int main(void)
{
	size_t buffsize = 1024;
	char *buffer = malloc(buffsize * sizeof(char));
	char *input_array;
	int characters;
	int i = 0;

	if (buffer == NULL || strlen(buffer) == 0)
	{
		fprintf(stderr, "Invalid input. \n");
		exit(1);
	}

	while (!feof(stdin))
	{
		printf("$: ");
		characters = getline(&buffer, &buffsize, stdin);
		input_array = strtok(buffer, " \t\n\r");
		printf("characters: %d\n", characters);

		while (input_array != NULL)
		{
			printf("%s\n", input_array);
			input_array = strtok(0, " ");
		}
	}
	return (0);
}*/