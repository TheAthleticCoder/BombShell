#include "headers.h"

// FUNCTION TO TAKE IN COMMAND AND TOKEN AND EXECUTE
void input_to_execute(char *command, char **tokens)
{
    // check if tokens have >, <, >>
    //print arg_count
    // printf("%d\n", arg_count);
    int i = 0;
    int redirect_flag = 0;
    int pipe_flag = 0;
    while (i < arg_count - 1)
    {
        if (strcmp(tokens[i], ">") == 0 || strcmp(tokens[i], "<") == 0 || strcmp(tokens[i], ">>") == 0)
        {
            redirect_flag = 1;
            break;
        }
        else if (strcmp(tokens[i], "|") == 0)
        {
            pipe_flag = 1;
            break;
        }
        i++;
    }

    //if pipe_flag is set, tokenize
    // if tokens have >, <, >>, call redirect function
    if (redirect_flag == 1)
    {
        tokens[arg_count - 1] = NULL;
        char **shift_tokens = malloc(sizeof(char *) * TOK_MAX);
        shift_tokens[0] = malloc(sizeof(char) * TOK_MAX);
        strcpy(shift_tokens[0], command);
        int i = 1;
        // printf("hiya\n");
        while (tokens[i - 1] != NULL)
        {
            shift_tokens[i] = malloc(sizeof(char) * TOK_MAX);
            strcpy(shift_tokens[i], tokens[i - 1]);
            i++;
        }
        shift_tokens[i] = NULL;
        // printf("hiya\n");
        redirect(shift_tokens);
        free(shift_tokens);
        // printf("hiya\n");
        // redirect(command, tokens);
    }
    else
    {
        // printf("hi\n");
        // tokens[arg_count - 1] = NULL;
        // strcmp to check if command is cd
        if (strcmp(command, "cd") == 0)
        {
            if (arg_count - 1 > 1)
            {
                printf("%d\n", rand());
                perror("Too many arguments");
                return -1;
            }
            cd(tokens);
        }
        // strcmp to check if command is pwd
        else if (strcmp(command, "pwd") == 0)
        {
            if (arg_count - 1 > 0)
            {
                perror("Too many arguments");
                return -1;
            }
            else
            {
                char cwd[CWD_MAX];
                if (getcwd(cwd, sizeof(cwd)) != NULL)
                {
                    printf("%s\n", cwd);
                }
            }
        }
        // strcmp to check if command is echo
        else if (strcmp(command, "echo") == 0)
        {
            echo(tokens);
        }
        // strcmp to check if command is ls
        else if (strcmp(command, "ls") == 0)
        {
            ls(tokens);
        }
        // strcmp to check if command is pinfo
        else if (strcmp(command, "pinfo") == 0)
        {
            pinfo(tokens);
        }
        // strcmp to check if command is discover
        else if (strcmp(command, "discover") == 0)
        {
            discover(tokens);
        }
        // strcmp to check if command is history
        else if (strcmp(command, "history") == 0)
        {
            displayHistory(tokens);
        }
        // strcmp to check if command is exit
        else if (strcmp(command, "exit") == 0)
        {
            exit(0);
        }
        else if (strcmp(command, "jobs") == 0)
        {
            // print a random number
            //  printf("%d\n", rand());
            jobs(command, tokens);
        }
        else if (strcmp(command, "sig") == 0)
        {
            // if more than 2 arguments, print error
            if (arg_count - 1 > 2)
            {
                perror("Too many arguments");
                return -1;
            }
            sig(command, tokens);
        }
        else if (strcmp(command, "fg") == 0)
        {
            // print a random number
            //  printf("%d\n", rand());
            foreground(tokens);
        }
        else if (strcmp(command, "bg") == 0)
        {
            // print a random number
            //  printf("%d\n", rand());
            background(tokens);
        }
        else
        {
            // setting last token to NULL to prevent garbage value from passing
            // printf("hi\n");
            tokens[arg_count - 1] = NULL;
            // print command and tokens
            // printf("command: %s\n", command);
            // int i = 0;
            // while (tokens[i] != NULL)
            // {
            //     printf("tokens[%d]: %s\n", i, tokens[i]);
            //     i++;
            // }
            run_fore_back(command, tokens);
        }
    }
}
