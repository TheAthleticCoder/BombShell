#include "headers.h"

// calling extern struct ptorcess from headers.h
// extern struct process *processes;
struct process *processes;
int process_count = 0;
//store current foreground process pid
int fg_pid = 0;

// add process to linked list
void add_process(pid_t pid, char *command, char **tokens)
{
    // create a new process
    // struct process *new_process = malloc(sizeof(struct process));
    struct process *new_process = calloc(1, sizeof(struct process));
    // set the pid
    new_process->num = process_count + 1;
    new_process->pid = pid;
    // set the command
    new_process->command = malloc(sizeof(char) * 100);
    strcpy(new_process->command, command);
    // set the tokens
    new_process->tokens = malloc(sizeof(char *) * 100);
    int i = 1;
    while (tokens[i] != NULL)
    {
        new_process->tokens[i] = malloc(sizeof(char) * 100);
        strcpy(new_process->tokens[i], tokens[i]);
        i++;
    }
    new_process->status = 1;
    new_process->ab_norm = NULL;
    // setting the next to NULL
    new_process->next = NULL;
    // if processes is NULL, set processes to new_process else add to end of linked list
    if (processes == NULL)
    {
        processes = new_process;
    }
    else
    {
        struct process *temp = processes;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_process;
    }
    process_count++;
}

// removing process from linked list
void remove_process(pid_t pid)
{
    struct process *temp = processes;
    while (temp != NULL)
    {
        if (temp->pid == pid)
        {
            temp->status = 0;
            break;
        }
        temp = temp->next;
    }
    // updating processes
    processes = temp;
    free(temp);
}

void check_background_process()
{
    struct process *temp = processes;
    while (temp != NULL)
    {
        if (temp->status == 1)
        {
            /// printing if process terminated normally or abnormally
            if (waitpid(temp->pid, &temp->ab_norm, WNOHANG) == temp->pid)
            {
                if (temp->ab_norm == 0)
                {
                    printf("[%d] %d exited normally\n", temp->num, temp->pid);
                }
                else
                {
                    printf("[%d] %d exited abnormally\n", temp->num, temp->pid);
                }
                temp->status = 0;
            }
        }
        temp = temp->next;
    }
    free(temp);
    // print pids and status
    temp = processes;
}

void run_fore_back(char **command, char **tokens)
{
    int i = 0;
    int background = 0;
    while (tokens[i] != NULL)
    {
        if (strcmp(tokens[i], "&") == 0)
        {
            background = 1;
            tokens[i] = NULL;
            break;
        }
        i++;
    }
    // if background == 1, run background process
    if (background == 1)
    {
        int status;
        pid_t child = fork();
        char **shift_tokens = malloc(sizeof(char *) * TOK_MAX);
        shift_tokens[0] = malloc(sizeof(char) * TOK_MAX);
        strcpy(shift_tokens[0], command);
        int i = 1;
        while (tokens[i - 1] != NULL)
        {
            shift_tokens[i] = malloc(sizeof(char) * TOK_MAX);
            strcpy(shift_tokens[i], tokens[i - 1]);
            i++;
        }
        shift_tokens[i] = NULL;
        if (child == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (child == 0)
        {
            execvp(shift_tokens[0], shift_tokens);
            perror("execvp");
            exit(1);
        }
        else
        {
            add_process(child, shift_tokens[0], shift_tokens);
            printf("%s [%d]", command, child);
            printf("\n");
        }
        free(shift_tokens);
    }
    else
    {
        int status;
        pid_t child = fork();
        time_t start_time = time(NULL);
        double time_elapsed = 0;
        char **shift_tokens = malloc(sizeof(char *) * TOK_MAX);
        shift_tokens[0] = malloc(sizeof(char) * TOK_MAX);
        strcpy(shift_tokens[0], command);
        int i = 1;
        tokens[arg_count - 1] = NULL;
        while (tokens[i - 1] != NULL)
        {
            shift_tokens[i] = malloc(sizeof(char) * TOK_MAX);
            strcpy(shift_tokens[i], tokens[i - 1]);
            i++;
        }
        shift_tokens[i] = NULL;
        fg_pid = process_count + 1;
        if (child == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (child == 0)
        {
            // execute the command
            execvp(shift_tokens[0], shift_tokens);
            perror("execvp");
            exit(1);
        }
        else
        {
            // wait for the child to finish
            // add the process to the linked list
            add_process(child, shift_tokens[0], shift_tokens);
            waitpid(child, &status, 0);
            // if process stopped, printing time taken
            if (WIFEXITED(status) != 0)
            {
                time_elapsed = difftime(time(NULL), start_time);
                // print process finished in time elapsed
                printf("%s finished in %.3f seconds\n", command, time_elapsed);
                remove_process(child);
            }
        }
        free(shift_tokens);
    }
}
