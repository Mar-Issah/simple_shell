#include "shell.h"

/**
 * _realloc - reallocates memory block
 * @ptr: pointer to the previous memory
 * @old_size: the old size
 * @updated_size: the new size
 *
 * Return: a pointer to the newly allocated memory
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int updated_size)
{
	void *result;

	if (updated_size == old_size)
		return (ptr);
	if (updated_size == 0 && ptr)
	{
		free(ptr);
		return (NULL);
	}
	result = malloc(updated_size);
	if (result == NULL)
		return (NULL);
	if (ptr == NULL)
	{
		fill_an_array(result, '\0', updated_size);
		free(ptr);
	}
	else
	{
		_memcpy(result, ptr, old_size);
		free(ptr);
	}
	return (result);
}
/**
 * _memset - fills a memory with constant byte
 * @s: pointer to memory area
 * @n: first n bytes
 * @byt: constant byte
 *
 * Return: A pointer to a character
 */
char *_memset(char *s, char byt, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
	{
		s[i] = byt;
	}
	return (s);
}
/**
 * free_space - frees data
 * @data: the data structure
 *
 * Return: Succes code
 */
int free_space(shell_info *data)
{
	free(data->args);
	data->args = NULL;
	free(data->line);
	data->line = NULL;
	free(data->command);
	data->command = NULL;
	free(data->error_message);
	data->error_message = NULL;
	return (0);
}
/**
 * _memcpy - cpies memory area
 * @destination: Destination
 * @src: Source memory
 * @n: Amount of memory
 *
 * Return: A pointer to dest
 */
char *_memcpy(char *destination, char *src, unsigned int n)
{
	unsigned int j;

	for (j = 0; j < n; j++)
	{
		destination[j] = src[j];
	}
	return (destination);
}
