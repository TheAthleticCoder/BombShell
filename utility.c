#include "headers.h"
int arg_count = 0;
int piped_count = 0;

// a function which takes in the input string
char printer(char *input)
{
    // if input is equal to home, print ~
    if (strcmp(input, home) == 0)
    {
        printf("~");
        printf("\n");
    }
    // else print ~ and the rest of the string
    else
    {
        printf("~%s", input + strlen(home));
        printf("\n");
    }
}

// FUNCTION TO REMOVE EXTRA SPACES
char *remove_extra_spaces(char *str)
{
    int i = 0, j = 0;
    while (str[i])
    {
        while (str[i] == ' ' && str[i + 1] == ' ')
        {
            i++;
        }
        str[j++] = str[i++];
    }
    str[j] = '\0';
    return str;
}

// FUNCTION TO TOKENIZE THE RECIEVED ARGUMENT BASED ON SPACES AND RETURN COMMAND+TOKENS
char **input_tokenize(char *input)
{
    arg_count = 0;
    char *save_pointer;
    char *delimiter = " \t";
    char *args = strtok_r(remove_extra_spaces(input), delimiter, &save_pointer);
    // print args
    //  char command[CMD_MAX];
    // declare command of size CMD_MAX
    char *command = malloc(sizeof(char) * CMD_MAX);
    // declare tokens of size TOKEN_MAX*TOKEN_MAX
    char **tokens = malloc(sizeof(char *) * TOK_MAX);
    // char tokens[TOK_MAX][TOK_MAX];
    // initialize tokens to NULL
    // print all arguments
    while (args != NULL)
    {
        // storing command from 1st argument
        if (arg_count == 0)
        {
            strcpy(command, args);
            // print command
            //  printf("%s\n", command);
            args = strtok_r(NULL, delimiter, &save_pointer);
        }
        else
        { // storing other args as tokens using pointers
            tokens[arg_count - 1] = args;
            // printf("%s\n", tokens[arg_count-1]);
            args = strtok_r(NULL, delimiter, &save_pointer);
        }
        arg_count++;
    }
    // if there is no command perror
    if (arg_count == 0)
    {
        perror("No command entered");
        return NULL;
    }
    else
    {
        // input to execute
        input_to_execute(command, tokens);
        // print tokens
    }
    free(args);
    free(command);
    free(tokens);
}

char **pipe_tokenize(char *input)
{
    // tokenize based on delimiter '|' for pipes
    piped_count = 0;
    char *save_pointer;
    char *delimiter = "|";
    char *piped = strtok_r(remove_extra_spaces(input), delimiter, &save_pointer);
    // declare tokens of size TOKEN_MAX*TOKEN_MAX
    char **piped_tokens = malloc(sizeof(char *) * TOK_MAX);
    while (piped != NULL)
    {
        piped_tokens[piped_count] = piped;
        piped = strtok_r(NULL, delimiter, &save_pointer);
        piped_count++;
    }
    // implement piping
    // print piped_count
    pipe_execute(piped_tokens);
    free(piped);
    free(piped_tokens);
}

void pipe_execute(char **piped_tokens)
{
    // if piped_count is 1, then no piping
    if (piped_count == 1)
    {
        // printf("No piping\n");
        input_tokenize(piped_tokens[0]);
    }
    else
    {
        // implement piping
        int first_STDIN = dup(STDIN_FILENO);
        int first_STDOUT = dup(STDOUT_FILENO);
        int prev_read = STDIN_FILENO;
        int fd[2];
        int i = 0;
        for(i = 0; i< piped_count; i++)
        {
            pipe(fd);
            pid_t pid = fork();
            if(pid<0)
            {
                perror("Fork failed");
                exit(1);
            }
            else if(pid == 0)
            {
                //child process
                dup2(prev_read, STDIN_FILENO);
                if(i != piped_count-1)
                {
                    dup2(fd[1], STDOUT_FILENO);
                }
                close(fd[0]);
                // printf("hihihihihihihihi\n\n");
                input_tokenize(piped_tokens[i]);
                exit(0);
            }
            else{
                //parent process
                wait(NULL);
                close(fd[1]);
                prev_read = fd[0];
            }
        }
        dup2(first_STDIN, STDIN_FILENO);
        dup2(first_STDOUT, STDOUT_FILENO);
    }
}
