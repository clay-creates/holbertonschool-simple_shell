#include "main.h"

/**
 * path_search - tokenizes copy of PATH to search for executable, given by user
 * @executable_name: name of command entered into user input (tokens[0])
 * @args: arguments for executable (found in tokens[1])
 */

void path_search(char **tokens)
{
    extern char **environ;
    char *path = NULL;

    for (int i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], "PATH=", 5) == 0)
        {
            path = strdup(environ[i] + 5);
            break;
        }
    }

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
        char *base_name = basename(strdup(tokens[0]));
        char *executable_path = malloc(strlen(dir) + strlen(base_name) + 2);

        if (executable_path == NULL)
        {
            perror("Error allocating memory for executable path");
            exit(EXIT_FAILURE);
        }

        strcpy(executable_path, dir);
        strcat(executable_path, "/");
        strcat(executable_path, base_name);

        if (access(executable_path, F_OK | X_OK) == 0)
        {
            /**printf("Found executable at %s\n", executable_path); need to execute if found */

            pid = fork();

            if (pid < 0)
            {
                perror("Fork failed.");
                exit(EXIT_FAILURE);
            }

            if (pid == 0)
            {
                tokens[0] = executable_path;

                exec_status = execve(executable_path, tokens, NULL);

                if (exec_status == -1)
                {
                    perror("Execve failed");
                    free(tokens);
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
                if (WIFEXITED(exec_status))
                {
                    /**printf("Child process exited with status %d\n", WEXITSTATUS(exec_status));*/
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
