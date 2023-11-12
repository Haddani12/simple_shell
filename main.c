#include "shell.h"

/**
 * main - entry point*
 * Return: 0 on success, 1 on error
 */
int main(int ad, char **ab)
{
	info_t info[] = { INFO_INIT };
	int fg = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fg)
			: "r" (fg));

	if (ad == 2)
	{
		fg = open(ab[1], O_RDONLY);
		if (fg == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(ab[0]);
				_eputs(": 0: Can not  open ");
				_eputs(ab[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fg;
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, ab);
	return (EXIT_SUCCESS);
}
