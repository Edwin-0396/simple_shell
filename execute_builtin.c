#include "simple_shell.h"

bool execute_builtin(cmd_t *cmd, char **envs)
{
	if (strcmp(cmd->command, "exit") == 0)
	{
		free_all(cmd);
		exit(EXIT_SUCCESS);
	}

	if (strcmp(cmd->command, "env") == 0)
	{
		while (*envs)
		{
			printf("%s\n", *envs);
			envs++;
		}
		free_all(cmd);
		return (true);
	}

	if (strcmp(cmd->command, "cd") == 0)
	{
		printf("I'm cd command\n");
		free_all(cmd);
		return (true);
	}
	return (false);
}
