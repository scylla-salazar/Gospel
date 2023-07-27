#include "shell.h"

/**
 * clear_info - This funct initializes info_t struct
 * @info: Refers to the struct addr.
 */

void clear_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * set_info - Ths funct initializes info_t struct.
 * @info: ReferRs to the struct add.
 * @av: Refers to the arg vector.
 *
 */

void set_info(info_t *info, char **av)
{
	int jah = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = str_tok(info->arg, " \t");
		if (!info->argv) /* chcks 4 conditions */
		{

			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		
		for (jah = 0; info->argv && info->argv[jah]; jah++)
			;
		info->argc = jah;

		replace_alias(info);
		replace_vars(info);
	}
}

/**
 * free_info - This func frees info_t struct fields.
 * @all: true (freing all fields).
 * @info: Referrs to the struct add.
 *
 */


void free_info(info_t *info, int all)
{
	ffree(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all) /* if freeing all fields */
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			free_list(&(info->env));
		if (info->history)
			free_list(&(info->history));
		if (info->alias)
			free_list(&(info->alias));
		ffree(info->environ);
			info->environ = NULL;
		bfree((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}

