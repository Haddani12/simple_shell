#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimete
 * @buffer
 * @q: address of current position in buf
 *
 * Return: 1 if chain delimeter, 0 otherwise
 */
int is_chain(info_t *info, char *buffer, size_t *q)
{
	size_t i = *q;

	if (buffer[i] == '|' && buffer[i + 1] == '|')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buffer[i] == '&' && buffer[i + 1] == '&')
	{
		buffer[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buffer[i] == ';')
	{
		buffer[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*q = i;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @buffer
 * @q: address of current position in buf
 * @a: starting position in buffer
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buffer, size_t *q, size_t a, size_t len)
{
	size_t i = *q;

	if (info->cmd_buffer_type == CMD_AND)
	{
		if (info->status)
		{
			buffer[a] = 0;
			i = len;
		}
	}
	if (info->cmd_buffer_type == CMD_OR)
	{
		if (!info->status)
		{
			buffer[a] = 0;
			i = len;
		}
	}

	*q = i;
}

/**
 * replace_alias - replaces an aliases in the tokenized string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int j;
	list_t *node;
	char *q;

	for (j = 0; j < 10; j++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		q = _strchr(node->str, '=');
		if (!q)
			return (0);
		q = _strdup(q + 1);
		if (!q)
			return (0);
		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces vars in the tokenized string
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int j = 0;
	list_t *node;

	for (j = 0; info->argv[j]; j++)
	{
		if (info->argv[j][0] != '$' || !info->argv[j][1])
			continue;

		if (!_strcmp(info->argv[j], "$?"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[j], "$$"))
		{
			replace_string(&(info->argv[j]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[j][1], '=');
		if (node)
		{
			replace_string(&(info->argv[j]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[j], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: address of old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}














#include "shell.h"

int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * @d: the char to check
 * @delimeter: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char d, char *delimeter)
{
	while (*delimeter)
		if (*delimeter++ == d)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @d: The character to input
 * Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int d)
{
	if ((d >= 'a' && d <= 'z') || (d >= 'A' && d <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @d: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *d)
{
	int j, sign = 1, flag = 0, output;
	unsigned int reslt = 0;

	for (j = 0; d[j] != '\0' && flag != 2; j++)
	{
		if (d[j] == '-')
			sign *= -1;

		if (d[j] >= '0' && d[j] <= '9')
		{
			flag = 1;
			reslt *= 10;
			reslt += (d[j] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -reslt;
	else
		output = reslt;

	return (output);
}
