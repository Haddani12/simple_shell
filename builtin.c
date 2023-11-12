#include "shell.h"
int _myexit(info_t *info)
{
	int exitch;

	if (info->argv[1]) 
	{
		exitch = _erratoi(info->argv[1]);
		if (exitch == -1)
		{
			info->status = 2;
			print_error(info, "No legal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * current directory 
 * @info: the struct containing potential argument 
 * Return:0
 */
int _mycd(info_t *info)
{
	char *c, *mydir, buffer[1500];
	int chdir;

	c = getcwd(buffer, 1500);
	if (!c)
		_puts("get pwd message failure \n");
	if (!info->argv[1])
	{
		mydir = _getenv(info, "myhome=");
		if (!mydir)
			chdir = 
				chdir((mydir = _getenv(info, "PWD=")) ? mydir : "/");
		else
			chdir = chdir(mydir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLD PWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLD PWD=")), _putchar('\n');
		chdir =
			chdir((mydir = _getenv(info, "OLD PWD=")) ? mydir : "/");
	}
	else
		chdir = chdir(info->argv[1]);
	if (chdir == -1)
	{
		print_error(info, "can not cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLD PWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1500));
	}
	return (0);
}

/**
 * changes the current directory of the process. _myhelp
 * @info: Structure containing potential arguments
 * Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **mydirectory;

	mydirectory = info->argv;
	_puts("help call works. \n");
	if (0)
		_puts(*mydirectory);
	return (0);
}
