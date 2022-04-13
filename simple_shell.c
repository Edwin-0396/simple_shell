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

	char *dup = strdup(input);
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
	count = count > 0 ? (count - 1) : 0;
	free(dup);

	return (count);
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
		cmd->command = strdup(input);
		return (cmd);
	}

	token = strtok(input, " ");
	while (token != NULL)
	{
		if (cmd->command == NULL)
			cmd->command = strdup(token);

		else
			cmd->args[i] = strdup(token), i++;

		token = strtok(NULL, " ");
	}

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
	char *line;
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
		line = NULL;
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
		free(line);

		if (strcmp(cmd->command, "exit") == 0)
		{
			free_all(cmd);
			exit(0);
		}

		// Func that free all mallocs
		free_all(cmd);
	}

	return (EXIT_SUCCESS);
}
