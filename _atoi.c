#include "shell.h"

/**
 * interactive - This program returns true if shell is interactive mode
 * @info: Refers to struct address
 * By Scylla-Salazar - 20th May 2023
 *
 * Return: 1 if interactive mode, 0 if otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - This function checks if character is a delimeter
 * @ch: the character to check
 * @delim: the delimeter string
 *
 * Return: 1 if true, 0 if false
 */
int is_delim(char ch, char *delim)
{
	while (*delim)
		if (*delim++ == ch)
			return (1);
	return (0);
}

/**
 *_isalpha - This function checks for alphabetic character
 *@chr: Refers to the character to input
 *
 *Return: 1 if chr is alphabetic, 0 if otherwise
 */

int _isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - This function converts a string to an integer
 *@st: Refers to the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *st)
{
	int i, sign = 1, flag = 0, output;
	unsigned int resuult = 0;

	for (i = 0;  st[i] != '\0' && flag != 2; i++)
	{
		if (st[i] == '-')
			sign *= -1;

		if (st[i] >= '0' && st[i] <= '9')
		{
			flag = 1;
			resuult *= 10;
			resuult += (st[i] - '0');
		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -resuult;
	else
		output = resuult;

	return (output);
}

