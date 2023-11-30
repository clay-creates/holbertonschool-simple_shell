#include "main.h"

/***/

int main(void)
{
    size_t buffsize = 1024;
    char *buffer = malloc(buffsize * sizeof(char));
    char *input_array;
    int characters;
    int i = 0;

    if (buffer == NULL)
    {
        perror("Buffer allocation failed.");
        exit(1);
    }

    while (!feof(stdin))
    {
        printf("$: ");
        characters = getline(&buffer, &buffsize, stdin);
        input_array = strtok(buffer, " ");
        printf("characters: %d\n", characters);

        while (input_array != NULL)
        {
            printf("%s\n", input_array);
            input_array = strtok(0, " ");
        }
    }
    return (0);
}