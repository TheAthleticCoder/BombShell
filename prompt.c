#include "headers.h"

void prompt() {
    
    //declare hostname using pointers
    char *hostname = malloc(sizeof(char) * HOST_NAME_MAX);
    char *username = malloc(sizeof(char) * HOST_NAME_MAX);
    char *cwd = malloc(sizeof(char) * CWD_MAX);
    char *path = malloc(sizeof(char) * BUFFER_MAX);

    if(gethostname(hostname, HOSTNAME_MAX) == -1) {
        perror("gethostname");
        exit(1);
    }
    if(getlogin_r(username, USERNAME_MAX) == -1) {
        perror("getlogin_r");
        exit(1);
    }
    if(getcwd(cwd, CWD_MAX) == NULL) {
        perror("getcwd");
        exit(1);
    }
    
    //checking if absolute path or relative path should be printed
    if(strcmp(cwd, "/") == 0) {
        strcpy(path, "~/");
    } else {
        strcpy(path, "~");
    }

    //if cwd is home, print ~
    if(strcmp(cwd, home) == 0) {
        strcpy(path, "~");
    }
    else{
        strcpy(path, "~");
        strcat(path, cwd + strlen(home));
    }
    // print prompt
    printf("<%s@%s:%s> ", username, hostname, path);

    //printing prompt
    // printf("<%s@%s:%s%s> ", username, hostname, path, cwd);
    //print current working directory
    // printf("%s\n", cwd);

    // else {
    //     if(cwd[0] == '/') {
    //     printf("%s@%s:~%s$ ", username, hostname, cwd);
    // }
    // else {
    //     printf("%s@%s:~%s$ ", username, hostname, cwd);
    // }
    // }
    free(hostname);
    free(username);
    free(cwd);
    free(path);
}


