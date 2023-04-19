#include "shell.h"

/**
 * file_path - assembles path to cd into
 * @commands: array of pointer pointing to commands
 * @envlist: head of env linked list
 *
 * Return: full filepath
 */
char *file_path(char **commands, env_t *envlist)
{
    env_t *fetched_home = fetch_node(envlist, "HOME");
    env_t *fetched_old = fetch_node(envlist, "OLDPWD");
    int hyphen = 0;
    char *path = safe_malloc(1024);

    if (commands[1] != NULL)
        hyphen = strncmp(commands[1], "-", 1);

    if (commands[1] == NULL)
        path = strcpy(path, fetched_home->val);
    else if (hyphen == 0)
        path = strcpy(path, fetched_old->val);
    else if (commands[1][0] == '/')
        path = strcpy(path, commands[1]);
    else
    {
        getcwd(path, 1024);
        strncat(path, "/", 1);
        strncat(path, commands[1], strlen(commands[1]));
    }

    return (path);
}


/**
 * _cd - builtin cd function
 * @arginv: arg inventory
 *
 * Return: 0 if good, -1 if bad
 */
int _cd(arg_inventory_t *arginv)
{
    char *path, *oldpwd, *pwd;
    int check;

    oldpwd = safe_malloc(1024);
    pwd = safe_malloc(1024);

    getcwd(oldpwd, 1024);

    char **commands = arginv->commands;
    path = file_path(commands, arginv->envlist);

    check = chdir(path);

    if (check == -1)
    {
        free(oldpwd);
        free(pwd);
        free(path);
        return (2);
    }
    else
    {
        getcwd(pwd, 1024);
        modify_node_env(&arginv->envlist, "PWD", pwd);
        modify_node_env(&arginv->envlist, "OLDPWD", oldpwd);
    }

    free(oldpwd);
    free(pwd);
    free(path);

    return (0);
}
