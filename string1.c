#include "shell.h"

/**
 * _strcpy - copies a string
 * @destination
 * @source
 *
 * Return: pointer to destination
 */
char *_strcpy(char *destination, char *source)
{
	int j = 0;

	if (destination == source || source == 0)
		return (destination);
	while (source[j])
	{
		destination[j] = source[j];
		j++;
	}
	destination[j] = 0;
	return (destination);
}

/**
 * _strdup - duplicates a string
 * Return: pointer to the duplicated string
 */
char *_strdup(const char *string)
{
	int leng = 0;
	char *mal;

	if (string == NULL)
		return (NULL);
	while (*string++)
		leng++;
	mal = malloc(sizeof(char) * (leng + 1));
	if (!mal)
		return (NULL);
	for (leng++; leng--;)
		mal[leng] = *--string;
	return (mal);
}

/**
 * _puts - prints an input string
 * Return: Nothing
 */
void _puts(char *string)
{
	int j = 0;

	if (!string)
		return;
	while (string[j] != '\0')
	{
		_putchar(string[j]);
		j++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @b: The character to print
 * Return: On success 1.
 */
int _putchar(char b)
{
	static int j;
	static char buffer[WRITE_BUF_SIZE];

	if (b == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(1, buffer, j);
		j = 0;
	}
	if (b != BUF_FLUSH)
		buffer[j++] = b;
	return (1);
}
