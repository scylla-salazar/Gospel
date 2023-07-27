#include "shell.h"

/**
 * get_environ - This funct returns the str array copy of our env
 * @info: Refers to the Structure containing potential arg.
 *   used to maintain const funct prototype.
 * Completedsalazar
 * Return: always (0.
 */

char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed) /* */
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - This funct removes an env var
 * @info: Referrs to the Structure containing potential args.
 *   used to maintain const funct prototype.
 *
 *  Return: 1 (on delete), 0 (else)
 * @var: the str env var property
 */

int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *w;

	if (!node || !var)
		return (0);

	while (node)
	{
		w = starts_with(node->str, var);
		if (w && *w == '=') /* testin conditions*/
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Ths func initializes a new envir var,
 *  / modify existing one
 * @info: Referss to the Structure containing potential args.
 *   used to maintain const funct prototype.
 * @var: Refers to the string environ var property.
 *
 * @value: Referrs to the str env var value.
 * Return: always (0).
 */

int _setenv(info_t *info, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *z;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf) /*   */
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = info->env;
	while (node) /*  */
	{
		z = starts_with(node->str, var);
		if (z && *z == '=')
		{
			free(node->str);
			node->str = buf;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buf, 0);
	free(buf);
	info->env_changed = 1;
	return (0);
}

