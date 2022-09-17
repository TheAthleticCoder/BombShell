#include "headers.h"

void redirect(char **tokens)
{
    //check and flag for >, <, >>
    int input_flag = 0;
    int output_flag = 0;
    int append_flag = 0;
    int i = 0;
    //store file name
    char *input_file_name = malloc(sizeof(char) * 100);
    char *output_file_name = malloc(sizeof(char) * 100);
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "<") == 0)
        {
            input_flag = 1;
            strcpy(input_file_name, tokens[i + 1]);
            // break;
        }
        else if (strcmp(tokens[i], ">") == 0)
        {
            // printf("hiya\n");
            output_flag = 1;
            strcpy(output_file_name, tokens[i + 1]);
            // break;
        }
        else if (strcmp(tokens[i], ">>") == 0)
        {
            append_flag = 1;
            strcpy(output_file_name, tokens[i + 1]);
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
        if (strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], ">>") == 0)
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
    if (input_flag == 1)
    {
        FILE *fp = fopen(input_file_name, "r");
        if (fp == NULL)
        {
            perror("fopen:");
            return;
        }
        fclose(fp);
    }
    if (output_flag == 1)
    {
        FILE *fp = fopen(output_file_name, "w");
        if (fp == NULL)
        {
            perror("fopen:");
            return;
        }
        fclose(fp);
    }
    if (append_flag == 1)
    {
        FILE *fp = fopen(output_file_name, "a");
        if (fp == NULL)
        {
            perror("fopen:");
            return;
        }
        fclose(fp);
    }
    //openin and opening files
    int fd_in = 0;
    int fd_out = 0;
    if (input_flag == 1)
    {
        fd_in = open(input_file_name, O_RDONLY);
        if (fd_in == -1)
        {
            perror("open:");
            return;
        }
    }
    if (output_flag == 1)
    {
        fd_out = open(output_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644);
        if (fd_out == -1)
        {
            perror("open:");
            return;
        }
    }
    if (append_flag == 1)
    {
        fd_out = open(output_file_name, O_WRONLY | O_CREAT | O_APPEND, 0644);
        if (fd_out == -1)
        {
            perror("open:");
            return;
        }
    }
    //forking
    pid_t pid = fork();
    if (pid == 0)
    {
        //child
        //redirecting
        if (input_flag == 1)
        {
            dup2(fd_in, 0);
            close(fd_in);
        }
        if (output_flag == 1 || append_flag == 1)
        {
            dup2(fd_out, 1);
            close(fd_out);
        }

        if (execvp(tokens[0], tokens) == -1)
        {
            perror("execvp:");
            exit(1);
        }
    }
    else if (pid > 0)
    {
        //parent
        //wait for child to finish
        int status;
        waitpid(pid, &status, 0);
    }
    else
    {
        perror("fork:");
    }
    //freeing memory
    free(input_file_name);
    free(output_file_name);
}