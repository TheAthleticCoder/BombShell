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
#include <stdbool.h>
#include <sys/stat.h>
#include <dirent.h>
#include <grp.h>
#include <time.h>
#include <termios.h>
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
// call input_tokenizer
#define CMD_MAX 512
#define TOK_MAX 512

extern int arg_count;
// declare global variable home
extern char *home;
extern char *prev_dir;
extern char *global_long_prefix;
extern char *global_prefix;
extern char **paths2;
extern int paths2_count;

char printer(char *input);
char **input_tokenizer(char *input);
void input_to_execute(char *command, char **tokens);

void echo(char **tokens);
void cd(char **tokens);
void ls(char **tokens);
extern int process_count;

struct process
{
    int num;
    pid_t pid;
    char *command;
    char **tokens;
    int status;
    int ab_norm;
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
void run_fore_back(char **command, char **tokens);
void remove_process(pid_t pid);
void add_process(pid_t pid, char *command, char **tokens);
void check_background_process();
void run_fore_back(char **command, char **tokens);

void discover(char **tokens);
void jobs(char *command, char **tokens);
void sig(char *command, char **tokens);
void foreground(char **tokens);
void background(char **tokens);

// keyboard based input
void die(const char *s);
void disableRawMode();
void enableRawMode();
char *auto_complete(char *input);

void ctrl_z_handler(int sig);
void redirect(char **tokens);
#endif
