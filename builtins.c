#include "shell.h"

/**
 * change_directory - changes directory
 * @data: pointer to the data structure
 *
 * Return: Succes code
 */
int change_directory(shell_info *data)
{
	char *home;

	home = _getenv("HOME");
	if (data->args[1] == NULL)
	{
		SETOWD(data->oldpwd);
		if (chdir(home) < 0)
			return (FAIL_CODE);
		return (SUCCESS_CODE);
	}
	if (_strcmp(data->args[1], "-") == 0)
	{
		if (data->oldpwd == 0)
		{
			SETOWD(data->oldpwd);
			if (chdir(home) < 0)
				return (FAIL_CODE);
		}
		else
		{
			SETOWD(data->oldpwd);
			if (chdir(data->oldpwd) < 0)
				return (FAIL_CODE);
		}
	}
	else
	{
		SETOWD(data->oldpwd);
		if (chdir(data->args[1]) < 0)
			return (FAIL_CODE);
	}
	return (SUCCESS_CODE);
}
#undef GETCWD
/**
 * abort_program - exit the program
 * @data: a pointer to the data structure
 *
 * Return: Succes code
 */
int abort_program(shell_info *data __attribute__((unused)))
{
	int code, i = 0;

	if (data->args[1] == NULL)
	{
		free_data(data);
		exit(errno);
	}
	while (data->args[1][i])
	{
		if (_isalpha(data->args[1][i++]) < 0)
		{
			data->error_msg = _strdup("Illegal number\n");
			return (FAIL_CODE);
		}
	}
	code = _atoi(data->args[1]);
	free_data(data);
	exit(code);
}

/**
 * handle_builtin - handle and manage the builtins command
 * @data: a pointer to the data structure
 *
 * Return: Succes code
 */
int handle_builtin(shell_info *data)
{
	built_in blt[] = {
		{"exit", abort_program},
		{"cd", change_directory},
		{NULL, NULL}
	};
	int count = 0;

	while ((blt + i)->command)
	{
		if (_strcmp(data->args[0], (blt + i)->command) == 0)
			return ((blt + i)->f(data));
		count++;
	}
	return (FAIL_CODE);
}
