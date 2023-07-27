#include "shell.h"

/**
 * _myexit - This function exits the shell
 * @info: Refers to the Structure containing potential arg.
 *          It is used to maintain constant function prototype.
 * Completed by Scylla-Salaza
 * Return: exits with a given exit status
 *         (-2) if info.argv[1] != "exit"
 */

int _myexit(info_t *info)
{
	int exit_checker;

	if (info->argv[1])
	{
		exit_checker = _erratoi(info->argv[1]);
		if (exit_checker == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
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
 * _mycd - This function changes the current directory of the process
 * @info: Refers to the structure containing potential.
 *          This is used to maintain constant function prototype.
 *
 *  Return: Always 0
 */
int _mycd(info_t *info)
{
	char *ch, *direct, buffer[1024];
	int chdir_ret;

	ch = getcwd(buffer, 1024);
	if (!ch)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		direct = _getenv(info, "HOME=");
		if (!direct)
			chdir_ret = /* */
				chdir((direct = _getenv(info, "PWD=")) ? direct : "/");
		else
			chdir_ret = chdir(direct);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(ch);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((direct = _getenv(info, "OLDPWD=")) ? direct : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myhelp - This function changes the current directory of the process
 * @info: Refers to the Structure containing potential args.
 *          This is used to maintain constant function prototype.
 *
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

