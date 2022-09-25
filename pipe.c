#include "headers.h"

void pipe(char **tokens)
{
    //check and flag for pipe
    int pipe_flag = 0;
    int i = 0;
    //store file name
    char *input_file_name = malloc(sizeof(char) * 100);
    char *output_file_name = malloc(sizeof(char) * 100);
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            pipe_flag = 1;
            // break;
        }
        i++;
    }
    // remove >, <, >> based on flags and store in new tokens
    char **new_tokens = malloc(sizeof(char *) * TOK_MAX);
    int j = 0;
    i = 0;
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "|") == 0)
        {
            i++;
        }
        else
        {
            new_tokens[j] = malloc(sizeof(char) * TOK_MAX);
            strcpy(new_tokens[j], tokens[i]);
            j++;
        }
        i++;
    }
    new_tokens[j] = NULL;
    tokens = new_tokens;

    //check if files exist based on flags
    if (pipe_flag == 1)
    {
        // FILE *fp = fopen(input_file_name, "r");
        // if (fp == NULL)
        // {
        //     perror("File does not exist");
        //     return;
        // }
        // else
        // {
        //     fclose(fp);
        // }
    }
}