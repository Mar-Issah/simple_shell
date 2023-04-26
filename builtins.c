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
 * handle_builtin - handle builtin command
 * @input: pointer to the data struc
 *
 * Return: Succes code
 */
int handle_builtin(shell_info *input)
{
	built_in blt[] = {
		{"exit", abort_program},
		{"cd", change_directory},
		{NULL, NULL}
	};
	int count = 0;

	while ((blt + count)->command)
	{
		if (_strcmp(input->args[0], (blt + i)->command) == 0)
			return ((blt + count)->f(data));
		count++;
	}
	return (FAIL_CODE);
}
/**
 * abort_program - abort the program
 * @data: pointer to the data structure
 * Return: Succes code
 */
int abort_program(shell_info *input __attribute__((unused)))
{
	int code, i = 0;

	if (input->args[1] == NULL)
	{
		free_data(input);
		exit(errno);
	}
	while (input->args[1][i])
	{
		if (_isalphabet(input->args[1][i++]) < 0)
		{
			input->error_msg = _strdup("Illegal number\n");
			return (FAIL_CODE);
		}
	}
	code = _atoi(input->args[1]);
	free_data(input);
	exit(code);
}

