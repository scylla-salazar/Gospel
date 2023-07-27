#include "shell.h"

/**
 * get_history_file - This function gets the history file
 * @info: Refers to the parameter struct
 * Completed by scylla-salaz
 * Return: allocated string containg history file, buf.
 */

char *get_history_file(info_t *info)
{
	char *buf, *direc;

	direc = _getenv(info, "HOME=");
	if (!direc)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(direc) + _strlen(HIST_FILE) + 2));
	if (!buf) /* */
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, direc);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}

/**
 * write_history - This function creates a file, or appends to an existing file
 * @info: Refers to the parameter struct
 *
 * Return: 1 on success,
 *        -1 if otherwise
 */

int write_history(info_t *info)
{
	ssize_t fd;
	char *filename = get_history_file(info);
	list_t *node = NULL;

	if (!filename) /* checks for filename*/
		return (-1);

	fd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (fd == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - This function reads history from file
 * @info: Refers to the parameter struct.
 *
 * Return: histcount on success, 0 if otherwise
 */
int read_history(info_t *info)
{
	int a, last = 0, linecount = 0;
	ssize_t fd1, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(info);

	if (!filename) /* checks for filename */
		return (0);

	fd1 = open(filename, O_RDONLY);
	free(filename);
	if (fd1 == -1)
		return (0);
	if (!fstat(fd1, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(fd1, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(fd1);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + last, linecount++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - This function adds entry to a history linked list
 * @info: Refers to the Structure containing potential arguments.
 *          This is Used to maintain
 * @buf: Refers to the buffer
 * @linecount: Refers to the history linecount, histcount
 *
 * Return: Always 0
 */

int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history) /*  */
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbers the history linked list after changes
 * @info: Refers to the Structure containing potential arguments.
 *           This is Used to maintain
 *
 * Return: the new histcount
 */

int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}

