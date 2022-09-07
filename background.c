#include "headers.h"

// calling extern struct ptorcess from headers.h
// extern struct process *processes;
struct process *processes;
int process_count = 0;

// add process to linked list
void add_process(pid_t pid, char *command, char **tokens)
{
    // create a new process
    struct process *new_process = malloc(sizeof(struct process));
    // set the pid
    new_process->pid = pid;
    // set the command
    new_process->command = malloc(sizeof(char) * 100);
    strcpy(new_process->command, command);
    // set the tokens
    new_process->tokens = malloc(sizeof(char *) * 100);
    int i = 0;
    while (tokens[i] != NULL)
    {
        new_process->tokens[i] = malloc(sizeof(char) * 100);
        strcpy(new_process->tokens[i], tokens[i]);
        i++;
    }
    // set the next to NULL
    new_process->next = NULL;
    // if processes is NULL, set processes to new_process
    if (processes == NULL)
    {
        processes = new_process;
    }
    // else, add new_process to the end of the linked list
    else
    {
        struct process *temp = processes;
        while (temp->next != NULL)
        {
            temp = temp->next;
        }
        temp->next = new_process;
    }
}

// remove process from linked list
void remove_process(pid_t pid)
{
    // if processes is NULL, return
    if (processes == NULL)
    {
        return;
    }
    // if the pid is the first pid, set processes to the next process
    if (processes->pid == pid)
    {
        processes = processes->next;
        return;
    }
    // else, find the process with the pid and remove it
    struct process *temp = processes;
    while (temp->next != NULL)
    {
        if (temp->next->pid == pid)
        {
            temp->next = temp->next->next;
            return;
        }
        temp = temp->next;
    }
    // free the process
    free(temp);
}

void check_background_process()
{
    // iterate through all the processes
    int i = 0;
    while (i < process_count)
    {
        // if the process is killed or exited, remove it from the list
        if (waitpid(processes[i].pid, NULL, WNOHANG) == processes[i].pid)
        {
            // print if process exited normally or abnormally
            if (WIFEXITED(processes[i].status))
            {
                printf("%s with pid = %d exited normally\n", processes[i].command, processes[i].pid);
            }
            else
            {
                printf("%s with pid = %d exited abnormally\n", processes[i].command, processes[i].pid);
            }
            remove_process(processes[i].pid);
            process_count--;
            i++;
        }
        else
        {
            i++;
        }
    }
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
        if (child == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (child == 0)
        {
            // execute the command
            char **shift_tokens = malloc(sizeof(char *) * TOK_MAX);
            // store command in shift_tokens[0]
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
            // set shift_tokens[i] to NULL
            shift_tokens[i + 1] = NULL;

            execvp(shift_tokens[0], shift_tokens);
            perror("execvp");
            exit(1);
            free(shift_tokens);
        }
        else
        {
            add_process(child, command, tokens);
            process_count++;
            printf("%s %d\n", command, child);
        }
    }
    // else, run foreground process
    else
    {
        int status;
        pid_t child = fork();
        time_t start_time = time(NULL);
        double time_elapsed = 0;
        if (child == -1)
        {
            perror("fork");
            exit(1);
        }
        else if (child == 0)
        {
            // execute the command
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
            // set shift_tokens[i+1] to NULL
            shift_tokens[i + 1] = NULL;

            execvp(shift_tokens[0], shift_tokens);
            perror("execvp");
            exit(1);
            free(shift_tokens);
        }
        else
        {
            // wait for the child to finish
            // add the process to the linked list
            add_process(child, command, tokens);
            waitpid(child, &status, 0);
            // if process stopped, print time taken
            if (WIFEXITED(status) != 0)
            {   
                time_elapsed = difftime(time(NULL), start_time);
                //print process finished in time elapsed
                printf("%s finished in %.3f seconds\n", command, time_elapsed);
                remove_process(child);
            }
        }
    }
}
