#include "shell.h"

/**
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t a = 0;
	size_t len_q = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		a = getline(buf, &len_q, stdin);
#else
		a = _getline(info, buf, &len_q);
#endif
		if (a > 0)
		{
			if ((*buf)[a - 1] == '\n')
			{
				(*buf)[a - 1] = '\0';
				a--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = a;
				info->cmd_buf = buf;
			}
		}
	}
	return (a);
}

/**
 * get_input - gets a line minus the newline
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buffer;
	static size_t a, b, len;
	ssize_t c = 0;
	char **buf_q = &(info->arg), *q;

	_putchar(BUF_FLUSH);
	c = input_buf(info, &buffer, &len);
	if (c == -1)
		return (-1);
	if (len)
	{
		b = a;
		q = buffer + a; /* for return */

		check_chain(info, buffer, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buffer, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buffer_type = CMD_NORM;
		}

		*buf_q = q;
		return (_strlen(q));
	}

	*buf_q = buffer;
	return (c);
}

/**
 * read_buf - reads a buffer
 * @a: size
 *
 * Return: c
 */
ssize_t read_buf(info_t *info, char *buf, size_t *a)
{
	ssize_t c = 0;

	if (*a)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*a = c;
	return (c);
}

/**
 * _getline - gets the next line of input from STDIN
 *
 * Return: a
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t b, len;
	size_t g;
	ssize_t c = 0, a = 0;
	char *q = NULL, *new_q = NULL, *a;

	q = *ptr;
	if (q && length)
		a = *length;
	if (b == len)
		b = len = 0;

	c = read_buf(info, buffer, &len);
	if (c == -1 || (c == 0 && len == 0))
		return (-1);

	a = _strchr(buffer + b, '\n');
	g = a ? 1 + (unsigned int)(a - buffer) : len;
	new_q = _realloc(q, a, a ? a + g : g + 1);
	if (!new_q)
		return (q ? free(q), -1 : -1);

	if (a)
		_strncat(new_q, buffer + b, g - b);
	else
		_strncpy(new_q, buffer + b, g - b + 1);

	a += g - b;
	b = g;
	q = new_q;

	if (length)
		*length = a;
	*ptr = q;
	return (a);
}

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
