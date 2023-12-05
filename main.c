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
	char *token = strtok(buffer, " \t\n\r");

	while (token != NULL)
	{
		tokens[i] = token;
		i++;
		token = strtok(NULL, " \t\n\r");
	}

	tokens[i] = NULL;

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
	printf("PATH: %s\n", getenv("PATH"));

	char *path_copy = strdup(path);

	if (path_copy == NULL)
	{
		perror("Error copying PATH");
		exit(EXIT_FAILURE);
	}

	char *dir = strtok(path_copy, ":");
	__pid_t pid, wait_pid;
	int exec_status;

	while (dir != NULL)
	{
		char *base_name = basename(strdup(executable_name));
		char *executable_path = malloc(strlen(dir) + strlen(base_name) + 2);

		if (executable_path == NULL)
		{
			perror("Error allocating memory for executable path");
			exit(EXIT_FAILURE);
		}

		strcpy(executable_path, dir);
		/**strcat(executable_path, "/");
		strcat(executable_path, base_name);*/

		if (access(executable_path, F_OK) == 0)
		{
			printf("Found executable at %s\n", executable_path); /** need to execute if found */

			pid = fork();

			if (pid < 0)
			{
				perror("Fork failed.");
				exit(EXIT_FAILURE);
			}

			if (pid == 0)
			{
				char *exec_args[3];
				exec_args[0] = executable_path;
				exec_args[1] = args;
				exec_args[2] = NULL;

				exec_status = execve(executable_path, exec_args, NULL);

				if (exec_status == -1)
				{
					perror("Execve failed");
					free(args);
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				wait_pid = waitpid(pid, &exec_status, 0);
				if (wait_pid == -1)
				{
					perror("Error waiting for child process");
					exit(EXIT_FAILURE);
				}
				if (WIFEXITED(exec_status))
				{
					printf("Child process exited with status %d\n", WEXITSTATUS(exec_status));
				}
			}
		}
		else
		{
			printf("Command not found: %s\n", executable_name);
			exit(EXIT_FAILURE);
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
	while (1)
	{
		printf("$: ");
		char *buffer = read_line();
		char **tokens = tokenize_line(buffer);

		if (tokens[0] != NULL)
		{
			path_search(tokens[0], tokens[1]);
		}

		free(tokens);
		free(buffer);
	}
	return 0;
}
