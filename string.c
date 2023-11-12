#include "shell.h"

/**
 * _strlen - returns the length of a string
 * Return: integer length of string
 */
int _strlen(char *s)
{
	int j = 0;

	if (!s)
		return (0);

	while (*s++)
		j++;
	return (j);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @c1: the first strang
 * @c2: the second strang
 *
 * Return: negative if c1 < c2, positive if c1 > c2, zero if c1 == c2
 */
int _strcmp(char *c1, char *c2)
{
	while (*c1 && *c2)
	{
		if (*c1 != *c2)
			return (*c1 - *c2);
		c1++;
		c2++;
	}
	if (*c1 == *c2)
		return (0);
	else
		return (*c1 < *c2 ? -1 : 1);
}

/**
 * starts_with - checks if needle starts with haystack
 * Return: address of next char of haystack or NULL
 */
char *starts_with(const char *hstck, const char *nedle)
{
	while (*nedle)
		if (*nedle++ != *hstck++)
			return (NULL);
	return ((char *)hstck);
}

/**
 * _strcat - concatenates two strings
 * @destination: the buffer
 * @source: the buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *destination, char *source)
{
	char *ret = destination;

	while (*destination)
		destination++;
	while (*source)
		*destination++ = *source++;
	*destination = *source;
	return (ret);
}
