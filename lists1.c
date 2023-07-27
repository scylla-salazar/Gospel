#include "shell.h"

/**
 * list_len - This func determines length of linked list
 * @h: Refers to ptr to 1st node
 * Completed
 *
 * Return: size of list
 */
size_t list_len(const list_t *h)
{
	size_t v = 0;

	while (h)
	{
		h = h->next;
		v++;
	}
	return (v);
}



/**
 * list_to_strings - Th1s funct returns an array of strs
 * @head: Referrs to d ptr to 1st node
 *
 * Return: array of strs.
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t l = list_len(head), b;
	char **strs;
	char *str;

	if (!head || !l)
		return (NULL);
	strs = malloc(sizeof(char *) * (l + 1));
	if (!strs)
		return (NULL);
	for (l = 0; node; node = node->next, l++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (b = 0; b < l; b++)
				free(strs[b]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[l] = str;
	}
	strs[l] = NULL;
	return (strs);
}


/**
 * print_list - This funct prints all elemnts of a list_t linked list
 * @h: Referrs to the ptr to 1st node
 *
 * Return: size of list
 */

size_t print_list(const list_t *h)
{
	size_t q = 0;

	while (h) /* iterates thru the nodes to print the elements */
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		q++;
	}
	return (q);
}

/**
 * node_starts_with - Th funct retrns node whose str starts with prefix
 * @node: Referrs to d ptr to list head
 *
 * @c: the next char after prefix to match
 * @prefix: Refers to the str to match
 * Return: match node or null
 */

list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *o = NULL;

	while (node) /* chcks 4 conditions  */
	{
		o = starts_with(node->str, prefix);
		if (o && ((c == -1) || (*o == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 * get_node_index - This funct gets the indx of a node
 *
 * @node: Referrs to the ptr to the node
 * @head: Referss to the ptr to list head
 * Return: indx of node t or -1, if otherwise
 */

ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t t = 0;

	while (head)
	{
		if (head == node)
			return (t);
		head = head->next;
		t++;
	}
	return (-1);
}
