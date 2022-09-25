#include "headers.h"

void ctrl_z_handler(int sig)
{
    // push any currently running foreground job into the background
    struct process *temp = processes;
    if (fg_pid != 0)
    {
        while (temp != NULL)
        {
            if (temp->num == fg_pid)
            {
                // print process number and pid
                if (temp->status == 1)
                {
                    temp->status = 0;
                    temp->ab_norm = "Stopped";
                    //kill process
                    int kill_fg = kill(temp->pid, SIGTSTP);
                    if (kill_fg == -1)
                    {
                        perror("kill fg:");
                    }
                    printf("\r");
                    printf("\b\b  \n");
                    break;
                }
            }
            temp = temp->next;
        }
    }
    free(temp);
    fflush(stdout);
}

void ctrl_c_handler(int sig)
{
    // pushing any currently running foreground job into the background
    struct process *temp = processes;
    while (temp != NULL)
    {
        // check if its a foreground process
        if (temp->num == process_count)
        {
            // check if status is 1
            if (temp->status == 1)
            {
                temp->status = 0;
                kill(temp->pid, SIGINT);
                printf("\r");
                printf("\b\b  \n");
            }
        }
        temp = temp->next;
    }
    free(temp);
    fflush(stdout);
}
