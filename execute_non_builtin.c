#include "simple_shell.h"

int execute_non_builtin(cmd_t *cmd, char *commandPath)
{
	int statusLock;
	char **arg_list = NULL;
	int totalCommand = cmd->n_args + 1;
	int i = 0;
	pid_t childPid;

	arg_list = malloc(sizeof(char *) * (totalCommand + 1));
	if (!arg_list)
		return (EXIT_FAILURE);
	while (i < totalCommand)
	{
		if (i == 0)
			arg_list[i] = strdup(commandPath);
		else
			arg_list[i] = strdup(cmd->args[i - 1]);
		i++;
	}
	arg_list[i] = NULL;

	childPid = fork();
	if (childPid == 0)
		execv(commandPath, arg_list);
	wait(&statusLock);

	if (arg_list)
	{
		for (i = 0; arg_list[i]; i++)
			free(arg_list[i]);
		free(arg_list);
	}
	return (EXIT_SUCCESS);
}
