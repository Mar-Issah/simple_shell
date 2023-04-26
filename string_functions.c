#include "shell.h"

/**
 * _strlen - finds the length of a string
 * @str: the given string
 *
 * Return: Succes code
 */
int _strlen(char *str)
{
	int len;

	for (len = 0; str[len]; len++)
		;
	return (len);
}
/**
 * _strcat - concatenates two string
 * @first: the first given destination
 * @second: the second given source
 *
 * Return: Succes code
 */
char *_strcat(char *first, char *second)
{
	int len1, len2, i = 0, j = 0;
	char *result;

	len1 = _strlen(first);
	len2 = _strlen(second);
	result = malloc((len1 + len2 + 2) * sizeof(char));
	if (!result)
		return (NULL);
	*result = '\0';
	while (first[j])
		result[i++] = first[j++];
	result[i++] = '/';
	j = 0;
	while (second[j])
		result[i++] = second[j++];
	result[i] = '\0';
	return (result);
}

/**
 * _strcmp - compare two strings
 * @s1: the first given string
 * @s2: the second given string
 *
 * Return: Succes code
 */
int _strcmp(char *s1, char *s2)
{
	int cmp = 0, j;

	if (s1 == NULL || s2 == NULL)
		return (1);
	for (j = 0; s1[j]; j++)
	{
		if (s1[j] != s2[j])
		{
			cmp = s1[j] - s2[j];
			break;
		}
		else
			continue;
	}
	return (cmp);
}

/**
 * _strdup - dupicates string
 * @str: the given string
 *
 * Return: Succes code
 */
char *_strdup(char *str)
{
	char *dupl;

	if (str == NULL)
		return (NULL);
	dupl = malloc(_strlen(str) + 1);
	if (dupl == NULL)
		return (NULL);
	_strcpy(dupl, str);
	return (dupl);
}
