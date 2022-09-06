#include "headers.h"

//call extern struct ptorcess from headers.h
extern struct process *processes;


// void add_process(pid_t pid, char *command, char **tokens){
//     //create a new process
//     struct process *new_process = malloc(sizeof(struct process));
//     //set the pid
//     new_process->pid = pid;
//     //set the command
//     new_process->command = malloc(sizeof(char) * 100);
//     strcpy(new_process->command, command);
//     //set the tokens
//     new_process->tokens = malloc(sizeof(char*) * 100);
//     int i = 0;
//     while(tokens[i] != NULL){
//         new_process->tokens[i] = malloc(sizeof(char) * 100);
//         strcpy(new_process->tokens[i], tokens[i]);
//         i++;
//     }
//     //set the next to NULL
//     new_process->next = NULL;
//     //if processes is NULL, set processes to new_process
//     if(processes == NULL){
//         processes = new_process;
//     }
//     //else, add new_process to the end of the linked list
//     else{
//         struct process *temp = processes;
//         while(temp->next != NULL){
//             temp = temp->next;
//         }
//         temp->next = new_process;
//     }
// }

void background(char *command, char **tokens){
    //forking a child process
    pid_t pid = fork();
    if(pid == -1) {
        perror("fork");
        return -1;
    }
    else if(pid == 0) {
        //child process
        //execute the command
        execvp(command, tokens);
        //if execvp fails, print error
        perror("execvp");
        exit(1);
    }
    else {
        //parent process
        //add the process to the linked list
        add_process(pid, command, tokens);
        //wait for the child process to finish
        waitpid(pid, NULL, 0);
    }
}
