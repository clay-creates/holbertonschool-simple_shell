#include "main.h"

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
