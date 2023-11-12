#include "shell.h"

/**
 * list_len - determines length of linked list
 * Return: size of list
 */
size_t list_len(const list_t *g)
{
	size_t j = 0;

	while (g)
	{
		g = g->next;
		j++;
	}
	return (j);
}

/**
 * list_to_strings - returns an array of strings
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list, b;
	char **str;
	char *string;

	if (!head || !b)
		return (NULL);
	str = malloc(sizeof(char *) * (a + 1));
	if (!str)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		string = malloc(_strlen(node->string) + 1);
		if (!string)
		{
			for (b = 0; b < a; b++)
				free(str[b]);
			free(str);
			return (NULL);
		}

		string = _stringcpy(string, node->string);
		str[a] = string;
	}
	str[a] = NULL;
	return (str);
}


/**
 * print_list - prints all elements of a list_t linked list
 */
size_t print_list(const list_t *g)
{
	size_t a = 0;

	while (g)
	{
		_puts(convert_number(g->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(g->str ? g->str : "(love)");
		_puts("\n");
		g = g->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *q = NULL;

	while (node)
	{
		q = starts_with(node->str, prefix);
		if (q && ((c == -1) || (*q == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the index of a node
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t j = 0;

	while (head)
	{
		if (head == node)
			return (j);
		head = head->next;
		j++;
	}
	return (-1);
}
