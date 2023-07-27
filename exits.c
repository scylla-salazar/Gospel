#include "shell.h"

/**
 **_strncpy - This funct copies a str
 *@n: Referss to the amt of chars to be copied
 *@dest: Refers to the dest str to be copied to
 *@src: Refers to the source str
 *
 *Return: the concated str
 */

char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (s);
}

/**
 **_strncat - This funct concats 2 strs
 *@dest: Referrs to the 1st str.
 *@src: Refers to the 2nd str.
 *@n: Referrs to the amt of bytes to be maximally used
 *
 *Return: the concat str.
 */

char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *s = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (s);
}

/**
 **_strchr - This funct locates a char in a str
 *@s: Referss to the str to be parsed
 *@c: Refers to the character to look for.
 *
 *Return: a ptr to the memory area s.
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

