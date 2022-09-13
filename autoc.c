#include "headers.h"

// function to return auto complete the command
char *auto_complete(char *input)
{
    // get the current working directory
    char cwd[CWD_MAX];
    getcwd(cwd, CWD_MAX);
    int path_flag = 0;
    // get the input
    char *input_copy = malloc(sizeof(char) * BUFFER_MAX);
    strcpy(input_copy, input);
    // get the last token using strtok_r
    char *save_pointer;
    char *token = strtok_r(input_copy, " ", &save_pointer);
    char *last_token = malloc(sizeof(char) * BUFFER_MAX);
    while (token != NULL)
    {
        strcpy(last_token, token);
        token = strtok_r(NULL, " ", &save_pointer);
    }

    // allocate memory for directory path
    char *dir_path = malloc(sizeof(char) * BUFFER_MAX);
    // if / is present in the last token, directory path is till the last / else set it to current working directory
    if (strchr(last_token, '/') != NULL)
    {
        // take the initial part of the last token till the last /
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
            // remove the last token part from the directory path
            dir_path[strlen(dir_path) - strlen(last_token_part)] = '\0';
            // update last token
            strcpy(last_token, last_token_part);
        }
        // if the last token part is empty, set the directory path to the last token
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
    // printf("last token: %s\n", last_token);
    DIR *dir = opendir(dir_path);
    if (dir == NULL)
    {
        printf("Directory does not exist");
        return NULL;
    }
    // store all paths beginning with last token in a 2d array
    struct dirent *entry;
    char **paths = malloc(sizeof(char *) * BUFFER_MAX);
    int i = 0;
    while ((entry = readdir(dir)) != NULL)
    {
        // printf("entry: %s\n", entry->d_name);
        // //print last token
        // printf("last token: %s\n", last_token);
        // // //print length of last token
        // printf("length of last token: %d\n", strlen(last_token));
        if (strncmp(entry->d_name, last_token, strlen(last_token)) == 0)
        {
            // printf("in");
            // if its a file then add space after it else if its a folder add / after it
            if (entry->d_type == DT_REG)
            {
                // printf("in");
                paths[i] = malloc(sizeof(char) * BUFFER_MAX);
                strcpy(paths[i], entry->d_name);
                strcat(paths[i], " ");
                // printf("paths[i]: %s\n", paths[i]);
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
        // print prefix and longest common prefix
        //  printf("prefix: %s\n", prefix);
        //  printf("longest common prefix: %s\n", longest_common_prefix);
        //  //print last token
        //  printf("last token: %s\n", last_token);
        // global_long_prefix = longest_common_prefix;
        // global_prefix = last_token;

        // if(strcmp(global_long_prefix, global_prefix) == 0){
        //     paths2_count = i;
        //     paths2 = paths;
        //     return NULL;
        // }

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
        // printf(longest_common_prefix);
        return longest_common_prefix;

        // if (strcmp(longest_common_prefix, last_token) == 0)
        // {
        //     // store all paths in another 2d array
        //     // use global variable paths2
        //     paths2_count = i;
        //     paths2 = paths;
        //     global_long_prefix = longest_common_prefix;
        //     global_prefix = last_token;
        //     // print paths2
        //     //  for (int j = 0; j < paths2_count; j++)
        //     //  {
        //     //      printf("paths2[%d]: %s\n", j, paths2[j]);
        //     //  }
        // }
        // else
        // {
        //     if (path_flag == 1)
        //     {
        //         char *temp = malloc(sizeof(char) * BUFFER_MAX);
        //         strcpy(temp, longest_common_prefix);
        //         strcpy(longest_common_prefix, dir_path);
        //         strcat(longest_common_prefix, temp);
        //         free(temp);
        //     }
        //     // printf(longest_common_prefix);
        //     return longest_common_prefix;
        // }

        // free all paths
        //  for (int j = 0; j < i; j++)
        //  {
        //      free(paths[j]);
        //  }
        //  free(paths);

        // if path flag = 1, join the directory path and the longest common prefix
        //  if (path_flag == 1)
        //  {
        //      char *temp = malloc(sizeof(char) * BUFFER_MAX);
        //      strcpy(temp, longest_common_prefix);
        //      strcpy(longest_common_prefix, dir_path);
        //      strcat(longest_common_prefix, temp);
        //      free(temp);
        //  }
        //  // printf(longest_common_prefix);
        //  return longest_common_prefix;
    }
    closedir(dir);
}

//     free(input_copy);
//     // free(dir_path);
//     free(last_token);
//     closedir(dir);
//     return dir_path;
// }