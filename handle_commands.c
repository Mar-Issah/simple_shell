#include "shell.h"
/**
 * read_command - read a line from the standard input
 * @data: a pointer to the struct of data
 *
 * Return: Succes code
 */
int read_command(shell_info *data)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, new_size;

	data->line = malloc(size * sizeof(char));
	if (data->line == NULL)
		return (FAIL_CODE);
	if (isatty(STDIN_FILENO))
		PRINT(PROMPT);
	for (csr_ptr = data->line, end_ptr = data->line + size;;)
	{
		read_st = read(STDIN_FILENO, &c, 1);
		if (read_st == 0)
			return (FAIL_CODE);
		*csr_ptr++ = c;
		if (c == '\n')
		{
			*csr_ptr = '\0';
			return (SUCCESS_CODE);
		}
		if (csr_ptr + 2 >= end_ptr)
		{
			new_size = size * 2;
			length = csr_ptr - data->line;
			data->line = _realloc(data->line, size * sizeof(char),
						new_size * sizeof(char));
			if (data->line == NULL)
				return (FAIL_CODE);
			size = new_size;
			end_ptr = data->line + size;
			csr_ptr = data->line + length;
		}
	}
}
#define DELIMITER " \n\t\r\a\v"
/**
 * split_command - splits line to tokens
 * @data: a pointer to the struct of data
 *
 * Return: Succes code
 */
int split_command(shell_info *data)
{
	char *token;
	size_t size = TOKENSIZE, new_size, i = 0;

	if (_strcmp(data->line, "\n") == 0)
		return (FAIL_CODE);
	data->args = malloc(size * sizeof(char *));
	if (data->args == NULL)
		return (FAIL_CODE);
	token = strtok(data->line, DELIMITER);
	if (token == NULL)
		return (FAIL_CODE);
	while (token)
	{
		data->args[i++] =  token;
		if (i + 2 >= size)
		{
			new_size = size * 2;
			data->args = _realloc(data->args, size * sizeof(char *),
					new_size * sizeof(char *));
			if (data->args == NULL)
				return (FAIL_CODE);
			size = new_size;
		}
		token = strtok(NULL, DELIMITER);
	}
	data->args[i] = NULL;
	return (0);
}
#undef DELIMITER
#define DELIMITER ":"
/**
 * parse_command - parses arguments to valid command
 * @data: a pointer to the struct of data
 *
 * Return: Succes code
 */
int parse_command(shell_info *data)
{
	if (is_path_form(data) > 0)
		return (SUCCESS_CODE);
	if (is_builtin(data) > 0)
	{
		if (handle_builtin(data) < 0)
			return (FAIL_CODE);
		return (NEUTRAL_CODE);
	}
	is_short_form(data);
	return (SUCCESS_CODE);
}
#undef DELIMITER
/**
 * process_command - process command and execute process
 * @data: a pointer to the struct of data
 *
 * Return:Succes code
 */
int process_command(shell_info *data)
{
	pid_t pid;
	int status;

	pid = fork();
	if (pid == 0)
	{
		signal(SIGINT, SIG_DFL);
		if (execve(data->command, data->args, environ) < 0)
		data->error_msg = _strdup("not found\n");
			return (FAIL_CODE);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}
