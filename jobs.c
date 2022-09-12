#include "headers.h"

struct jobs{
    int num;
    pid_t pid;
    char *command;
    char **tokens;
    int status;
    int ab_norm;
    struct jobs *next;
};

//compare function for qsort for sorting jobs
int job_compare(const void *a, const void *b){
    struct jobs *job1 = (struct jobs *)a;
    struct jobs *job2 = (struct jobs *)b;
    return job1->num - job2->num;
}

void printJobs(int flag_r, int flag_s)
{
    //store running jobs in array
    struct jobs *running_jobs = (struct jobs *)malloc(sizeof(struct jobs) * 100);
    //store stopped jobs in array
    struct jobs *stopped_jobs = (struct jobs *)malloc(sizeof(struct jobs) * 100);
    //count of running jobs
    int running_count = 0;
    //count of stopped jobs
    int stopped_count = 0;
    //if both flags are 0, print all jobs
    if (flag_r == 0 && flag_s == 0)
    {
        flag_r = 1;
        flag_s = 1;
    }
    int i = 0;
    struct process *temp = processes;
    while (temp != NULL)
    {
        if(temp->status == 1){
            running_jobs[running_count].num = temp->num;
            running_jobs[running_count].pid = temp->pid;
            running_jobs[running_count].command = temp->command;
            running_jobs[running_count].tokens = temp->tokens;
            running_jobs[running_count].status = temp->status;
            running_jobs[running_count].ab_norm = temp->ab_norm;
            running_jobs[running_count].next = NULL;
            running_count++;
        }
        else{
            stopped_jobs[stopped_count].num = temp->num;
            stopped_jobs[stopped_count].pid = temp->pid;
            stopped_jobs[stopped_count].command = temp->command;
            stopped_jobs[stopped_count].tokens = temp->tokens;
            stopped_jobs[stopped_count].status = temp->status;
            stopped_jobs[stopped_count].ab_norm = temp->ab_norm;
            stopped_jobs[stopped_count].next = NULL;
            stopped_count++;
        }
        temp = temp->next;
    }
    //if flag_r is set, sort running jobs
    if(flag_r == 1){
        qsort(running_jobs, running_count, sizeof(struct jobs), job_compare);
        //print running jobs in format process_count Running command tokens pid
        for(int i=0;i<running_count;i++){
            printf("[%d] Running ", running_jobs[i].num);
            //prin the command
            printf("%s ", running_jobs[i].command);
            int j = 0;
            while(running_jobs[i].tokens[j] != NULL){
                printf("%s ", running_jobs[i].tokens[j]);
                j++;
            }
            printf("[%d]\n", running_jobs[i].pid);
        }
    }
    //if flag_s is set, sort stopped jobs
    if(flag_s == 1){
        qsort(stopped_jobs, stopped_count, sizeof(struct jobs), job_compare);
        //print stopped jobs in format process_count Stopped command tokens pid
        for(int i=0;i<stopped_count;i++){
            printf("[%d] Stopped ", stopped_jobs[i].num);
            //prin the command
            printf("%s ", stopped_jobs[i].command);
            int j = 0;
            while(stopped_jobs[i].tokens[j] != NULL){
                printf("%s ", stopped_jobs[i].tokens[j]);
                j++;
            }
            printf("[%d]\n", stopped_jobs[i].pid);
        }
    }

    free(running_jobs);
    free(stopped_jobs);
}

void jobs(char *command, char **tokens)
{
    int flag_r = 0;
    int flag_s = 0;
    int i = 0;
    while(i < arg_count-1)
    {   
        //print tokens[i] for debugging
        if(strcmp(tokens[i], "-r") == 0)
        {
            flag_r = 1;
        }
        else if(strcmp(tokens[i], "-s") == 0)
        {
            flag_s = 1;
        }
        else if(strcmp(tokens[i], "-rs") == 0 || strcmp(tokens[i], "-sr") == 0)
        {
            flag_r = 1;
            flag_s = 1;
        }
        i++;
    }
    printJobs(flag_r, flag_s);
}

