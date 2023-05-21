#include "shell.h"

/**
 * bfree - This function frees a pointer and NULLs the address
 * @ptr: Refers to address of the pointer to free
 * Completed by Loveline-Ezenwafor
 *
 * Return: 1 if freed; otherwise, 0.
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
