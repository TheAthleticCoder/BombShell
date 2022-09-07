#include "headers.h"

char *home;
char *prev_dir;

int main()
{
    //delimiter
    char *delimiter = ";\n";
    //set home as current working directory
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
        char *input = malloc(sizeof(char) * BUFFER_MAX);
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
        check_background_process();
    }
    free(home);
    free(prev_dir);
    return 0;
}
