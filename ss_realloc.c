#include "shell.h"

/**
 **_memset - This function fills memory with a const byte
 *@s: Refers to the pt to the memory area
 *@b: Refers to the byte to fill with
 *@n: Refers to the amt of bytes to be filled.
 *Completed
 *Return: a pointer to the memory
 */

char *_memset(char *s, char b, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
		s[j] = b;
	return (s);
}

/**
 * ffree - This function frees a str of strs
 * @pp: Refers to string of str.
 *
 */

void ffree(char **pp)
{
	char **a = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(a);
}

/**
 * _realloc - This function reallocates a block of memory
 * @ptr: Refers to the ptr to previous  block
 * @old_size: byte size of previous block.
 * @new_size: byte size of new block.
 *
 * Return: pointer to da ol'block nameen.
 */

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr) /*  */
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}
