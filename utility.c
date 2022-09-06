#include "headers.h"
int arg_count = 0;


//a function which takes in the input string 
char printer(char *input) {
    //if input is equal to home, print ~
    if(strcmp(input, home) == 0) {
        printf("~");
        printf("\n");
    }
    //else print ~ and the rest of the string
    else {
        printf("~%s", input + strlen(home));
        printf("\n");
    }
    
}


//FUNCTION TO REMOVE EXTRA SPACES
char *remove_extra_spaces(char *str) {
    int i = 0, j = 0;
    while(str[i]) {
        while(str[i] == ' ' && str[i+1] == ' ') {
            i++;
        }
        str[j++] = str[i++];
    }
    str[j] = '\0';
    return str;
}

//FUNCTION TO TOKENIZE THE RECIEVED ARGUMENT BASED ON SPACES AND RETURN COMMAND+TOKENS
char **input_tokenize(char *input) {
    arg_count = 0;
    char *save_pointer;
    char *delimiter = " \t";
    char *args = strtok_r(remove_extra_spaces(input), delimiter, &save_pointer);
    //print args
    // char command[CMD_MAX];
    //declare command of size CMD_MAX
    char *command = malloc(sizeof(char) * CMD_MAX);
    //declare tokens of size TOKEN_MAX*TOKEN_MAX
    char **tokens = malloc(sizeof(char *) * TOK_MAX);
    // char tokens[TOK_MAX][TOK_MAX];
    //initialize tokens to NULL
    //print all arguments
    while(args != NULL) {
        //storing command from 1st argument
        if(arg_count == 0) {
            strcpy(command, args);
            //print command
            // printf("%s\n", command);
            args = strtok_r(NULL, delimiter, &save_pointer);
        }
        else { //storing other args as tokens using pointers
            tokens[arg_count-1] = args;
            // printf("%s\n", tokens[arg_count-1]);
            args = strtok_r(NULL, delimiter, &save_pointer);
        }
        arg_count++;
        // args = strtok_r(NULL, delimiter, &save_pointer);
    }
    // printf("1%s\n", command);
    // for(int i = 0; i < arg_count-1; i++) {
    //     printf("%s\n", tokens[i]);
    // }
    //if there is no command perror
    if(arg_count == 0) {
        perror("No command entered");
        return NULL;
    }
    else
    {
        //input to execute
        input_to_execute(command, tokens);
        //print tokens
    }
    free(args);
    free(command);
    free(tokens);
}    



