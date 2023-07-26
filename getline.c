#include "shell.h"

/**
 * input_buf - The buffer for chained commands.
 *
 * @info: Parameter struct.
 * @buf: Address of buffer.
 * @len: Address of len variable.
 *
 * Return: Bytes read.
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t l = 0;
	size_t len_b = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);

		l = _getline(info, buf, &len_b);

		if (l > 0)
		{
			if ((*buf)[l - 1] == '\n')
			{
				(*buf)[l - 1] = '\0';
				l--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = l;
				info->cmd_buf = buf;
			}
		}
	}
	return (l);
}

/**
 * get_input - Gets a line minus the newline.
 *
 * @info: Parameter struct.
 *
 * Return: Bytes read.
 */
ssize_t get_input(info_t *info)
{
	static char *buf;
	static size_t i, j, len;
	ssize_t l = 0;
	char **buf_b = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	l = input_buf(info, &buf, &len);
	if (l == -1)
		return (-1);
	if (len)
	{
		j = i;
		p = buf + i;

		check_chain(info, buf, &j, i, len);
		while (j < len)
		{
			if (is_chain(info, buf, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_b = p;
		return (_strlen(p));
	}

	*buf_b = buf;
	return (l);
}

/**
 * read_buf - Reads a buffer.
 *
 * @info: Parameter struct.
 * @buf: Buffer.
 * @i: Size.
 *
 * Return: l.
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t l = 0;

	if (*i)
		return (0);
	l = read(info->readfd, buf, READ_BUF_SIZE);
	if (l >= 0)
		*i = l;
	return (l);
}

/**
 * _getline - Gets the next line of input from STDIN.
 *
 * @info: Parameter struct.
 * @ptr: Address of pointer to buffer, preallocated or NULL.
 * @length: Size of preallocated ptr buffer if not NULL.
 *
 * Return: s.
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t l = 0, s = 0;
	char *p = NULL, *new_b = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	l = read_buf(info, buf, &len);
	if (l == -1 || (l == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_b = _realloc(p, s, s ? s + k : k + 1);
	if (!new_b)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_b, buf + i, k - i);
	else
		_strncpy(new_b, buf + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_b;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigintHandler - Blocks ctrl-C.
 *
 * @sig_num: The signal number.
 *
 * Return: Void.
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
