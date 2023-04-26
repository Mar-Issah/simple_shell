#include "shell.h"

/**
 * main - entry point
 *
 * Return: Succes code
 */
int main(void)
{
	shell_info data;
	int pl;

	_memset((void *)&data, 0, sizeof(data));
	signal(SIGINT, signal_handler);
	while (1)
	{
		index_command(&data);
		if (read_command(&data) < 0)
		{
			if (isatty(STDIN_FILENO))
				PRINT("\n");
			break;
		}
		if (split_command(&data) < 0)
		{
			free_data(&data);
			continue;
		}
		pl = parse_command(&data);
		if (pl == 0)
		{
			free_data(&data);
			continue;
		}
		if (pl < 0)
		{
			print_error(&data);
			continue;
		}
		if (process_command(&data) < 0)
		{
			print_error(&data);
			break;
		}
		free_data(&data);
	}
	free_data(&data);
	exit(EXIT_SUCCESS);
}