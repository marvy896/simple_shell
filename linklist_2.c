#include "shell.h"

/**
 * _alias - builtin func to set alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _alias(arg_inventory_t *arginv)
{
	char *input, **combo, **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		write_alias(arginv->alias);
		return (EXT_SUCCESS);
	}
	else if (commands[2] != NULL)
	{
		_perror("alias: too many arguments.\n");
		return (-1);
	}

	input = commands[1];

	combo = separate_string(input);

	if (modify_node_alias(&arginv->alias, combo[0], combo[1]) == EXT_FAILURE)
		add_node_alias(&arginv->alias, combo[0], combo[1]);

	free(combo[0]);
	free(combo[1]);
	free(combo);
	return (EXT_SUCCESS);
}

/**
 * _unalias - builtin func to unset alias
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int _unalias(arg_inventory_t *arginv)
{
	char **commands;

	commands = (char **)arginv->commands;

	if (commands[1] == NULL)
	{
		_perror("unalias: missing arguments.\n");
		return (-1);
	}

	if (commands[2] != NULL)
	{
		_perror("unalias: too many arguments.\n");
		return (-1);
	}

	if (remove_node_alias(&arginv->alias, commands[1]) == EXT_SUCCESS)
		return (EXT_SUCCESS);

	return (EXT_FAILURE);
}

/**
 * shell_help - prints help commands info based on the other input argument
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
typedef struct {
    char *name;
    int (*func)(int argc, char **argv);
} bins_t;

// Define the help functions
int help_exit(int argc, char **argv) {
    printf("This is the help message for the exit command.\n");
    return 0;
}

int help_env(int argc, char **argv) {
    printf("This is the help message for the env command.\n");
    return 0;
}

int help_setenv(int argc, char **argv) {
    printf("This is the help message for the setenv command.\n");
    return 0;
}

int help_unsetenv(int argc, char **argv) {
    printf("This is the help message for the unsetenv command.\n");
    return 0;
}

int help_history(int argc, char **argv) {
    printf("This is the help message for the history command.\n");
    return 0;
}

// Define the shell_help function
int shell_help(int argc, char **argv) {
    // Define the bins array with correct syntax
    bins_t bins[] = {
        {"exit", help_exit},
        {"env", help_env},
        {"setenv", help_setenv},
        {"unsetenv", help_unsetenv},
        {"history", help_history},
    };

    // Print the help message for each command
    for (int i = 0; i < sizeof(bins) / sizeof(bins[0]); i++) {
        printf("%s\n", bins[i].name);
    }

    return 0;
}

int main() {
    char *args[] = {"help", NULL};
    shell_help(1, args);
    return 0;
}


/**
 * shell_exit - exit status to exit
 * @arginv: arguments inventory
 *
 * Return: 0 on success
 */
int shell_exit(arg_inventory_t *arginv)
{
	char **commands;
	int es;

	commands = (char **)arginv->commands;
	if (commands[1] == NULL)
		arginv->exit = 1;
	else if (is_uint(commands[1]))
	{
		es = _atoi(commands[1]);
		arginv->exit = 1;
		arginv->exit_status = es;
	}
	else
		_perror("exit: Illegal number\n");

	return (EXT_SUCCESS);
}
