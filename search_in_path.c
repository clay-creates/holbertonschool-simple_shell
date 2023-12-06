#include "main.h"

/**
 * search_in_path - searches for an executable in the PATH
 * @path: the path string
 * @tokens: saved and tokenized user input
 */

void search_in_path(char *path, char **tokens)
{
	char *path_copy = strdup(path);
	char *dir = strtok(path_copy, ":");
	__pid_t pid, wait_pid;
	int exec_status;
	char *base_name = basename(strdup(tokens[0]));
	char *executable_path = malloc(strlen(dir) + strlen(base_name) + 2);

	if (path_copy == NULL)
	{
		perror("Error copying PATH");
		exit(EXIT_FAILURE);
	}

	if (executable_path == NULL)
	{
		perror("Error allocating memory for executable path");
		exit(EXIT_FAILURE);
	}

	while (dir != NULL)
	{
		strcpy(executable_path, dir);
		strcat(executable_path, "/");
		strcat(executable_path, base_name);

		if (access(executable_path, F_OK | X_OK) == 0)
		{
			pid = fork();

			if (pid < 0)
			{
				perror("Fork failed");
				exit(EXIT_FAILURE);
			}

			if (pid == 0)
			{
				char *tokens[0] = executable_path;
				exec_status = execve(executable_path, tokens, NULL);

				if (exec_status == -1)
				{
					perror("Execve failed");
					exit(EXIT_FAILURE);
				}
			}
			else if (pid > 0)
			{
				wait_pid = waitpid(pid, &exec_status, 0);
				if (wait_pid == -1)
				{
					perror("Error waiting for child process");
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				printf("Command not found: %s\n", tokens[0]);
			}
			break;
		}
		free(executable_path);
		dir = strtok(NULL, ":");
	}
	free(path_copy);
}
