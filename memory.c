#include "shell.h"

/**
 * bfree - This function frees a pointer & nul the add
 * @ptr: Refers to addr of the ptr to free
 * Completed 
 * Return: 1 if freeded; otherwise, 0.
 */

int bfree(void **ptr)
{
	if (ptr && *ptr) /*  */
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
