#include "shell.h"

/**
 * _strlen - This function returns the length of a str
 * @s: Refers to str whose length to check
 * Completed
 * Return: int length of str
 */

int _strlen(char *s)
{
	int a = 0;

	if (!s)
		return (0);

	while (*s++)
		a++;
	return (a);
}

/**
 * _strcmp - This function performs lexico comparison of two str.
 * @s1: Refers to the 1st str
 * @s2: Refers to the 2nd str
 *
 * Return: negative if s1 < s2, positive if s1 > s2,& zero if s1 == s2
 */

int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2) /*  */
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with -This function checks if needle starts with haystack
 * @haystack: Refers to th3 str to search
 * @needle: Refers to the substr to find.
 * Return: addr of next char of haystack or NULL
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two str
 * @dest: the destination buf
 * @src: the source buf
 * Return: ptr to dest buf
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest) /*  */
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
