#include "shell.h"

/**
 * **strtow - This function splits a string into words.
 *               Repeat delimiters are ignored
 * @str: Refers to the input string.
 * @d:   Refers to the delimeter string.
 * Completed by Loveline-Ezenwafor on 21st May 2023.
 *
 * Return: a pointer to an array of strings,
 *         NULL, on failure
 */

char **strtow(char *str, char *d)
{
	int x, y, z, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (x = 0; str[x] != '\0'; x++)
		if (!is_delim(str[x], d) && (is_delim(str[x + 1], d) || !str[x + 1]))
			num_words++;

	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++)
	{
		while (is_delim(str[x], d))
			x++;
		z = 0;
		while (!is_delim(str[x + z], d) && str[x + z])
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			s[y][m] = str[x++];
		s[y][m] = 0;
	}
	s[y] = NULL;
	return (s);
}


/**
 * **strtow2 - This function splits a string into words.
 * @str: Refers to the input string;
 * @d: Refers to the delimeter;
 *
 * Return: a pointer to an array of strings,
 *         NULL, on failure
 */

char **strtow2(char *str, char d)
{
	int x, y, z, m, num_words = 0;
	char **s;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (x = 0; str[x] != '\0'; x++)
		if ((str[x] != d && str[x + 1] == d) ||
		    (str[x] != d && !str[x + 1]) || str[x + 1] == d)
			num_words++;
	if (num_words == 0)
		return (NULL);
	s = malloc((1 + num_words) * sizeof(char *));
	if (!s)
		return (NULL);
	for (x = 0, y = 0; y < num_words; y++) /*    */
	{
		while (str[x] == d && str[x] != d)
			x++;
		z = 0;
		while (str[x + z] != d && str[x + z] && str[x + z] != d)
			z++;
		s[y] = malloc((z + 1) * sizeof(char));
		if (!s[y])
		{
			for (z = 0; z < y; z++)
				free(s[z]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < z; m++)
			s[y][m] = str[x++];
		s[y][m] = 0;
	}
	s[y] = NULL;
	return (s);
}

