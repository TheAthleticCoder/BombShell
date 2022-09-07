#include "headers.h"

// Function for ECHO Command
void echo(char **tokens)
{
    for (int i = 0; i < arg_count - 1; i++)
    {
        printf("%s ", tokens[i]);
    }
    printf("\n");
}
