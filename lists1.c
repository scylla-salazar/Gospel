#include "shell.h"

/**
 * list_len - This function determines length of linked list
 * @h: Refers to pointer to first node
 * Completed
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - This function returns an array of strings of the list->str
 * @head: Refers to the pointer to first node
 *
 * Return: array of strings.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !a)
		return (NULL);
	strs = malloc(sizeof(char *) * (a + 1));
	if (!strs)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < a; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[a] = str;
	}
	strs[a] = NULL;
	return (strs);
}


/**
 * print_list - This function prints all elements of a list_t linked list
 * @h: Refers to the pointer to first node
 *
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t j = 0;

	while (h) /*  */
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		j++;
	}
	return (j);
}

/**
 * node_starts_with - The function returns node whose string starts with prefix
 * @node: Refers to the pointer to list head
 * @prefix: Refers to the string to match
 * @c: the next character after prefix to match
 *
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *p = NULL;

	while (node) /*   */
	{
		p = starts_with(node->str, prefix);
		if (p && ((c == -1) || (*p == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - This function gets the index of a node
 * @head: Refers to the pointer to list head
 * @node: Refers to the pointer to the node
 *
 * Return: index of node or -1
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
