#include "headers.h"

// store history commands in a 2D array
char history_array[MAX_HISTORY][BUFFER_MAX];
int cmd_count = 0;

void historyWriter(char *input)
{
    // open history file
    FILE *fp = fopen("history.txt", "a");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    // write input to history file
    fprintf(fp, "%s\n", input);
    // close history file
    fclose(fp);
}

void historyLoader()
{
    // open history file
    char *path = (char *)malloc(sizeof(char) * BUFFER_MAX);
    strcpy(path, home);
    strcat(path, "/history.txt");
    FILE *fp = fopen(path, "r");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    size_t buffer_size = BUFFER_MAX;
    char *buffer = malloc(sizeof(char) * buffer_size);
    if (buffer == NULL)
    {
        perror("malloc");
        return;
    }
    getline(&buffer, &buffer_size, fp);
    // storing number of commands in cmd_count
    cmd_count = atoi(buffer);
    // copying history commands to history_array
    int i = 0;
    while (i < cmd_count)
    {
        getline(&buffer, &buffer_size, fp);
        // copying buffer value without newline character
        strncpy(history_array[i], buffer, strlen(buffer) - 1);
        i++;
    }
    free(buffer);
    free(path);
    fclose(fp);
}

void changeHistory(char *command)
{
    // If 20 commands are already saved, we erase the oldest(hist_commands[0]) and append the latest command
    if (cmd_count == MAX_HISTORY)
    {
        int i = 0;
        while (i < MAX_HISTORY - 1)
        {
            strcpy(history_array[i], history_array[i + 1]);
            i++;
        }
        strcpy(history_array[MAX_HISTORY - 1], command);
    }
    else
    {
        strcpy(history_array[cmd_count], command);
        cmd_count++;
    }
}

void uniqueHistory(char *command)
{
    // checking if last command is same as current command
    if (strcmp(history_array[cmd_count - 1], command) == 0)
    {
        return;
    }
    else
    {
        changeHistory(command);
    }
}

void saveHistory()
{
    // open history file
    // store home path to variable
    char *path = (char *)malloc(sizeof(char) * BUFFER_MAX);
    strcpy(path, home);
    strcat(path, "/history.txt");
    FILE *fp = fopen(path, "w+");
    if (fp == NULL)
    {
        perror("fopen");
        return;
    }
    // writing number of commands in history file
    fprintf(fp, "%d\n", cmd_count);
    // writing history commands in history file
    int i = 0;
    while (i < cmd_count)
    {
        fprintf(fp, "%s\n", history_array[i]);
        i++;
    }
    // close history file
    free(path);
    fclose(fp);
}

void displayHistory(char **tokens)
{
    // if arg_count is 1, display all history commands
    if (arg_count == 1)
    {
        // printing history commands if less than 10
        if (cmd_count <= 10)
        {
            for (int i = 0; i < cmd_count; i++)
            {
                printf("%s\n", history_array[i]);
            }
        }
        // else print last 10 commands
        else
        {
            for (int i = cmd_count - 10; i < cmd_count; i++)
            {
                printf("%s\n", history_array[i]);
            }
        }
    }
    // if arg_count is 2, display last n commands
    else if (arg_count == 2)
    {
        int n = atoi(tokens[0]);
        // printing history commands if less than n
        if (cmd_count <= n)
        {
            for (int i = 0; i < cmd_count; i++)
            {
                printf("%s\n", history_array[i]);
            }
        }
        // else print last n commands
        else
        {
            for (int i = cmd_count - n; i < cmd_count; i++)
            {
                printf("%s\n", history_array[i]);
            }
        }
    }
    else
    {
        printf("Invalid number of arguments\n");
    }
}