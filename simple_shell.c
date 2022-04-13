#include "simple_shell.h"

void free_all(cmd_t *cmd, char *line)
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

	if (line)
	{
		free(line);
		line = NULL;
	}
}

int count_args_by_space(char *full_command)
{
	int count = 0;
	char *dup = strdup(full_command);
	char *token = strtok(dup, " ");

	while (token != NULL)
		count++, token = strtok(NULL, " ");

	/**
	 * -1 because ignoring the command
	 */
	count = count > 0 ? (count - 1) : 0;
	free(dup);

	return (count);
}

cmd_t *new_cmd(int n_args)
{
	cmd_t *cmd = (cmd_t *)malloc(sizeof(cmd_t));
	if (!cmd)
		return NULL;

	cmd->command = NULL;
	cmd->n_args = n_args;
	cmd->args = NULL;

	cmd->args = (char **)malloc(sizeof(char *) * n_args);
	if (cmd->args == NULL)
	{
		free_all(cmd, NULL);
		return NULL;
	}
	return (cmd);
}

cmd_t *parse_cmd(char *input)
{
	int i = 0, args_count = 0;
	cmd_t *cmd = NULL;
	char *token = NULL,
			 *full_command = NULL;

	full_command = strdup(input);

	/** Remove the last character '\n' for '\0' */
	full_command[strlen(full_command) - 1] = '\0';

	// ["ls", "-l", "-a", "-b"]
	args_count = count_args_by_space(full_command);

	cmd = new_cmd(args_count);
	if (!cmd)
	{
		free(full_command);
		return NULL;
	}

	if (cmd->n_args == 0)
	{
		cmd->command = strdup(full_command);
		free(full_command);
		return (cmd);
	}

	token = strtok(full_command, " ");
	while (token != NULL)
	{
		if (cmd->command == NULL)
			cmd->command = strdup(token);

		else
			cmd->args[i] = strdup(token), i++;

		token = strtok(NULL, " ");
	}

	free(full_command);
	return (cmd);
}

void new_signal_handler(int num __attribute__((unused)))
{
	if (write(STDOUT_FILENO, "\n$ ", 3) == EOF)
		exit(EXIT_FAILURE);
}

/**
 * main - Shell program (entry point)
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[])
{
	/* Variables */
	size_t len = 0;
	ssize_t nread;
	char *line = NULL;
	int count = 0;

	/**
	 * SIGINT = Interrupt the process
	 * rewrite default signals handler
	 *
	 * SIG_IGN = Ignore signal.
	 */
	signal(SIGINT, new_signal_handler);

	while (true)
	{
		count++;
		/**
		 * Print the prompt - "$ "
		 * when failed return (-1)
		 */

		if (isatty(STDIN_FILENO) == 1)
		{
			if (write(STDOUT_FILENO, "$ ", 2) == EOF)
				exit(EXIT_FAILURE);
		}

		/* line the input provided by the user*/
		if ((nread = getline(&line, &len, stdin)) == EOF)
		{
			if (isatty(STDIN_FILENO) != 0)
				write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}

		/* Manipulate line(read buffer)*/
		cmd_t *cmd = parse_cmd(line);

		if (strcmp(cmd->command, "exit") == 0)
		{
			free_all(cmd, line);
			exit(0);
		}

		// Func that free all mallocs
		free_all(cmd, NULL);

		/**
		 * Remove the "\n" of the end
		 * from the variable - (line)
		 *
		 * Example:
		 *  input - "hola\n" and should
		 * 	be "hola"... Without the break line
		 */
	}

	return (EXIT_SUCCESS);
}
