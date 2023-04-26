#include "shell.h"
/**
 * is_path_string - chekc if the given fikenname is a path
 * @data: the data strucct pointer
 *
 * Return: Succes code
 */
int is_path_string(shell_info *data)
{
	if (_strchr(data->args[0], '/') != 0)
	{
		data->command = _strdup(data->args[0]);
		return (SUCCESS_CODE);
	}
	return (FAIL_CODE);
}
#define DELIMITER ":"
/**
 * is_abbreviated - chekc if the given fikenname is short form
 * @data: the data strucct pointer
 *
 * Return: Succes code
 */
void is_abbreviated(shell_info *data)
{
	char *path, *token, *_path;
	struct stat st;
	int exist_flag = 0;

	path = _getenv("PATH");
	_path = _strdup(path);
	token = strtok(_path, DELIMITER);
	while (token)
	{
		data->command = _strcat(token, data->args[0]);
		if (stat(data->command, &st) == 0)
		{
			exist_flag += 1;
			break;
		}
		free(data->command);
		token = strtok(NULL, DELIMITER);
	}
	if (exist_flag == 0)
	{
		data->command = _strdup(data->args[0]);
	}
	free(_path);
}
#undef DELIMITER
/**
 * is_builtin - checks if the command is builtin
 * @data: a pointer to the data structure
 *
 * Return: Succes code
 */
int is_builtin(shell_info *data)
{
	built_in blt[] = {
		{"exit", abort_program},
		{"cd", change_directory},
		{NULL, NULL}
	};
	int count = 0;

	while ((blt + count)->command)
	{
		if (_strcmp(data->args[0], (blt + i)->command) == 0)
			return (SUCCESS_CODE);
		count++;
	}
	return (NEUTRAL_CODE);
}
