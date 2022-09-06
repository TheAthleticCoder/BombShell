#ifndef __HEADERS_H
#define __HEADERS_H

#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <errno.h>
#include <limits.h>
#include <sys/types.h>
#include <dirent.h>
#include <pwd.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <signal.h>
#define ll long long int

#define HOSTNAME_MAX 512
#define USERNAME_MAX 512
#define CWD_MAX 512
#define BUFFER_MAX 512
#define MAX_HISTORY 20
void prompt();

char *remove_extra_spaces(char *str);
//call input_tokenizer
#define CMD_MAX 512
#define TOK_MAX 512

extern int arg_count;
//declare global variable home
extern char *home;
extern char *prev_dir;

char printer(char *input);
char **input_tokenizer(char *input);
void input_to_execute(char *command, char **tokens);

void echo(char **tokens);
void cd(char **tokens);
void ls(char **tokens);

struct process
{
    pid_t pid;
    char *command;
    char **tokens;
    int status;
    struct process *next;
};
extern struct process *processes;

void pinfo(char **tokens);
void historyWriter(char *input);
void historyLoader();
void changeHistory(char *command);
void uniqueHistory(char *command);
void saveHistory();
void displayHistory(char **tokens);

void discover(char **tokens);
#endif
