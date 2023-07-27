#include "shell.h"

/**
 * _erratoi - s function converts a str to an int
 * @s: Refers to the string to be converted
 * Completed by scylla-salazar .
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */

int _erratoi(char *s)
{
	int j = 0;
	unsigned long int rezult = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (j = 0;  s[j] != '\0'; j++)
	{
		if (s[j] >= '0' && s[j] <= '9')
		{
			rezult *= 10;
			rezult += (s[j] - '0');
			if (rezult > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (rezult);
}

/**
 * print_error - This function prints an error message
 * @info: Refers to the parameter & return info struct
 * @estr: Refers to the string containing specified error type
 *
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1, on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - This function prints a decimal (integer) number (base 10)
 * @input: Refers to the input
 * @fd: Refers to the filedescriptor to write to
 *
 * Return: no of characters printed
 */

int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, counts = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		counts++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + current / j);
			counts++;
		}
		current %= j;
	}
	__putchar('0' + current);
	counts++;

	return (counts);
}

/**
 * convert_number - This funtion converter function, a clone of itoa
 * @num: Refers to the number
 * @base: Refers to the base
 * @flags: argument flags.
 *
 * Return: string.
 */

char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long m = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		m = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[m % base];
		m /= base;
	} while (m != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_comments - This function replaces first instance of '#' with '\0'
 * @buf: Refers to thaddress of the string to modify
 *
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int j;

	for (j = 0; buf[j] != '\0'; j++)
		if (buf[j] == '#' && (!j || buf[j - 1] == ' '))
		{
			buf[j] = '\0';
			break;
		}
}

