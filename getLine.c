#include "shell.h"

/**
 * input_buf - This funct buffers chained cmds
 * @len: Refers to the addr of len var
 * @info: Referrs to the parametre struct
 * @buf: Refers to the addr of buf
 * 
 * Completed
 *
 * Return: bytes read.
 */

ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t x = 0;
	size_t len_p = 0;

	if (!*len)
	{
		/* free buf */
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
				(*buf)[x - 1] = '\0';
				x--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* 1s it a chain cmd */
			{
				*len = x;
				info->cmd_buf = buf;
			}
		}
	}
	return (x);
}

/**
 * get_input - This funct gets a line minus the newline
 * @info: Refers to the parametre struct
 *
 *  Return: bytes read.
 */

ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' cmd chain buff */
	static size_t x, y, len;
	ssize_t a = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	a = input_buf(info, &buf, &len);
	if (a == -1) /* EOF */
		return (-1);
	if (len)
	{
		y = x;
		p = buf + x;

		check_chain(info, buf, &y, x, len);
		while (y < len)
		{
			if (is_chain(info, buf, &y))
				break;
			y++;
		}

		x = y + 1;
		if (x >= len)
		{
			x = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /*pasing bck ptr to cur_ent cmd posit */
		return (_strlen(p)); /* return length of cur_ent cmd */
	}

	*buf_p = buf; /*pas back buf frm _getli */
	return (a);
}

/**
 * read_buf - This funct reads a buf
 * @i: Refers to the size
 * @info: Refrers to the parametr struct
 * @buf: Refers to the buff
 *
 *
 * Return: no of chars
 */

ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t t = 0;

	if (*i)
		return (0);
	t = read(info->readfd, buf, READ_BUF_SIZE);
	if (t >= 0)
		*i = t;
	return (t);
}

/**
 * _getline - This func gets nxt line of input frm standard STDIN
 *
 * @ptr: Refers to addr of ptr to buff, preallocated / NULL
 * @length: Referrs to the size of prealloc ptr buf if not NULL
 * @info: REfers to the parametr struct
 * Return: size
 */

int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t q;
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
	new_p = _realloc(p, s, s ? s + q : q + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + a, q - a);
	else
		_strncpy(new_p, buf + a, q - a + 1);

	s += q - a;
	a = q;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - The funct blocks ctrl-C
 * @sig_num: Referrs to the signal num
 *
 * Return: void.
 */

void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

