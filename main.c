#include "headers.h"

char *home;
char *prev_dir;
int main()
{
    //print prompt
    char *delimiter = ";\n";
    //set home as current working directory
    // char *home;
    // char *temp = malloc(sizeof(char) * CWD_MAX);
    //copy temp to home
    home = malloc(sizeof(char) * CWD_MAX);
    prev_dir = malloc(sizeof(char) * CWD_MAX);
    getcwd(home, CWD_MAX);
    strcpy(prev_dir, home);
    //load history
    historyLoader();
    while (1)
    {
        //Prompt to display the kernel like display
        prompt();
        //declare user input using pointers
        char *input = malloc(sizeof(char) * BUFFER_MAX);
        //use readline to get user input
        // input = readline(input);
        // printf("%s\n", input);
        fgets(input, BUFFER_MAX, stdin);
        if (input != NULL)
        {
            char *save_pointer;
            char *args = strtok_r(remove_extra_spaces(input), delimiter, &save_pointer);
            while(args != NULL) {
                //update history counter
                uniqueHistory(args);
                saveHistory();
                input_tokenize(args);
                args = strtok_r(NULL, delimiter, &save_pointer);
            }
        }
        else{
            //if there is no input, print error
            perror("fgets");
            return -1; 
        }
        free(input);
    }
    free(home);
    free(prev_dir);
    return 0;
}
