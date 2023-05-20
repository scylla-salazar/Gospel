#include "shell.h"

/**
 * _myenv - s function prints the current environment
 * @info: Refers to the Structure containing potential arguments.
 *          This is used to maintain constant function prototype.
 * Completed by scylla-salazar on 20th May 2023.
 * Return: Always 0
 */

int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - This function gets the value of an environ variable
 * @info: Refers to the Structure containing potential arguments.
 * 	    This is used to maintain constant function prototype.
 * @name: Refers to environ var name
 *
 * Return: the value
 */

char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *x;

	while (node)
	{
		x = starts_with(node->str, name);
		if (x && *x)
			return (x);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - This function initializes a new environment variable,
 *             or modify an existing one
 * @info: Refers to the Structure containing potential arguments.
 *          This is used to maintain constant function prototype.
 *
 * Return: 0 on success; 1 on failure
 */

int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - This function Removes an environment variable
 * @info: Refers to the Structure containing potential arguments.
 *          This is used to maintain constant function prototype.
 *
 * Return: 0 on Success, 1 on failure.
 */

int _myunsetenv(info_t *info)
{
	int a;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= info->argc; a++)
		_unsetenv(info, info->argv[a]);

	return (0);
}

/**
 * populate_env_list - This function populates env linked list
 * @info: Refers to the Structure containing potential arguments.
 *          This is used to maintain constant function prototype.
 *
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t j;

	for (j = 0; environ[j]; j++)
		add_node_end(&node, environ[j], 0);
	info->env = node;
	return (0);
}

