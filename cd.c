#include "headers.h"

//Function to check validity of changing directory
void change_direc(char *path){
    char *temp = malloc(sizeof(char) * CWD_MAX);
    getcwd(temp, CWD_MAX);
    long path_check = chdir(path);
    if(path_check == -1){
        perror("chdir");
        return;
    }
    else{
        strcpy(prev_dir, temp);
    }
    free(temp);
}

void cd(char **tokens){
    //if there are no arguments, go to home directory
    if(arg_count-1 == 0 || strcmp(tokens[0], "~") == 0) {
        // printf("%s\n", home);
        change_direc(home);
    }
    else if(strcmp(tokens[0], "-") == 0){
        change_direc(prev_dir);
    }
    else if(strcmp(tokens[0],"..") == 0){
        change_direc("..");
    }
    else{
        char *current = malloc(sizeof(char) * CWD_MAX);
        getcwd(current, CWD_MAX);
        change_direc(strcat(strcat(current, "/"), tokens[0]));
        free(current);
    }
    //print home
    // printf("%s\n", home);
    return 0;
}