#include "shell.h"

/**
 * file_path - assembles path to cd into
 * @commands: array of pointer pointg to commands
 * @envlist: head of env linked list
 *
 * Return: full filepath
 */
char *file_path(char **commands, env_t *envlist)
{
	env_t *fetched_home = fetch_node(envlist, "HOME");
	env_t *fetched_old = fetch_node(envlist, "OLDPWD");
	int hyphen = commands[1] ? _strncmp(commands[1], "-", 1) : 1;
	char *path = safe_malloc(PATH_MAX);

	if (!path)
		return (NULL);
	if (!commands[1])
		path = _strcpy(path, fetched_home->val);
	else if (hyphen == 0)
		path = _strcpy(path, fetched_old->val);
	else if (commands[1][0] == '/')
		path = _strcpy(path, commands[1]);
	else
	{
		if (!getcwd(path, PATH_MAX))
		{
			free(path);
			return (NULL);
		}
		_strncat(path, "/", 1);
		_strncat(path, commands[1], _strlen(commands[1]));
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
	char *path, *oldpwd, *pwd, **commands;
	int check;

	oldpwd = safe_malloc(1024);
	pwd = safe_malloc(1024);

	getcwd(oldpwd, 1024);

	commands = (char **)arginv->commands;

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
