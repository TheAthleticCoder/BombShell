#include "headers.h"

void sig(char *command, char **tokens){
    //process with job number 2 with signal 9
    int job_num = atoi(tokens[0]);
    int sig_num = atoi(tokens[1]);
    // printf("job_num: %d, sig_num: %d\n", job_num, sig_num);
    struct process *temp = processes;
    while (temp != NULL)
    {
        if (temp->num == job_num)
        {   
            // printf("exists");
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