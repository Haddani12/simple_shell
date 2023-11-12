#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * Return: (s) a pointer to the memory area s
 */
char *_memset(char *c, char d, unsigned int m)
{
	unsigned int j;

	for (j = 0; j < m; j++)
		c[j] = d;
	return (c);
}

/**
 * ffree - frees a string of strings
 * @qq: string of strings
 */
void ffree(char **qq)
{
	char **b = qq;

	if (!qq)
		return;
	while (*qq)
		free(*qq++);
	free(b);
}

/**
 * _realloc - reallocates a block of memory
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *pointer, unsigned int old_size, unsigned int new_size)
{
	char *q;

	if (!pointer)
		return (malloc(new_size));
	if (!new_size)
		return (free(pointer), NULL);
	if (new_size == old_size)
		return (pointer);

	q = malloc(new_size);
	if (!q)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		q[old_size] = ((char *)pointer)[old_size];
	free(pointer);
	return (q);
}
