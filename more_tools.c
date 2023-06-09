#include "shell.h"

/**
 * _atoi - converts character to int
 * @c: the given character
 *
 * Return: An integer
 */
int _atoi(char *c)
{
	unsigned int val = 0;
	int sign = 1;

	if (c == NULL)
		return (0);
	while (*c)
	{
		if (*c == '-')
			sign *= (-1);
		else
			val = (val * 10) + (*c - '0');
		c++;
	}
	return (sign * val);
}

/**
 * _itoa - convert integer to array
 * @num: the given number
 *
 * Return: a pointer to the null terminated string
 */
char *_itoa(unsigned int num)
{
	int len = 0, i = 0;
	char *s;

	len = num_digits(num);
	s = malloc(len + 1);
	if (!s)
		return (NULL);
	*s = '\0';
	while (num / 10)
	{
		s[i] = (num % 10) + '0';
		num /= 10;
		i++;
	}
	s[i] = (num % 10) + '0';
	array_rev(s, len);
	s[i + 1] = '\0';
	return (s);
}


/**
 * num_digits - Determine the number of digit int integer
 * @num: the given number
 *
 * Return: the length of the integer
 */
int num_digits(int num)
{
	int len = 0;

	while (num != 0)
	{
		len++;
		num /= 10;
	}
	return (len);
}
/**
 * print_error - prints error
 * @data: the data structure pointer
 *
 * Return: Succes code
 */
int print_error(shell_info *data)
{
	char *idx = _itoa(data->index);

	LOG("hsh: ");
	LOG(idx);
	LOG(": ");
	LOG(data->args[0]);
	LOG(": ");
	LOG(data->error_message);
	free(idx);
	return (0);
}

/**
 * write_history - prints error
 * @data: the data structure pointer
 *
 * Return: Succes code
 */
int write_history(shell_info *data __attribute__((unused)))
{
	char *filename = "history";
	char *line_of_history = "this is a line of history";
	ssize_t fd, w;
	int len;

	if (!filename)
		return (-1);
	fd = open(filename, O_RDWR | O_APPEND);
	if (fd < 0)
		return (-1);
	if (line_of_history)
	{
		while (line_of_history[len])
			len++;
		w = write(fd, line_of_history, len);
		if (w < 0)
			return (-1);
	}
	return (1);
}
