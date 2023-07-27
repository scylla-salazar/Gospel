#include "shell.h"

/**
 * interactive - This program returns true if shell is interac mode
 * @info: Refers to struct addr
 * Return: 1 if interactive mode, 0 if otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This funtion checks if char is a delim
 * @chr: the character to check
 * @delim: the delimeter string
 *
 * Return: 1 if true, 0 (if false)
 */
int is_delim(char chr, char *delim)
{
	while (*delim)
		if (*delim++ == chr)
			return (1);
	return (0);
}

/**
 *_isalpha - This funtion checks for alpha char
 *@chr: ThisRefers to the char to input
 *Return: 1 if chr is alphabetic, 0 (if otherwise)
 */

int _isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}


/**
 *_atoi - This function converts a str to an int
 *@st: This Refers to the str to be converted
 *Return: 0 ( no numbers in string), or converted number otherwise
 */

int _atoi(char *st)
{
	int i, sign = 1, flags = 0, out_put;
	unsigned int res_lt = 0;

	for (i = 0;  st[i] != '\0' && flags != 2; i++)
	{
		if (st[i] == '-')
			sign *= -1;

		if (st[i] >= '0' && st[i] <= '9')
		{
			flags = 1;
			res_lt *= 10;
			res_lt += (st[i] - '0');
		}
		else if (flags == 1)
			flags = 2;
	}

	if (sign == -1)
		out_put = -res_lt;
	else
		out_put = res_lt;

	return (out_put);
}

