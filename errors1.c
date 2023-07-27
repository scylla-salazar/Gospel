#include "shell.h"

/**
 * _erratoi - a function converts a str to an int
 * @s: Refers to the string to be converted
 * Completed .
 * Return: 0 if no nums in str, converted num, otherwise
 * -1 on error
 */

int _erratoi(char *s)
{
	int e = 0;
	unsigned long int res_lt = 0;

	if (*s == '+')
		s++;  /*  */
	for (e = 0;  s[e] != '\0'; e++)
	{
		if (s[e] >= '0' && s[e] <= '9')
		{
			res_lt *= 10;
			res_lt += (s[e] - '0');
			if (res_lt > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res_lt);
}

/**
 * print_error - This funct prints an err message
 * @info: Referrs to the parametre info struct
 * @estr: Referrs to the str containing specified err type
 *
 * Return: 0 if no nos in str, converted num otherwise
 * -1, on error
 */

void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_dec(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_dec - This funct prints a decimal (int) num (base 10)
 * @input: Referrs to the input
 * @fd: Referrs to the filedescriptor to write to
 *
 * Return: no of chars printed
 */

int print_dec(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int j, co_nts = 0;
	unsigned int _abs_, cur_ent;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		co_nts++;
	}
	else
		_abs_ = input;
	cur_ent = _abs_;
	for (j = 1000000000; j > 1; j /= 10)
	{
		if (_abs_ / j)
		{
			__putchar('0' + cur_ent / j);
			co_nts++;
		}
		cur_ent %= j;
	}
	__putchar('0' + cur_ent);
	co_nts++;

	return (co_nts);
}

/**
 * convert_number - This funtion converter function, a clone of a
 * @num: Refers to the numr
 * @base: Referrs to the base
 * @flags: arg flags.
 *
 * Return: str.
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
 * remove_comments - This function replaces 1st instance of '#' with '\0'
 * @buf: Referrs to thaddr of the str to modify
 *
 * Return: Always 0;
 */

void remove_comments(char *buf)
{
	int t;

	for (t = 0; buf[t] != '\0'; t++) /* Checks the chars */
		if (buf[t] == '#' && (!t || buf[t - 1] == ' '))
		{
			buf[t] = '\0';
			break;
		}
}

