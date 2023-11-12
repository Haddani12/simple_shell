#include "shell.h"

/**
 * **strtow - splits a string into words. Repeat delimiters
 * @d: the delimeter string
 * Return: a pointer to an array of strings, or NULL on failure
 */

char **strtow(char *str, char *d)
{
	int a, b, g, n, nwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (a = 0; str[a] != '\0'; a++)
		if (!is_delim(str[a], d) && (is_delim(str[a + 1], d) || !str[a + 1]))
			nwords++;

	if (nwords == 0)
		return (NULL);
	c = malloc((1 + nwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (is_delim(str[a], d))
			a++;
		g = 0;
		while (!is_delim(str[a + g], d) && str[a + g])
			g++;
		c[b] = malloc((g + 1) * sizeof(char));
		if (!c[b])
		{
			for (g = 0; g < b; g++)
				free(c[g]);
			free(c);
			return (NULL);
		}
		for (n = 0; n < g; n++)
			c[b][n] = str[a++];
		c[b][n] = 0;
	}
	c[b] = NULL;
	return (c);
}

/**
 * **strtow2 - splits a string into words
 * @d: the delimeter
 * Return: a pointer to an array of strings, or NULL on failure
 */
char **strtow2(char *str, char d)
{
	int a, b, g, n, nwords = 0;
	char **c;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (a = 0; str[a] != '\0'; a++)
		if ((str[a] != d && str[a + 1] == d) ||
				(str[a] != d && !str[a + 1]) || str[a + 1] == d)
			nwords++;
	if (nwords == 0)
		return (NULL);
	c = malloc((1 + nwords) * sizeof(char *));
	if (!c)
		return (NULL);
	for (a = 0, b = 0; b < nwords; b++)
	{
		while (str[a] == d && str[a] != d)
			a++;
		g = 0;
		while (str[a + g] != d && str[a + g] && str[a + g] != d)
			g++;
		c[b] = malloc((g + 1) * sizeof(char));
		if (!c[b])
		{
			for (g = 0; g < b; g++)
				free(c[g]);
			free(c);
			return (NULL);
		}
		for (n = 0; n < g; n++)
			c[b][n] = str[a++];
		c[b][n] = 0;
	}
	c[b] = NULL;
	return (c);
}
