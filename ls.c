#include "headers.h"

// compare function for qsort
int compare(const void *a, const void *b)
{
    return strcmp(*(const char **)a, *(const char **)b);
}

// function to check file type and print the output in color
void color_print(char *name, char *path)
{
    char *color_temp = malloc(sizeof(char) * BUFFER_MAX);
    strcpy(color_temp, path);
    strcat(color_temp, "/");
    strcat(color_temp, name);
    struct stat sb;
    if (stat(color_temp, &sb) == -1)
    {
        perror("stat");
    }
    if (S_ISREG(sb.st_mode))
    {
        // check if it is an executable file
        if ((sb.st_mode & S_IXUSR) || (sb.st_mode & S_IXGRP) || (sb.st_mode & S_IXOTH))
        {
            printf("\033[1;32m%s\033[0m", name);
        }
        else
        {
            printf("%s", name);
        }
    }
    else if (S_ISDIR(sb.st_mode))
    {
        printf("\033[1;34m%s\033[0m", name);
    }
    else
    {
        printf("%s", name);
    }
    free(color_temp);
}

// Function to list files in desired format based on flags and paths
void ls_direc(char *path, int flag_l, int flag_a)
{
    struct stat path_stat;
    stat(path, &path_stat);
    if (S_ISREG(path_stat.st_mode) && flag_l == 0)
    {
        printf("%s\n", path);
        return;
    }
    DIR *dir = opendir(path);
    // directory not found
    if (dir == NULL)
    {
        perror("opendir");
        return;
    }
    struct dirent *entry;
    if (flag_a == 1 && flag_l == 0)
    {
        char **files = malloc(sizeof(char *) * 100);
        int i = 0;
        while ((entry = readdir(dir)) != NULL)
        {
            files[i] = malloc(sizeof(char) * 100);
            strcpy(files[i], entry->d_name);
            i++;
        }
        // sorting the files
        qsort(files, i, sizeof(char *), compare);
        // printing the files
        for (int j = 0; j < i; j++)
        {
            color_print(files[j], path);
            printf("\n");
        }
        // free the files
        for (int j = 0; j < i; j++)
        {
            free(files[j]);
        }
        free(files);
    }
    else if (flag_a == 0 && flag_l == 0)
    {
        char **files = malloc(sizeof(char *) * BUFFER_MAX);
        int i = 0;
        // reading files apart from hidden files
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_name[0] != '.')
            {
                files[i] = malloc(sizeof(char) * BUFFER_MAX);
                strcpy(files[i], entry->d_name);
                i++;
            }
        }
        // sorting the files
        qsort(files, i, sizeof(char *), compare);
        // printing the files
        for (int j = 0; j < i; j++)
        {
            color_print(files[j], path);
            printf("\n");
        }
        // free the files
        for (int j = 0; j < i; j++)
        {
            free(files[j]);
        }
        free(files);
    }
    else if (flag_l == 1)
    {
        char **files = malloc(sizeof(char *) * BUFFER_MAX);
        int i = 0;
        // if flag_a == 1 read hidden files as well, else read only non-hidden files
        if (flag_a == 1)
        {
            while ((entry = readdir(dir)) != NULL)
            {
                // reading the file name and qsort it
                files[i] = malloc(sizeof(char) * BUFFER_MAX);
                strcpy(files[i], entry->d_name);
                i++;
            }
        }
        else
        {
            while ((entry = readdir(dir)) != NULL)
            {
                if (entry->d_name[0] != '.')
                {
                    files[i] = malloc(sizeof(char) * BUFFER_MAX);
                    strcpy(files[i], entry->d_name);
                    i++;
                }
            }
        }
        // sorting the files
        qsort(files, i, sizeof(char *), compare);
        // printing total number of blocks
        struct stat fileStat;
        int total = 0;
        for (int j = 0; j < i; j++)
        {
            char *temp = malloc(sizeof(char) * BUFFER_MAX);
            strcpy(temp, path);
            strcat(temp, "/");
            strcat(temp, files[j]);
            if (stat(temp, &fileStat) < 0)
            {
                perror("stat");
                return;
            }
            total += fileStat.st_blocks;
            free(temp);
        }
        printf("total %d\n", total / 2);
        for (int j = 0; j < i; j++)
        {
            struct stat fileStat;
            char *file = malloc(sizeof(char) * BUFFER_MAX);
            strcpy(file, path);
            strcat(file, "/");
            strcat(file, files[j]);
            if (stat(file, &fileStat) < 0)
            {
                perror("stat");
                return;
            }
            // print the file permissions
            printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf(" ");
            // print the number of links
            printf("%ld ", fileStat.st_nlink);
            // print the user name
            struct passwd *pw = getpwuid(fileStat.st_uid);
            printf("%s ", pw->pw_name);
            // print the group name
            struct group *gr = getgrgid(fileStat.st_gid);
            printf("%s ", gr->gr_name);
            // print the file size
            printf("%ld ", fileStat.st_size);
            // print the time of last modification
            char *time = ctime(&fileStat.st_mtime);
            time[strlen(time) - 1] = '\0';
            printf("%s ", time);
            // print the file name
            color_print(files[j], path);
            printf("\n");
            free(file);
        }
        // free the files
        for (int j = 0; j < i; j++)
        {
            free(files[j]);
        }
        free(files);
    }
    closedir(dir);
}

// Main function for ls
void ls(char **tokens)
{
    int flag_a = 0;
    int flag_l = 0;
    int index = 0;
    int flag_path = 0;
    int path_counter = 0;
    char *path = (char *)malloc(sizeof(char) * BUFFER_MAX);
    char **paths = malloc(sizeof(char *) * BUFFER_MAX);
    while (index < arg_count - 1)
    {
        if (strcmp(tokens[index], "-a") == 0)
        {
            flag_a = 1;
        }
        else if (strcmp(tokens[index], "-l") == 0)
        {
            flag_l = 1;
        }
        else if (strcmp(tokens[index], "-al") == 0 || strcmp(tokens[index], "-la") == 0)
        {
            flag_a = 1;
            flag_l = 1;
        }
        else
        {
            paths[path_counter] = malloc(sizeof(char) * BUFFER_MAX);
            strcpy(paths[path_counter], tokens[index]);
            path_counter++;
        }
        index++;
    }
    if (path_counter == 0)
    {
        paths[path_counter] = malloc(sizeof(char) * BUFFER_MAX);
        strcpy(paths[path_counter], ".");
        path_counter++;
    }
    
    if (path_counter == 1)
    {
        ls_direc(paths[0], flag_l, flag_a);
    }
    else
    {
        for (int i = 0; i < path_counter; i++)
        {
            printf("%s:\n", paths[i]);
            ls_direc(paths[i], flag_l, flag_a);
            printf("\n");
        }
    }
    // free everything
    for (int i = 0; i < path_counter; i++)
    {
        free(paths[i]);
    }
    free(paths);
}