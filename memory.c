#include "shell.h"

/**
 * bfree - frees a pointer and NULLs the address
 * @pointer: address of the pointer
 * Return: 1 if freed, otherwise 0.
 */
int bfree(void **pointer)
{
	if (pointer && *pointer)
	{
		free(*pointer);
		*pointer = NULL;
		return (1);
	}
	return (0);
}
