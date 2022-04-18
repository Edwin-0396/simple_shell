#include "simple_shell.h"

void free_all(cmd_t *cmd)
{
	int i = 0;

	if (cmd)
	{
		free(cmd->command);
		cmd->command = NULL;

		if (cmd->args)
		{
			for (; i < cmd->n_args; i++)
			{
				if (cmd->args[i])
					free(cmd->args[i]);
			}
			free(cmd->args);
			cmd->args = NULL;
		}
		free(cmd);
		cmd = NULL;
	}
}

void new_signal_handler(int pid __attribute__((unused)))
{
	if (write(STDOUT_FILENO, "\n$ ", 3) == EOF)
		exit(EXIT_FAILURE);
}

void _getline(char **line)
{
	size_t len = 0;
	ssize_t nread = 0;

	nread = getline(line, &len, stdin);
	if (nread == EOF)
	{
		if (isatty(STDIN_FILENO) != 0)
			write(STDOUT_FILENO, "\n", 1);
		exit(EXIT_FAILURE);
	}
}
