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

void path_search(const char *executable_name)
{
	char *path = getenv("PATH");
	char *path_token = strtok(path, ":");

	while (path_token != NULL)
	{
		char *executable_path = malloc(strlen(path_token) + strlen(executable_name) + 2);
		if (executable_path == NULL)
		{
			perror("Memory allocation failed.");
			exit(1);
		}
		strcpy(executable_path, path_token);
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
				char *args[] = {executable_path, NULL};
				execve(executable_path, args, NULL);

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
		free(executable_path);
		path_token = strtok(NULL, ":");
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
