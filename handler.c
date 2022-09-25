#include "headers.h"

void ctrl_z_handler(int sig)
{
    // push any currently running foreground job into the background
    struct process *temp = processes;
    // take the latest foreground process and convert it to background
    // print process count
    // printf("process count: %d\n", process_count);
    // print processes number and pid
    if (fg_pid != 0)
    {
        while (temp != NULL)
        {
            if (temp->num == fg_pid)
            {
                // print process number and pid
                if (temp->status == 1)
                {
                    // printf("[%d] %d\n", temp->num, temp->pid);
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


    // if (fg_pid != 0)
    // {
    //     while (temp != NULL)
    //     {
    //         // check if num is equal to process_count
    //         if (temp->num == fg_pid)
    //         {
    //             // check if status is 1
    //             if (temp->status == 1)
    //             {
    //                 // convert the process to a background process and stop the process
    //                 //  kill(temp->pid, SIGSTOP);

    //                 temp->status = 0;
    //                 kill(temp->pid, SIGTSTP);
    //                 printf("\r");
    //                 printf("\b\b  \n");
    //                 // printf("\r");
    //             }
    //             fg_pid = 0;
    //         }
    //         temp = temp->next;
    //     }
    // }
    // free(temp);
    // // prompt();
    // fflush(stdout);
// }

void ctrl_c_handler(int sig)
{
    // push any currently running foreground job into the background
    struct process *temp = processes;
    // take the latest foreground process and convert it to background
    // print process count
    // printf("process count: %d\n", process_count);
    // print processes number and pid
    while (temp != NULL)
    {
        // check if its a foreground process
        if (temp->num == process_count)
        {
            // check if status is 1
            if (temp->status == 1)
            {
                // convert the process to a background process and stop the process
                //  kill(temp->pid, SIGSTOP);

                temp->status = 0;
                kill(temp->pid, SIGINT);
                printf("\r");
                printf("\b\b  \n");
                // printf("\r");
            }
        }
        temp = temp->next;
    }
    free(temp);
    // prompt();
    fflush(stdout);
}
