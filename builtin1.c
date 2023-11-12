#include "shell.h"

/**
 * _myhistory - displays the history list
 * @info:  this struct containing potential arguments
 *  Return: 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets alias to string
 * Return: success 0,  error 1.
 */
int unset_alias(info_t *info, char *str)
{
	char *p, c;
	int hist;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	c= *p;
	* p= 0;
	hist = delete_at_index(&(info->alias),
			get_index(info->alias, node_starts_with(info->alias, str, -1)));
	*p = c;
	return (hist);
}

/**
 * set_alias - this code  sets alias to string
 */
int set_alias(info_t *info, char *str)
{
	char *p;

	p = _strchr(str, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias
 * @node: alias node
 */
int print_alias(list_t *node)
{
	char *p = NULL, *d = NULL;

	if (node)
	{
		p = _strchr(node->str, '=');
		for (d = node->str; d<= p; d++)
			_putchar(*d);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - mimics the alias builtin
 * @info: the structure containing arguments
 */
int _myalias(info_t *info)
{
	int j = 0;
	char *p = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		p = _strchr(info->argv[j], '=');
		if (p)
			set_alias(info, info->argv[j]);
		else
			print_alias(node_starts_with(info->alias, info->argv[j], '='));
	}

	return (0);
}
