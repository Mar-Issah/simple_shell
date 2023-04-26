#include "shell.h"

#define SETOWD(V) (V = _strdup(_getenv("OLDPWD")))
/**
 * change_dir - changes directory
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 */
int change_dir(shell_info *data)
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
 * abort_prg - exit the program
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 */
int abort_prg(shell_info *data __attribute__((unused)))
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
 * handle_builtin - handle and manage the builtins cmd
 * @data: a pointer to the data structure
 *
 * Return: (Success) 0 is returned
 */
int handle_builtin(shell_info *data)
{
	built_in blt[] = {
		{"exit", abort_prg},
		{"cd", change_dir},
		{NULL, NULL}
	};
	int i = 0;

	while ((blt + i)->cmd)
	{
		if (_strcmp(data->args[0], (blt + i)->cmd) == 0)
			return ((blt + i)->f(data));
		i++;
	}
	return (FAIL_CODE);
}
