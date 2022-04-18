#include "simple_shell.h"

char *get_path_from_command(cmd_t *cmd, char *envPath)
{
	char *path = NULL,
			 *token = NULL,
			 *tempEnvPath = NULL,
			 *tempToken = NULL;
	struct stat stats;

	tempEnvPath = _strdup(envPath);

	token = strtok(tempEnvPath, ":");
	while (token != NULL)
	{
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
	cmd_t *cmd = (cmd_t *)malloc(sizeof(cmd_t));
	if (!cmd)
		return NULL;

	cmd->n_args = n_args;
	cmd->command = NULL;
	cmd->args = NULL;

	cmd->args = (char **)malloc(sizeof(char *) * n_args);
	if (cmd->args == NULL)
	{
		free_all(cmd);
		return NULL;
	}
	return (cmd);
}

int count_args_by_space(char *input)
{
	int count = 0;
	/**
	 * Duplicate the "input" variable
	 * for non modificated.
	 *
	 * Because the function strtok() modified
	 * the variable that provide.
	 *
	 * And the end make a free for the
	 * variable duplicated "dup"
	 */

	char *dup = _strdup(input);
	char *token = strtok(dup, " ");

	while (token != NULL)
		count++, token = strtok(NULL, " ");

	/**
	 * Make a count of all input
	 * included the command
	 *
	 * ["ls", "-l", "-a", "-b"] = 4
	 *
	 * And put -1 for ignoring the command
	 * ["-l", "-a", "-b"] = 3
	 *
	 * (-1) because ignoring the command
	 */

	//  = condition ? case true : case false;
	count = count >= 1 ? (count - 1) : 0;
	free(dup);

	return (count);
}

cmd_t *parse_cmd(char *input)
{
	int i = 0, args_count = 0;
	cmd_t *cmd = NULL;
	char *token = NULL;

	/**
	 * Remove the "\n" of the end
	 * from the variable - (line)
	 *
	 * Example:
	 *  input - "hola\n" and should
	 * 	be "hola"... Without the break line
	 */
	/** Remove the last character '\n' for '\0' */
	if (input[strlen(input) - 1] == '\n')
		input[strlen(input) - 1] = '\0';

	/**
	 * Return the count of the args
	 * each arg its separated by space
	 *
	 * Example:
	 * - ["ls", "-l", "-a", "-b"]
	 * Output: 3
	 */
	args_count = count_args_by_space(input);

	cmd = new_cmd(args_count);
	if (!cmd)
		return NULL;

	if (cmd->n_args == 0)
	{
		cmd->command = _strdup(input);
		return (cmd);
	}
	// Input: ls -l -a -b
	// command = [ls] [-l] [-a] [-b]

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