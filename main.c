#include "headers.h"

char *home;
char *prev_dir;
// int paths2_count;
// char **paths2;
// char *global_long_prefix;
// char *global_prefix;
int main()
{
    // delimiter
    struct termios orig_termios;
    char *delimiter = ";\n";
    // set home as current working directory
    home = malloc(sizeof(char) * CWD_MAX);
    prev_dir = malloc(sizeof(char) * CWD_MAX);
    getcwd(home, CWD_MAX);
    strcpy(prev_dir, home);
    // paths2_count = 0;
    // load history
    historyLoader();

    //implement ctrl + z
    signal(SIGTSTP, ctrl_z_handler);
    //implement ctrl + c
    signal(SIGINT, ctrl_c_handler);
    while (1)
    {
        // Prompt to display the kernel like display
        prompt();
        // print process count
        //  printf("%d\n", process_count);
        char *input = malloc(sizeof(char) * BUFFER_MAX);
        // global_long_prefix = malloc(sizeof(char) * BUFFER_MAX);
        // global_prefix = malloc(sizeof(char) * BUFFER_MAX);
        // paths2 = malloc(sizeof(char *) * BUFFER_MAX);
        // memset(global_long_prefix, 0, BUFFER_MAX);
        // memset(global_prefix, 0, BUFFER_MAX);
        char *c;
        setbuf(stdout, NULL);
        enableRawMode();
        memset(input, '\0', 100);
        int pt = 0;
        while (read(STDIN_FILENO, &c, 1) == 1)
        {
            if (iscntrl(c))
            {
                if (c == 10)
                {
                    break;
                }
                else if (c == 27)
                {
                    char buf[3];
                    buf[2] = 0;
                    if (read(STDIN_FILENO, buf, 2) == 2)
                    { // length of escape code
                        printf("\rarrow key: %s", buf);
                    }
                }
                else if (c == 127)
                { // backspace
                    if (pt > 0)
                    {
                        if (input[pt - 1] == 9)
                        {
                            for (int i = 0; i < 7; i++)
                            {
                                printf("\b");
                            }
                        }
                        input[--pt] = '\0';
                        printf("\b \b");
                    }
                }
                else if (c == 9)
                { // TAB character
                    // input[pt++] = c;
                    // get argument after last space
                    char *input_copy = malloc(sizeof(char) * BUFFER_MAX);
                    strcpy(input_copy, input);
                    char *save_pointer;
                    char *token = strtok_r(input_copy, " ", &save_pointer);
                    char *last_token = malloc(sizeof(char) * BUFFER_MAX);
                    while (token != NULL)
                    {
                        strcpy(last_token, token);
                        token = strtok_r(NULL, " ", &save_pointer);
                    }

                    char *auto_complete_string = auto_complete(last_token);

                    if (auto_complete_string != NULL)
                    {
                        printf("%s", auto_complete_string + strlen(last_token));
                        // update input
                        strcat(input, auto_complete_string + strlen(last_token));
                        pt += strlen(auto_complete_string) - strlen(last_token);
                    }
                    else
                    {
                        printf("\a");
                    }
                    free(input_copy);
                    free(last_token);
                    free(auto_complete_string);
                }
                else if (c == 4)
                {
                    //if there is no input, exit
                    if (pt == 0)
                    {
                        printf("\r");
                        exit(0);
                    }
                    else
                    {
                        printf("\a");
                    }
                }
                else
                {
                    printf("%d\n", c);
                }
            }
            else
            {
                input[pt++] = c;
                printf("%c", c);
            }
        }
        disableRawMode();
        printf("\nInput Read: [%s]\n", input);
        // fgets(input, BUFFER_MAX, stdin);
        // printf("\nInput Read: [%s]\n", input);
        if (input != NULL)
        {
            char *save_pointer;
            char *args = strtok_r(remove_extra_spaces(input), delimiter, &save_pointer);
            while (args != NULL)
            {
                // update history counter
                uniqueHistory(args);
                saveHistory();
                pipe_tokenize(args);
                // input_tokenize(args);
                args = strtok_r(NULL, delimiter, &save_pointer);
            }
        }
        else
        {
            // if there is no input, print error
            perror("fgets");
            return -1;
        }
        check_background_process();
        free(input);
    }
    free(home);
    free(prev_dir);
    return 0;
}
