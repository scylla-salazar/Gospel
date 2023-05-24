#include "shell.h"

/**
 **_strncpy - This function copies a string
 *@dest: Refers to the destination string to be copied to
 *@src: Refers to the source string
 *@n: Refers to the amount of characters to be copied
 *Completed by scylla-salazar on 20th May 2023.
 *
 *Return: the concatenated string
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
 **_strncat - This function concatenates two strings
 *@dest: Refers to the first string
 *@src: Refers to the second string
 *@n: Refers to the amount of bytes to be maximally used
 *
 *Return: the concatenated string.
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
 **_strchr - This function locates a character in a string
 *@s: Refers to the string to be parsed
 *@c: Refers to the character to look for.
 *
 *Return: (s) a pointer to the memory area s.
 */

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}

