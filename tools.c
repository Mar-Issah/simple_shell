#include "shell.h"

/**
 * signal_handler - handle the process interrept signal
 * @signo: the signal identifier
 *
 * Return: void
 */
void signal_handler(int sig)
{
	if (sig == SIGINT)
	{
		PRINT("\n");
		PRINT(PROMPT);
	}
}
/**
 * _getenv - gets the path
 * @path_name: a pointer to the struct of data
 *
 * Return: Succes code
 */
char *_getenv(char *path_name)
{
	char **environ_cursor, *env_ptr, *name_ptr;
	environ_cursor = environ;

	while (*environ_cursor)
	{
		env_ptr = *environ_cursor;
		name_ptr = path_name;
		while (*env_ptr == *name_ptr)
		{
			if (*env_ptr == '=')
				break;
			env_ptr++;
			name_ptr++;
		}
		if ((*env_ptr == '=') && (*name_ptr == '\0'))
			return (env_ptr + 1);
		environ_cursor++;
	}
	return (NULL);
}

/**
 * populate_array - fill an array with elements
 * @array: the given array
 * @el: the given element
 * @len: the length of the array
 *
 * Return: pointer to filled array
 */
void *populate_array(void *array, int el, unsigned int len)
{
	char *p = array;
	unsigned int i = 0;

	while (i < len)
	{
		*p = el;
		p++;
		i++;
	}
	return (array);
}

/**
 * array_rev - reverse array
 * @arr: the given array
 * @len: the array length
 *
 * Return: void
 */
void array_rev(char *arr, int len)
{
	char tmp;
	int count;

	for (count = 0; count < (len / 2); count++)
	{
		tmp = arr[count];
		arr[count] = arr[(len - 1) - count];
		arr[(len - 1) - count] = tmp;
	}
}
/**
 * index_command - indexed command
 * @data: a pointer to the data structure
 *
 * Return: void
 */
void index_command(shell_info *data)
{
	data->index += 1;
}
