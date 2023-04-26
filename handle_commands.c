#include "shell.h"
/**
 * read_command - read line from stdin
 * @data: pointer to the struct of data
 *
 * Return: Succes code
 */
int read_command(shell_info *data)
{
	char *csr_ptr, *end_ptr, c;
	size_t size = BUFSIZE, read_st, length, updated_size;

	data->line = malloc(size * sizeof(char));
	if (data->line == NULL)
		return (FAIL_CODE);
	if (isatty(STDIN_FILENO))
		LOG(PROMPT);
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
			updated_size = size * 2;
			length = csr_ptr - data->line;
			data->line = _realloc(data->line, size * sizeof(char),
						updated_size * sizeof(char));
			if (data->line == NULL)
				return (FAIL_CODE);
			size = updated_size;
			end_ptr = data->line + size;
			csr_ptr = data->line + length;
		}
	}
}
#define DELIMITER " \n\t\r\a\v"

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
		data->error_message = _strdup("not found\n");
			return (FAIL_CODE);
	}
	else
	{
		waitpid(pid, &status, WUNTRACED);
	}
	return (0);
}

/**
 * split_command - splits line to tokens
 * @data: a pointer to the struct of data
 *
 * Return: Succes code
 */
int split_command(shell_info *data)
{
	char *token;
	size_t size = TOKENSIZE, updated_size, i = 0;

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
			updated_size = size * 2;
			data->args = _realloc(data->args, size * sizeof(char *),
					updated_size * sizeof(char *));
			if (data->args == NULL)
				return (FAIL_CODE);
			size = updated_size;
		}
		token = strtok(NULL, DELIMITER);
	}
	data->args[i] = NULL;
	return (0);
}
#undef DELIMITER
#define DELIMITER ":"
/**
 * parse_command - parses arguments
 * @data: a pointer to the struct of data
 *
 * Return: Succes code
 */
int parse_command(shell_info *input)
{
	if (is_path_string(input) > 0)
		return (SUCCESS_CODE);
	if (is_builtin(input) > 0)
	{
		if (handle_builtin(input) < 0)
			return (FAIL_CODE);
		return (NEUTRAL_CODE);
	}
	is_abbreviated(input);
	return (SUCCESS_CODE);
}
#undef DELIMITER
