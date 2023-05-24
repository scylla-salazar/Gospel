#include "shell.h"
#include <stdio.h>

/**
 * main - The function indicates the entry point
 * @ac: Refers to arg count
 * @av: Refers to arg vector
 * Updated by scylla-salazar on 24th May 2023.
 *
 * Return: 0 on success; 1, if error
 */


int main(int ac, char **av)
{
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
			"add $3, %0"
			: "=r" (fd)
			: "r" (fd));

	if (ac == 2) /*  */
	{
		fd = open(av[1], O_RDONLY);
		if (fd == -1)  /*  */
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info[0].readfd = fd; /*  */ Changed info->readfd to info[0].readfd
	}
	populate_env_list(info);
	read_history(info);
	hsh(info, av);
	return (EXIT_SUCCESS);
}
