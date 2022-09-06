#include "headers.h"

//FUNCTION TO TAKE IN COMMAND AND TOKEN AND EXECUTE
void input_to_execute(char *command, char **tokens){
    //strcmp to check if command is cd
    if(strcmp(command, "cd") == 0) {
        // char *home;
        //if there are more than 2 arguments, print error
        if(arg_count-1 > 1) {
            printf("%d\n", rand());
            perror("Too many arguments");
            return -1;
        }
        cd(tokens);
    }
    else if (strcmp(command, "pwd") == 0) {
        //if there are arguments, print error
        if(arg_count-1 > 0) {
            perror("Too many arguments");
            return -1;
        }
        else {
            //print current working directory
            char cwd[CWD_MAX];
            if (getcwd(cwd, sizeof(cwd)) != NULL) {
                printf("%s\n", cwd);
            }
        }

    }
    else if (strcmp(command, "echo") == 0) {
        echo(tokens);
    }
    else if (strcmp(command, "ls") == 0){
        // print random number
        ls(tokens);
        // ls(tokens);
    }
    else if(strcmp(command, "pinfo") == 0){
        pinfo(tokens);
        //print random number
        // printf("%d\n", rand());
    }
    else if(strcmp(command, "discover") == 0){
        //print random number
        discover(tokens);
    }
    else if(strcmp(command, "history") == 0){
        //print random number
        displayHistory(tokens);
    }
    else if(strcmp(command, "exit") == 0){
        //exit the shell
        exit(0);
    }
    // else{
    //     //check if token[0] is & or not
    //     if(strcmp(tokens[0], "&") == 0){
    //         //pass command and tokens to background
    //         background(command, tokens);
    //     }
    //     else
    //     {
    //         printf("fg");
    //     }
    // }
}
