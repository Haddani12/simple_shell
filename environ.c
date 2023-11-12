#include "shell.h"

/**
 * _myenv - the current environ
 * @info: this struct containing potential arguments
 * Return 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @nom: environ variable name
 * Return: the value
 */
char *_getenv(info_t *info, const char *nom)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, nom);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv -  this Initialize a new environment variable,
 *  Return 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 8)
	{
		_eputs("Incorrect number arg\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv -  this remove an environment variable
 * Return 0
 */
int _myunsetenv(info_t *info)
{
	int j;

	if (info->argc == 1)
	{
		_eputs("arguements.\n");
		return (1);
	}
	for (j = 1; j <= info->argc; j++)
		_unsetenv(info, info->argv[j]);

	return (0);
}

/**
 * populate_env_list - populates environ linked list
 * Return:0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}
