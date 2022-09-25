#include "headers.h"

void sig(char *command, char **tokens){
    int job_num = atoi(tokens[0]);
    int sig_num = atoi(tokens[1]);
    struct process *temp = processes;
    while (temp != NULL)
    {
        if (temp->num == job_num)
        {   
            int sigg = kill(temp->pid, sig_num);
            if (sigg == -1)
            {
                perror("kill sig:");
            }
            break;
        }
        temp = temp->next;
    }
}