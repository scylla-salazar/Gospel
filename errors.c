#include "shell.h"

/**
 *_eputs -  This function prints an input string
 * @str: Refers to the string to be printed
 * Completed by scylla-salazar on 20th May 2023.
 *
 * Return: Nothing
 */

void _eputs(char *str)
{
	int j = 0;

	if (!str)
		return;
	while (str[j] != '\0')
	{
		_eputchar(str[j]);
		j++;
	}
}

/**
 * _eputchar - This function writes the character c to stderr
 * @c: Refers to The character to print
 *
 * Return: 1 On success.
 *        -1 if error, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int j;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || j >= WRITE_BUF_SIZE)
	{
		write(2, buf, j);
		j = 0;
	}
	if (c != BUF_FLUSH)
		buf[j++] = c;
	return (1);
}

/**
 * _putfd - This function writes the character c to given fd
 * @c: Refers to The character to print
 * @fd: Refers to The filedescriptor to write to
 *
 * Return: 1, On success.
 *        -1,On error,  and errno is set appropriately.
 */

int _putfd(char c, int fd)
{
	static int k;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || k >= WRITE_BUF_SIZE)
	{
		write(fd, buf, k);
		k = 0;
	}
	if (c != BUF_FLUSH)
		buf[k++] = c;
	return (1);
}

/**
 *_putsfd - This function prints an input string
 * @st: Refers to the string to be printed
 * @fd: Refers to the the filedescriptor to write to
 *
 * Return: the number of characters put
 */
int _putsfd(char *st, int fd)
{
	int a = 0;

	if (!st)
		return (0);
	while (*st)
	{
		a += _putfd(*st++, fd);
	}
	return (a);
}

