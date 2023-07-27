#include "shell.h"

/**
 * _myhistory - The function displays the history list, 1 cmd by line,
 * preceded with line nums, start at 0.
 * @info: Refers to the Struct containing potential .
 *  Used to maintain const func prototype.
 * Completed by scylla-salaza.
 *  Return: always (0)
 */


int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}


/**
 * unset_alias - This funct sets alias to str
 * @info: Refers to parameter struct
 * @str: Refers to the string alias
 *
 * Return: 0 (success), 1 on error
 */


int unset_alias(info_t *info, char *str)
{
	char *x, y;
	int ret;

	x = _strchr(str, '=');
	if (!x)
		return (1);
	y = *x;
	*x = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*x = y;
	return (ret);
}



/**
 * set_alias - Th1s funct sets alias to str
 * @info: Referrs to parametr struct
 * @str: Refers to the str alias
 *
 * Return: 0 (success), 1 on error
 */


int set_alias(info_t *info, char *str)
{
	char *ch;

	ch = _strchr(str, '=');
	if (!ch)
		return (1);
	if (!*++ch)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}


/**
 * print_alias - This funct prints an alias str
 * @node: Referrs to d alias node
 *
 * Return: always 0 (success), 1 on error
 */


int print_alias(list_t *node)
{
	char *x = NULL, *y = NULL;

	if (node)
	{
		x = _strchr(node->str, '=');
		for (y = node->str; y <= x; y++)
			_putchar(*y);
		_putchar('\'');
		_puts(x + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}



/**
 * _myalias - This func mimics the alias builtin
 * @info: Refers to the Struct containing potential args.
 *  Used to maintain const funct prototype.
 *
 *  Return: always (0)
 */


int _myalias(info_t *info)
{
	int t = 0;
	char *x = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (t = 1; info->argv[t]; t++)
	{
		x = _strchr(info->argv[t], '=');
		if (x)
			set_alias(info, info->argv[t]);
		else
			print_alias(node_starts_with(info->alias, info->argv[t], '='));
	}

	return (0);
}

