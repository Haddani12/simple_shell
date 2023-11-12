i#include "shell.h"

/**
 * _eputs - prints an input string
 * Return: Nothing
 */
void _eputs(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (str[j] != '\0')
	{
		_eputchar(string[j]);
		j++;
	}
}

/**
 * _eputchar - writes the character
 * @d caractere to print
 * Return: On success 1
 */
int _eputchar(char d)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buf[j++] = d;
	return (1);
}

/**
 * _putfg - writes the character d to given fg
 * @d: The character to print
 * @fd: The filedescriptor to print
 * Return: On success 1.
 */
int _putfg(char d, int fg)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (d == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(fg, buffer, j);
		j = 0;
	}
	if (d != BUF_FLUSH)
		buffer[j++] = d;
	return (1);
}

/**
 * _putsfd - prints an input string
 *
 * Return: the number of chars put
 */
int _putsfg(char *string, int fg)
{
	int j = 0;

	if (!string)
		return (0);
	while (*string)
	{
		j += _putfg(*string++, fg);
	}
	return (j);
}
