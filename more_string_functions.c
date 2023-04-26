#include "shell.h"

/**
 * _isalphabet - check if the input is a letter
 * @c: the character to be checked
 *
 * Return: 1 if letter, 0 otherwise
 */
int _isalphabet(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
	{
		return (SUCCESS_CODE);
	}
	return (FAIL_CODE);
}
/**
 * _strcpy - copy a string from source to destination
 * @source: the string source
 * @destination: the string destination
 *
 * Return: the pointer to dest
 */
char *_strcpy(char *destination, char *source)
{
	int i;

	for (i = 0; source[i] != '\0'; i++)
	{
		destination[i] = source[i];
	}
	destination[i] = '\0';
	return (destination);
}

/**
 * _strchr - locates a character in a given string
 * @str: the given string
 * @character: the given string
 *
 * Return: Succes code
 */
char *_strchr(char *str, char character)
{
	char *ptr;

	if (str == NULL)
		return (NULL);
	for (ptr = str; *ptr; ptr++)
		if (*ptr == character)
			return (ptr);
	return (NULL);
}

