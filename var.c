#include "shell.h"

/**
 * is_chain - The function tests if current char in buf is a chain delim
 * @info: Refers to the parameter struct;
 * @buf: Refers to the char buffer;
 * @p: Refers to address of current position in buf;
 * Return: 1, if chain delimeter,0, if  otherwise
 */

int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t y = *p;

	if (buf[y] == '|' && buf[y + 1] == '|') /*   */
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[y] == '&' && buf[y + 1] == '&')
	{
		buf[y] = 0;
		y++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[y] == ';')
	{
		buf[y] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = y;
	return (1);
}


/**
 * check_chain- This checks we should continue chaining based on last status
 * @info: Refers-to the paramet struct;
 * @buf: Refers-to the char buf;
 * @p: Refers to addr of current position in buf;
 * @i: Refers to the start position in buf;
 * @lent: Refers to length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t lent)
{
	size_t k = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			k = lent;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			k = lent;
		}
	}

	*p = k;
}


/**
 * replace_alias - This function replaces an aliases in the tokenized str
 * @info: Refers to the parameter struct;
 * Return: 1, if replaced, 0, if  otherwise
 */

int replace_alias(info_t *info)
{
	int a;
	list_t *node;
	char *p;

	for (a = 0; a < 10; a++) /*     */
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}


/**
 * replace_vars - This function replaces vars in the tokenized str;
 * @info: Refers to the parameter struct;
 *
 * Return: 1, if replaced, 0, if otherwise.
 */

int replace_vars(info_t *info)
{
	int u = 0;
	list_t *node;

	for (u = 0; info->argv[u]; u++)
	{
		if (info->argv[u][0] != '$' || !info->argv[u][1])
			continue;

		if (!_strcmp(info->argv[u], "$?"))
		{
			replace_string(&(info->argv[u]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[u], "$$")) /*   */
		{
			replace_string(&(info->argv[u]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[u][1], '=');
		if (node)
		{
			replace_string(&(info->argv[u]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[u], _strdup(""));

	}
	return (0);
}

/**
 * replace_string - This function replaces str
 * @old: Refers to the addr of old str
 * @new: Refers to the new str
 *
 * Return: 1, if replaced, 0, if otherwise.
 */

int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

