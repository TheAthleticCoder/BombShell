#include "headers.h"

// FUNCTION TO TAKE IN COMMAND AND TOKEN AND EXECUTE
void input_to_execute(char *command, char **tokens)
{
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
    else
    {
        //setting last token to NULL to prevent garbage value from passing
        tokens[arg_count - 1] = NULL;
        run_fore_back(command, tokens);
    }
}
