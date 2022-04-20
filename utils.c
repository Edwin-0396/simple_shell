#include "simple_shell.h"

/**
 * free_all - function that frees all the content of struct
 * @cmd: input struct
 */
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

/**
 * new_signal_handler - funciton that ignores the signal
 * to interrupt the process
 *@pid: pid of the process
 */

void new_signal_handler(int pid __attribute__((unused)))
{
	if (write(STDOUT_FILENO, "\n$ ", 3) == EOF)
		exit(EXIT_FAILURE);
}

/**
 * _getline - funciton that get input line
 *@line: input string
 */
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

/**
 * remove_spaces - funciton that remove spaces from a string
 *@cmd: input struct of cmd
 */
void remove_spaces(cmd_t *cmd)
{
	int i = 0, j = 0;

	while (cmd->command[i])
	{
		if (cmd->command[i] != ' ')
			cmd->command[j++] = cmd->command[i];
		i++;
	}
	cmd->command[j] = '\0';
}

/**
 * find_char - function that find a character
 *@cmd: input struct of cmd
 *Return: bool true if found and false if not
 */
bool find_char(cmd_t *cmd)
{
	int index = 0;
	bool flag = false;
	char cmp = '/';

	remove_spaces(cmd);

	while (cmd->command[index])
	{
		if (cmd->command[index] == cmp)
		{
			flag = true;
			return (flag);
		}
		index++;
	}
	return (flag);
}
