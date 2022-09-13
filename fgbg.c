#include "headers.h"

void foreground(char **tokens)
{
    int job_num = atoi(tokens[0]);
    struct process *temp = processes;
    //bring stopped or running process to foreground and resume it
    while (temp != NULL)
    {
        if (temp->num == job_num)
        {
            int status;
            int fg = kill(temp->pid, SIGCONT);
            if (fg == -1)
            {
                perror("kill fg:");
            }
            int wait = waitpid(temp->pid, &status, WUNTRACED);
            if (wait == -1)
            {
                perror("waitpid fg:");
            }
            if (WIFSTOPPED(status))
            {
                temp->status = 0;
                temp->ab_norm = "Stopped";
            }
            else if (WIFEXITED(status))
            {
                temp->status = 0;
                temp->ab_norm = "Exited";
            }
            else if (WIFSIGNALED(status))
            {
                temp->status = 0;
                temp->ab_norm = "Killed";
            }
            break;
        }
        temp = temp->next;
    }
}

void background(char **tokens)
{
    int job_num = atoi(tokens[0]);
    struct process *temp = processes;
    //change stopped background process to running in background
    while (temp != NULL)
    {
        if (temp->num == job_num)
        {
            int status;
            //print pid and status
            // printf("[%d] %d %s\n", temp->num, temp->pid, temp->ab_norm);
            int bg = kill(temp->pid, SIGCONT);
            if (bg == -1)
            {
                perror("kill bg:");
            }
            temp->status = 1;
            break;
        }
        temp = temp->next;
    }
}