#include "shell.h"

/**
 * is_cmd - determines if a file is an executable command
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *pat)
{
	struct stat struc;

	(void)info;
	if (!pat || stat(pat, &struc))
		return (0);

	if (struc.struc_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates characters
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int j = 0, g = 0;

	for (g = 0, j = start; j < stop; j++)
		if (pathstr[j] != ':')
			buffer[g++] = pathstr[j];
	buffer[g] = 0;
	return (buffer);
}

/**
 * find_path - finds this cmd in the PATH string
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int j = 0, current_position = 0;
	char *pat;

	if (!patstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!patstr[j] || patstr[j] == ':')
		{
			pat = dup_chars(patstr, current_position, j);
			if (!*pat)
				_strcat(pat, cmd);
			else
			{
				_strcat(pat, "/");
				_strcat(pat, cmd);
			}
			if (is_cmd(info, pat))
				return (pat);
			if (!patstr[j])
				break;
			current_position = j;
		}
		j++;
	}
	return (NULL);
}
