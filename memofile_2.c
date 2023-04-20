#include "shell.h"

/**
 * save_alias - saves alias definitions to a file
 * @arginv: pointer to the argument inventory
 *
 * Return: 0 on success, 1 on failure
 */
int save_alias(arg_inventory_t *arginv)
{
	alias_t *tmp = arginv->alias;
	char *file = arginv->alias_file;
	char *buffer;
	int fd;

	fd = open(file, O_CREAT | O_WRONLY | O_TRUNC, 0666);
	if (fd == -1)
		return 1;

	while (tmp != NULL)
	{
		buffer = (char *)safe_malloc(_strlen(tmp->alias) + _strlen(tmp->command) + 4);
		_strcpy(buffer, tmp->alias);
		_strcat(buffer, ":");
		_strcat(buffer, tmp->command);
		_strcat(buffer, "\n");
		append_text_to_file(file, buffer);
		tmp = tmp->next;
		free(buffer);
	}

	close(fd);
	return 0;
}

/**
 * load_alias - loads alias definitions from a file
 * @arginv: pointer to the argument inventory
 *
 * Return: 0 on success, 1 on failure
 */
int load_alias(arg_inventory_t *arginv)
{
	ssize_t count;
	size_t sz = BUFSIZE;
	char *file = arginv->alias_file;
	char *buffer = NULL, *val = NULL;
	int fd;

	fd = open(file, O_RDONLY);
	if (fd == -1)
		return 1;

	buffer = (char *)safe_malloc(sz);

	while ((count = _readline(fd, &buffer, &sz)) > 0)
	{
		while (count > 0 && buffer[count - 1] == '\n')
			buffer[--count] = '\0';

		val = buffer;
		while (*val != '\0' && *val != ':')
			val++;

		if (*val == '\0')
			continue;

		*val++ = '\0';
		add_node_alias(&arginv->alias, buffer, val);
	}

	free(buffer);
	close(fd);
	return 0;
}

/**
 * fetch_node_alias - fetches a node of a given alias
 * @head: pointer to the head of the list
 * @var: alias to match the node to fetch
 *
 * Return: fetched node or NULL
 */
alias_t *fetch_node_alias(alias_t *head, char *var)
{
	alias_t *tmp = head;

	while (tmp != NULL)
	{
		if (_strcmp(tmp->alias, var) == 0)
			return tmp;

		tmp = tmp->next;
	}

	return NULL;
}
