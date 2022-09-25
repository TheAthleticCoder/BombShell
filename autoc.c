#include "headers.h"

//FUNCTION TO IMPLEMENT AUTOCOMPLETION 
char *auto_complete(char *input)
{
    char cwd[CWD_MAX];
    getcwd(cwd, CWD_MAX);
    int path_flag = 0;
    // GETTING THE INPUT
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

    // allocating memory for directory path
    char *dir_path = malloc(sizeof(char) * BUFFER_MAX);
    // if / is present in the last token, directory path is till the last / else set it to current working directory
    if (strchr(last_token, '/') != NULL)
    {
        // taking the initial part of the last token till the last /
        char *last_token_copy = malloc(sizeof(char) * BUFFER_MAX);
        strcpy(last_token_copy, last_token);
        char *save_pointer;
        char *token = strtok_r(last_token_copy, "/", &save_pointer);
        char *last_token_part = malloc(sizeof(char) * BUFFER_MAX);
        while (token != NULL)
        {
            strcpy(last_token_part, token);
            token = strtok_r(NULL, "/", &save_pointer);
        }
        // if the last token part is not empty, set the directory path to the initial part of the last token
        if (strcmp(last_token_part, "") != 0)
        {

            strcpy(dir_path, last_token);
            // removing the last token part from the directory path
            dir_path[strlen(dir_path) - strlen(last_token_part)] = '\0';
            // updating last token
            strcpy(last_token, last_token_part);
        }
        // if the last token part is empty, setting the directory path to the last token
        else
        {
            strcpy(dir_path, last_token);
            // update last token
            strcpy(last_token, "");
        }
        path_flag = 1;
    }
    else
    {
        strcpy(dir_path, cwd);
    }
    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        printf("Directory does not exist");
        return NULL;
    }
    struct dirent *entry;
    char **paths = malloc(sizeof(char *) * BUFFER_MAX);
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        if (strncmp(entry->d_name, last_token, strlen(last_token)) == 0)
        {
            // if its a file then adding space after it else if its a folder adding / after it
            if (entry->d_type == DT_REG)
            {
                paths[i] = malloc(sizeof(char) * BUFFER_MAX);
                strcpy(paths[i], entry->d_name);
                strcat(paths[i], " ");
                i++;
            }
            else if (entry->d_type == DT_DIR)
            {
                paths[i] = malloc(sizeof(char) * BUFFER_MAX);
                strcpy(paths[i], entry->d_name);
                strcat(paths[i], "/");
                i++;
            }
        }
    }
    // if there are no paths beginning with last token, return NULL
    if (i == 0)
    {
        // printf("in1");
        return NULL;
    }
    else if (i == 1)
    {
        // if path flag = 1, join the directory path and the paths[0] else return paths[0]
        if (path_flag == 1)
        {
            char *path = malloc(sizeof(char) * BUFFER_MAX);
            strcpy(path, dir_path);
            strcat(path, paths[0]);
            return path;
        }
        else
        {
            return paths[0];
        }
    }
    else
    {
        // find the longest common prefix of all paths
        char *longest_common_prefix = malloc(sizeof(char) * BUFFER_MAX);
        strcpy(longest_common_prefix, paths[0]);
        for (int j = 1; j < i; j++)
        {
            int k = 0;
            while (longest_common_prefix[k] != '\0' && paths[j][k] != '\0' && longest_common_prefix[k] == paths[j][k])
            {
                k++;
            }
            longest_common_prefix[k] = '\0';
        }

        for (int j = 0; j < i; j++)
        {
            free(paths[j]);
        }
        free(paths);

        if (path_flag == 1)
        {
            char *temp = malloc(sizeof(char) * BUFFER_MAX);
            strcpy(temp, longest_common_prefix);
            strcpy(longest_common_prefix, dir_path);
            strcat(longest_common_prefix, temp);
            free(temp);
        }
        return longest_common_prefix;
    }
    closedir(dir);
}
