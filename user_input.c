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

/**
 * path_search - tokenizes copy of PATH to search for executable, given by user
 * @executable_name: name of command entered into user input (tokens[0])
 * @args: arguments for executable (found in tokens[1])
 */

void path_search(const char *executable_name, char *args)
{
	char *path = getenv("PATH");
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");

	while (dir != NULL)
	{
		char *executable_path = malloc(strlen(path_copy) + strlen(executable_name) + 2);
		if (executable_path == NULL)
		{
			perror("Memory allocation failed.");
			exit(1);
		}
		strcpy(executable_path, path_copy);
		strcat(executable_path, "/");
		strcat(executable_path, executable_name);
		if (access(executable_path, F_OK) == 0)
		{
			printf("Found executable at %s\n", executable_path); /** need to execute if found */

			__pid_t pid = fork();
			if (pid < 0)
			{
				perror("Fork failed.");
				exit(1);
			}

			if (pid == 0)
			{
				char *exec_args[] = {executable_path, args, NULL};
				execve(executable_path, exec_args, NULL);

				perror("Execve failed.");
				exit(1);
			}

			if (pid > 0)
			{
				int status;
				wait(&status);
				if (WIFEXITED(status))
				{
					printf("Child process exited with status %d\n", WEXITSTATUS(status));
				}
			}
		}
		else
		{
			printf("Command not found: %s\n", executable_name);
		}
		free(executable_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
}

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
		if (tokens[0] = NULL)
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
