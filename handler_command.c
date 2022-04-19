#include "simple_shell.h"

char *get_path_from_command(cmd_t *cmd, char *envPath)
{
	char *path = NULL,
		 *token = NULL,
		 *tempEnvPath = NULL;
	struct stat stats;
	bool flag = false;

	tempEnvPath = _strdup(envPath);

	token = strtok(tempEnvPath, ":");
	flag = find_char(cmd);
	
	while (token != NULL)
	{
		if (flag == true)
			path = _strdup(cmd->command);
		else
			path = _strconcat(token, "/", cmd->command);

		if (stat(path, &stats) == 0)
			break;

		free(path);
		path = NULL;
		token = strtok(NULL, ":");
	}

	free(tempEnvPath);

	if (!path)
		return (NULL);
	return (path);
}

cmd_t *new_cmd(int n_args)
{
	cmd_t *cmd = NULL;

	cmd = (cmd_t *)malloc(sizeof(cmd_t));
	if (!cmd)
		return (NULL);

	cmd->n_args = n_args;
	cmd->command = NULL;
	cmd->args = NULL;

	cmd->args = (char **)malloc(sizeof(char *) * n_args);
	if (cmd->args == NULL)
	{
		free_all(cmd);
		return (NULL);
	}
	return (cmd);
}

int count_args_by_space(char *input)
{
	int count = 0;
	char *dup = _strdup(input);
	char *token = strtok(dup, " ");

	while (token != NULL)
		count++, token = strtok(NULL, " ");

	count = count >= 1 ? (count - 1) : 0;
	free(dup);
	return (count);
}

cmd_t *parse_cmd(char *input)
{
	int i = 0, args_count = 0;
	cmd_t *cmd = NULL;
	char *token = NULL;

	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	args_count = count_args_by_space(input);

	cmd = new_cmd(args_count);
	if (!cmd)
		return (NULL);

	if (cmd->n_args == 0)
	{
		cmd->command = _strdup(input);
		return (cmd);
	}

	token = strtok(input, " ");
	while (token != NULL)
	{
		if (cmd->command == NULL)
			cmd->command = _strdup(token);

		else
			cmd->args[i] = _strdup(token), i++;

		token = strtok(NULL, " ");
	}

	return (cmd);
}
