#include "shell.h"

/**
 * input_buf - This function buffers chained commands
 * @info: Refers to the parameter struct
 * @buf: Refers to the address of buffer
 * @len: Refers to the address of len var
 * Completed by scylla-salazar on 20th May 2023.
 *
 * Return: bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len) /*  if nothing left in the buffer, then fill it */
	{
		/*  bfree((void **)info->cmd_buf);; */
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		x = getline(buf, &len_p, stdin);
#else
		x = _getline(info, buf, &len_p);
#endif
		if (x > 0)
		{
			if ((*buf)[x - 1] == '\n')
			{
				(*buf)[x - 1] = '\0'; /*  remove trailing newline, */
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) - is this a cmd chain? */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - This function gets a line minus the newline
 * @info: Refers to the parameter struct
 *
 *  Return: bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' cmd chain buffer  */
	static size_t x, y, len;
	ssize_t a = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &len);
	if (a == -1) /* EOF */
		return (-1);
	if (len)	/* we have cmds left in the chain buffer */
	{
		y = x; /* initialize new iterator to current buf position */
		p = buf + x; /* getting pointer for return */

		check_chain(info, buf, &y, x, len);
		while (y < len) /* iterate to the semicolon or end. */
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1; /*  increment past nulled ';'' */
		if (x >= len) /* reached end of buffer?  */
		{
			x = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (_strlen(p)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _getline() */
	return (a); /* return length of buffer from _getline() */
}

/**
 * read_buf - This function reads a buffer
 * @info: Refers to the parameter struct
 * @buf: Refers to the buffer
 * @i: Refers to the size
 *
 * Return: a
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t a = 0;

	if (*i)
		return (0);
	a = read(info->readfd, buf, READ_BUF_SIZE);
	if (a >= 0)
		*i = a;
	return (a);
}

/**
 * _getline - This function gets the next line of input from STDIN
 * @info: REfers to the parameter struct
 * @ptr: Refers to address of pointer to buffer, preallocated or NULL
 * @length: Refers to the size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t b;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (a == len)
		a = len = 0;

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + a, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + b : b + 1);
	if (!new_p) /* MALLOC FAILURE!; */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, b - a);
	else
		_strncpy(new_p, buf + a, b - a + 1);

	s += b - a;
	a = b;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - The function blocks ctrl-C
 * @sig_num: Refers to the signal number
 *
 * Return: void.
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

