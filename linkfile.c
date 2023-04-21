#include "shell.h"

/**
 * locate_path - finds the value of the PATH env variable
 * @path: pointer to path buffer
 * @envlist: pointer to envlist linked list
 *
 * Return: 1 if found, 0 if not
 */
int locate_path(char *path, env_t *envlist)
{
    env_t *tmp = envlist;

    while (tmp != NULL)
    {
        if (_strcmp(tmp->var, "PATH") == 0)
        {
            _strcpy(path, tmp->val);
            return 1;
        }

        tmp = tmp->next;
    }

    return 0;
}

/**
 * cat_path - concatenates command to path to search if it's a valid command in path
 * @search_path: env to search
 * @cmd: command to search for
 *
 * Return: 0 if found, -1 if not found
 */
int cat_path(char **search_path, char *cmd)
{
    int i, fd, len;
    char *new;

    new = safe_malloc(BUFSIZE);

    for (i = 0; search_path[i] != NULL; i++)
    {
        _strcpy(new, search_path[i]);
        len = _strlen(new);
        new[len] = '/';

        _strncat(new, cmd, _strlen(cmd));
        fd = access(new, F_OK);
        if (fd == 0)
        {
            _strcpy(cmd, new);
            free(new);
            return 0;
        }
        else
        {
            mem_reset(new, BUFSIZE);
        }
    }

    free(new);
    return -1;
}

/**
 * count_paths - counts how many paths are in the PATH string
 * @path_str: PATH env array
 *
 * Return: number of paths found
 */
int count_paths(char *path_str)
{
    unsigned int i = 0, count = 0;

    if (path_str[0] != '\0')
        count++;

    while (path_str[i] != '\0')
    {
        if (path_str[i] == ':')
            count++;

        i++;
    }

    return count;
}

/**
 * tokenize_path - tokenizer specifically for path
 * @path_str: PATH env variable string
 *
 * Return: pointer to array of path folders
 */
char **tokenize_path(char *path_str)
{
    unsigned int start = 0, end, i = 0, count = 0;
    char **paths;

    paths = safe_malloc((count_paths(path_str) + 1) * sizeof(char *));

    while (1)
    {
        if (path_str[i] == ':' || path_str[i] == '\0')
        {
            end = i;
            if (end == start)
            {
                paths[count] = safe_malloc(3 * sizeof(char));
                _strcpy(paths[count], "./");
            }
            else
            {
                paths[count] = safe_malloc((end - start + 1) * sizeof(char));
                _strncpy(paths[count], &path_str[start], end - start);
            }
            count++;
            start = i + 1;
        }
        if (path_str[i] == '\0')
            break;

        i++;
    }

    paths[count] = NULL;
    return paths;
}

/**
 * free_paths - frees the array of paths
 * @paths: paths
 */
void free_paths(char **paths)
{
    int i = 0;

    while (paths[i] != NULL)
    {
        free(paths[i]);
        i++;
    }

    free(paths);
}
