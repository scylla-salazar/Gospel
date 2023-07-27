#include "shell.h"

/**
 *_eputs -  This funct prints an input str
 * @str: Referss to the str to be printed
 * Completed by scylla-salazar o.
 *
 * Return: Nothng
 */

void _eputs(char *str)
{
	int z = 0;

	if (!str)
		return;
	while (str[z] != '\0')
	{
		_eputchar(str[z]);
		z++;
	}
}

/**
 * _eputchar - This funct writes the char to stderr
 * @c: Refers to The char to print
 *
 * Return: 1 On succes.
 * -1 if error, and errno is set appropriately.
 */

int _eputchar(char c)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(2, buf, x);
		x = 0;
	}
	if (c != BUF_FLUSH)
		buf[x++] = c;
	return (1);
}

/**
 * _putfd - This funct writes the char to given fd
 * @fd: Referrs to The filedescriptor to write to
 * @c: Refers to The character to print
 * 
 *
 * Return: 1, On succes.
 * -1,On error,  and errno is set appropriately.
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
 *_putsfd - This funct prints an input str
 * 
 * @fd: Referss to the the filedescriptor to write to
 * @st: Refers to the str to be printed
 * Return: the num of chars put
 */
int _putsfd(char *st, int fd)
{
	int v = 0;

	if (!st)
		return (0);
	while (*st)
	{
		v += _putfd(*st++, fd);
	}
	return (v);
}

