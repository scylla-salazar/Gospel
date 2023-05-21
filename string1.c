#include "shell.h"

/**
 * _strcpy - This function copies a string.
 * @dest: Refers to the destination.
 * @src: Refers to the source.
 * Completed by Loveline-Ezenwafor on 21st May 2023.
 *
 * Return: pointer to destination
 */

char *_strcpy(char *dest, char *src)
{
	int u = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[u])
	{
		dest[u] = src[u];
		u++;
	}
	dest[u] = 0;
	return (dest);
}


/**
 * _strdup - This function duplicates a string.
 * @str: Refers to the string to duplicate
 *
 * Return: pointer to the duplicated str.
 */

char *_strdup(const char *str)
{
	int lent = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lent++;
	ret = malloc(sizeof(char) * (lent + 1));
	if (!ret)
		return (NULL);
	for (lent++; lent--;)
		ret[lent] = *--str;
	return (ret);
}


/**
 *_puts - This function prints an input str;
 *@str: Refers to the string to be printed
 *
 * Return: Nothing
 */
void _puts(char *str)
{
	int c = 0;

	if (!str)
		return;
	while (str[c] != '\0') /* Prints  each element of the str */
	{
		_putchar(str[c]);
		c++;
	}
}

/**
 * _putchar - Thid function writes the character c to stdout;
 * @c: Refers to the character to print.
 *
 * Return: 1, On success.
 *        -1, On error, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int e;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || e >= WRITE_BUF_SIZE)
	{
		write(1, buf, e);
		e = 0;
	}
	if (c != BUF_FLUSH)
		buf[e++] = c;
	return (1);
}

