#include "shell.h"


/**
 * hsh - Referrs to the main shell loop;
 * @av: Refers to the argu vector from;
 * @info: Referrs to the parametre infostruct;
 *
 * Compl
 * Return: 0 on success; 1 on error, or error code
 */


int hsh(info_t *info, char **av)
{
	ssize_t f = 0;
	int builtin_ret = 0;

	while (f != -1 && builtin_ret != -2)
	{
		clear_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		f = get_input(info);
		if (f != -1)
		{
			set_info(info, av);
			builtin_ret = find_builtin(info);
			if (builtin_ret == -1)
				find_cmd(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	write_history(info);
	free_info(info, 1);
	if (!interactive(info) && info->status) /* chcks 4 conditions */
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}



/**
 * find_builtin - This funct finds a builtin cmd;
 * @info: Refers to the paramet & return info struct,
 * Return: -1 if builtin not found,
 * 0 if builtin executed successfully;
 * 1 if builtin found but not successful, -2 -builtin signals exit.
 */

int find_builtin(info_t *info)
{
	int w, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (w = 0; builtintbl[w].type; w++) /* Checks for builtin cmd */
		if (_strcmp(info->argv[0], builtintbl[w].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[w].func(info);
			break;
		}
	return (built_in_ret);
}


/**
 * find_cmd - This funct finds a cmd in PATH;
 * @info: Refers to the paramet info struct;
 * Return: void.
 */

void find_cmd(info_t *info)
{
	char *path = NULL;
	int u, v;

	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (u = 0, v = 0; info->arg[u]; u++) /*   */
		if (!is_delim(info->arg[u], " \t\n"))
			v++;
	if (!v)
		return;

	path = find_path(info, _getenv(info, "PATH="), info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_cmd(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(info, info->argv[0]))
			fork_cmd(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}



/**
 * fork_cmd - Th1s funct forks an exec thread to run cmd;
 * @info: Refers to the parametr info struct;
 * Return: void;
 */

void fork_cmd(info_t *info)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1) /* Investigates the conditions*/
	{
		/* TODO: PUT ERr FUNCt   */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status)) /*    */
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

