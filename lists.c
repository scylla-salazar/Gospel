#include "shell.h"

/**
 * add_node - A funtion that adds a node to the start of the list
 * @head: Refers to add of pointer to head node
 * @str: Refers to str field of node
 * @num: Refers to node index used by history
 * Completed
 * Return: size of list.
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new_Head;

	if (!head)
		return (NULL);
	new_Head = malloc(sizeof(list_t));
	if (!new_Head)
		return (NULL);
	_memset((void *)new_Head, 0, sizeof(list_t));
	new_Head->num = num;
	if (str)
	{
		new_Head->str = _strdup(str);
		if (!new_Head->str)
		{
			free(new_Head);
			return (NULL);
		}
	}
	new_Head->next = *head;
	*head = new_Head;
	return (new_Head);
}

/**
 * add_node_end - A funtion that adds a node to the end of the list
 * @head: Refers to address of pointer to head node
 * @str: Refers to str field of node
 * @num: Refers to node index used by history
 *
 * Return: size of list.
 */

list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *new_Node, *node;

	if (!head)
		return (NULL);

	node = *head;
	new_Node = malloc(sizeof(list_t));
	if (!new_Node)
		return (NULL);
	_memset((void *)new_Node, 0, sizeof(list_t));
	new_Node->num = num;
	if (str)
	{
		new_Node->str = _strdup(str);
		if (!new_Node->str)
		{
			free(new_Node);
			return (NULL);
		}
	}
	if (node) /*  */
	{
		while (node->next)
			node = node->next;
		node->next = new_Node;
	}
	else
		*head = new_Node;
	return (new_Node);
}

/**
 * print_list_str - This funtion prints only the str element of a list_t
 *                    linked list
 * @h: Refers to pointer to first node
 *
 *
 * Return: size of list
 */

size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - This function deletes node at given index
 * @head: Refers to address of pointer to first node
 * @index: Refers to index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */

int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int j = 0;

	if (!head || !*head)
		return (0);

	if (!index) /*   */
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (j == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		j++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - This function frees all nodes of a list
 * @head_ptr: Refers to address of pointer to head node
 *
 * Return: void
 */

void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr) /*  */
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
