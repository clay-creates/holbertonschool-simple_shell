#include "main.h"

/***/

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
        }
        free(executable_path);
        path_token = strtok(NULL, ":");
    }
}
