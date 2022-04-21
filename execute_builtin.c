#include "simple_shell.h"

/**
 * execute_builtin - function that executes a builtin command
 * @cmd: input command
 * @envs: enviroment variables
 * Return: builtin executed
 */

bool execute_builtin(cmd_t *cmd, char **envs)
{
	if (_strcmp(cmd->command, "exit") == 0)
	{
		free_all(cmd);
		exit(EXIT_SUCCESS);
	}

	if (_strcmp(cmd->command, "env") == 0)
	{
		while (*envs)
		{
			printf("%s\n", *envs);
			envs++;
		}
		free_all(cmd);
		return (true);
	}

	if (_strcmp(cmd->command, "cd") == 0)
	{
		printf("I'm cd command\n");
		free_all(cmd);
		return (true);
	}
	return (false);
}

void Error_handler(cmd_t *cmd, char **argv)
{
	char *message = NULL, *commandPath = NULL;
	int count = 0;

	message = malloc(sizeof(char) * 100);
	sprintf(message, "%s: %d: %s: not found\n", argv[0], count, cmd->command);
	write(STDERR_FILENO, message, _strlen(message));

	free(commandPath), free_all(cmd), free(message);
	if (isatty(STDIN_FILENO) != 1)
		exit(127);
}
