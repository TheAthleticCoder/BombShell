#include "headers.h"

// a function which takes in the input string
char discover_printer(char *input)
{
    // if input is equal to home, print ~
    if (strcmp(input, home) == 0)
    {
        printf(".");
        printf("\n");
    }
    // else print ~ and the rest of the string
    else
    {
        printf(".%s", input + strlen(home));
        printf("\n");
    }
}

void discover_direc(char *path, char *file_name, int flag_d, int flag_f, int flag_file)
{
    // declare an array to store full path
    char *full_path = malloc(sizeof(char) * BUFFER_MAX);
    // open directory
    DIR *dir = opendir(path);
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    // check if filename is given
    if (flag_file == 1)
    {
        // check if file is present in in path and its subdirectories
        // if file is present, print its path
        // if file is not present, print error
        if (flag_f == 0)
        {
            // check if file is present in path
            if (flag_d == 0)
            {
                // check if file is present in path
                strcpy(full_path, path);
                strcat(full_path, "/");
                strcat(full_path, file_name);
                if (access(full_path, F_OK) != -1)
                {
                    printf("%s\n", full_path);
                }
            }
            // check if file is present in subdirectories
            else
            {
                // check if file is present in subdirectories
                struct dirent *entry;
                while ((entry = readdir(dir)) != NULL)
                {
                    // check if entry is a directory
                    if (entry->d_type == DT_DIR)
                    {
                        // check if entry is . or ..
                        if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0)
                        {
                            continue;
                        }
                        // check if file is present in subdirectory
                        strcpy(full_path, path);
                        strcat(full_path, "/");
                        strcat(full_path, entry->d_name);
                        discover_direc(full_path, file_name, flag_d, flag_f, flag_file);
                    }
                }
            }
        }
    }
    else
    {
        struct dirent *direc;
        while ((direc = readdir(dir)) != NULL)
        {
            // if flag_d is set, print directories
            if (flag_d == 1 && flag_f == 0)
            {
                if (direc->d_type == DT_DIR)
                {
                    // if name is directory we are in or parent directory, print it as it is
                    if (strcmp(direc->d_name, ".") == 0)
                    {
                        continue;
                        // printf("%s\n", direc->d_name);
                    }
                    else if (strcmp(direc->d_name, "..") == 0)
                    {
                        continue;
                    }
                    else
                    {
                        strcpy(full_path, path);
                        strcat(full_path, "/");
                        strcat(full_path, direc->d_name);
                        printf("%s\n", full_path);
                        // discover_printer(full_path);
                        // recursively call discover_direc
                        discover_direc(full_path, file_name, flag_d, flag_f, flag_file);
                        // clear full_path
                        memset(full_path, 0, BUFFER_MAX);
                    }
                }
            }
            // if flag_f is set, print files
            if (flag_f == 1 && flag_d == 0)
            {
                if (direc->d_type == DT_REG)
                {
                    // if name is directory we are in or parent directory, print it as it is
                    if (strcmp(direc->d_name, ".") == 0)
                    {
                        continue;
                        // printf("%s\n", direc->d_name);
                    }
                    else if (strcmp(direc->d_name, "..") == 0)
                    {
                        continue;
                    }
                    else
                    {
                        strcpy(full_path, path);
                        strcat(full_path, "/");
                        strcat(full_path, direc->d_name);
                        printf("%s\n", full_path);
                        // discover_printer(full_path);
                        memset(full_path, 0, BUFFER_MAX);
                    }
                }
            }
            // if flag_d and flag_f are not set or both are set, print all
            if ((flag_d == 0 && flag_f == 0) | (flag_d == 1 && flag_f == 1))
            {
                // print full path
                if (strcmp(direc->d_name, ".") == 0)
                {
                    continue;
                    // printf("%s\n", direc->d_name);
                }
                else if (strcmp(direc->d_name, "..") == 0)
                {
                    continue;
                }
                else
                {
                    strcpy(full_path, path);
                    strcat(full_path, "/");
                    strcat(full_path, direc->d_name);
                    printf("%s\n", full_path);
                    // discover_printer(full_path);
                    // if its a directory, recursively call discover_direc
                    if (direc->d_type == DT_DIR)
                    {
                        discover_direc(full_path, file_name, flag_d, flag_f, flag_file);
                    }
                    else
                    {
                        continue;
                    }
                    // clear full_path
                    memset(full_path, 0, BUFFER_MAX);
                }
            }
        }
    }

    // struct dirent *direc;
    // while ((direc = readdir(dir)) != NULL)
    // {
    //     // if flag_d is set, print directories
    //     if (flag_d == 1)
    //     {
    //         if (direc->d_type == DT_DIR)
    //         {
    //             // if name is directory we are in or parent directory, print it as it is
    //             if (strcmp(direc->d_name, ".") == 0)
    //             {
    //                 continue;
    //                 // printf("%s\n", direc->d_name);
    //             }
    //             else if (strcmp(direc->d_name, "..") == 0)
    //             {
    //                 continue;
    //             }
    //             else
    //             {
    //                 strcpy(full_path, path);
    //                 strcat(full_path, "/");
    //                 strcat(full_path, direc->d_name);
    //                 printf("%s\n", full_path);
    //                 // discover_printer(full_path);
    //                 // recursively call discover_direc
    //                 discover_direc(full_path, file_name, flag_d, flag_f, flag_file);
    //                 // clear full_path
    //                 memset(full_path, 0, BUFFER_MAX);
    //             }
    //         }
    //     }
    //     // if flag_f is set, print files
    //     if (flag_f == 1)
    //     {
    //         if (direc->d_type == DT_REG)
    //         {
    //             // if name is directory we are in or parent directory, print it as it is
    //             if (strcmp(direc->d_name, ".") == 0)
    //             {
    //                 continue;
    //                 // printf("%s\n", direc->d_name);
    //             }
    //             else if (strcmp(direc->d_name, "..") == 0)
    //             {
    //                 continue;
    //             }
    //             else
    //             {
    //                 strcpy(full_path, path);
    //                 strcat(full_path, "/");
    //                 strcat(full_path, direc->d_name);
    //                 printf("%s\n", full_path);
    //                 // discover_printer(full_path);
    //                 memset(full_path, 0, BUFFER_MAX);
    //             }
    //         }
    //     }
    //     // if flag_d and flag_f are not set or both are set, print all
    //     if ((flag_d == 0 && flag_f == 0) | (flag_d == 1 && flag_f == 1))
    //     {
    //         // print full path
    //         if (strcmp(direc->d_name, ".") == 0)
    //         {
    //             continue;
    //             // printf("%s\n", direc->d_name);
    //         }
    //         else if (strcmp(direc->d_name, "..") == 0)
    //         {
    //             continue;
    //         }
    //         else
    //         {
    //             strcpy(full_path, path);
    //             strcat(full_path, "/");
    //             strcat(full_path, direc->d_name);
    //             printf("%s\n", full_path);
    //             // discover_printer(full_path);
    //             // if its a directory, recursively call discover_direc
    //             if (direc->d_type == DT_DIR)
    //             {
    //                 discover_direc(full_path, file_name, flag_d, flag_f, flag_file);
    //             }
    //             else
    //             {
    //                 continue;
    //             }
    //             // clear full_path
    //             memset(full_path, 0, BUFFER_MAX);
    //         }
    //     }
    // }
    free(full_path);
    closedir(dir);
}

void discover(char **tokens)
{
    int index = 0;
    int flag_d = 0;
    int flag_f = 0;
    int flag_file = 0;
    int path_flag = 0;
    // variable to store file name
    char *file_name = (char *)malloc(sizeof(char) * BUFFER_MAX);
    // variable to store path
    char *path = (char *)malloc(sizeof(char) * BUFFER_MAX);
    // check if there are arguments
    while (index < arg_count - 1)
    {
        // if token is -d, set flag_d to 1
        if (strcmp(tokens[index], "-d") == 0)
        {
            flag_d = 1;
            // printf("flag_d is set\n");
        }
        else if (strcmp(tokens[index], "-f") == 0)
        {
            flag_f = 1;
            // printf("flag_f is set\n");
        }
        // else if token is in quotes, store it in file_name
        else if (tokens[index][0] == '"')
        {
            strcpy(file_name, tokens[index]);
            // remove quotes from file_name
            int i = 0;
            while (file_name[i] != '\0')
            {
                file_name[i] = file_name[i + 1];
                i++;
            }
            file_name[i - 2] = '\0';
            flag_file = 1;
            // printf("file_name is %s", file_name);
        }
        else
        {
            // opendir
            // save it to path
            strcpy(path, tokens[index]);
            path_flag = 1;
            // printf("path is %s", path);
        }
        index++;
    }
    // if path_flag is not set, set path to current working directory
    if (path_flag == 0)
    {
        // print random numbe
        strcpy(path, ".");
        // printf("path is 3%s\n", path);
    }
    // call discover_direc
    discover_direc(path, file_name, flag_d, flag_f, flag_file);
}
