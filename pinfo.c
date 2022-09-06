#include "headers.h"

void get_info(pid_t pid){
    //print the pid
    char file_name[1024];
    sprintf(file_name, "/proc/%d/stat", pid);
    FILE *fp = fopen(file_name, "r");
    if(fp == NULL){
        perror("fopen");
        return;
    }
    else{
        //reading through the file
        //display process status
        char *line = NULL;
        size_t len = 0;
        ssize_t read;
        //stroe '+' or '-' based on foreground or background
        char *status;
        //store the process id
        pid_t console_pid = tcgetpgrp(STDOUT_FILENO);
        pid_t my_pid = getpgrp();
        if(console_pid == my_pid){
            status = "+";
        }
        else{
            status = "";
        }

        if((read = getline(&line, &len, fp)) != -1){
            // printf("%s", line);
            char *token = strtok(line, " ");
            int i = 0;
            while(token != NULL){
                if(i == 0){
                    printf("pid : %s\n", token);
                }
                else if(i == 2){
                    ///print process status with status
                    printf("process status : %s%s\n", token, status);
                }
                else if(i == 22){
                    printf("memory : %s {Virtual Memory}\n", token);
                }
                token = strtok(NULL, " ");
                i++;
            }
        }
        else{
            perror("getline");
            return;
        }
        //print executable path
        char *path = malloc(sizeof(char) * 1024);
        sprintf(path, "/proc/%d/exe", pid);
        char *buf = malloc(sizeof(char) * 1024);
        int bytes = readlink(path, buf, 1024);
        if(bytes == -1){
            perror("readlink");
            return;
        }
        else{
            //print executable path using printer
            printf("executable path : ");
            printer(buf);
        }
    }

}

void pinfo(char **tokens) {
    //if there are more than 2 arguments, print error
    if(arg_count-1 > 1) {
        perror("Too many arguments");
        return -1;
    }
    //if there are no arguments, print info about shell
    else if(arg_count-1 == 0) {
        //get pid of shell
        pid_t pid = getpid();
        //get info about shell
        get_info(pid);
    }
    //if there is 1 argument, print info about that process
    else if(arg_count-1 == 1) {
        //get pid of process
        pid_t pid = atoi(tokens[0]);
        //get info about process
        get_info(pid);
    }
}