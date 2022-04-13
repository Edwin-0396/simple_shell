#include "simple_shell.h"

cmd_t parse_cmd(char *full_command)
{
	int i = 0, count = 0;
	char *token = NULL;

	cmd_t cmd = {
			.command = NULL,
			.args = NULL,
	};

	/** Remove the last character '\n' for '\0' */
	full_command[strlen(full_command) - 1] = '\0';

	// ["ls", "-l", "-a", "-b"]
	token = strtok(full_command, " ");

	while (token != NULL)
	{
		count++;
		token = strtok(NULL, " ");
	}

	free(token);

	/**
	 * -1 because ignoring the command
	 */
	cmd.args = malloc(sizeof(char) * (4 - 1));
	if (cmd.args == NULL)
		exit(1);
	token = strtok(full_command, " ");

	while (token != NULL)
	{
		if (!cmd.command)
		{
			cmd.command = malloc(sizeof(char) * strlen(token));
			if (!cmd.command)
				exit(1);
			if (cmd.command)
				cmd.command = strdup(token);
		}
		else
		{
			cmd.args[i] = malloc(sizeof(char) * strlen(token));
			if (!cmd.args[i])
			{
				free(cmd.command);
				exit(1);
			}
			if (cmd.args[i])
				cmd.args[i] = token;
			i++;
		}
		token = strtok(NULL, " ");
	}

	free(token);

	return (cmd);
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
	char *line = NULL, *token = NULL;
	int count = 0;

	/**
	 * SIGINT = Interrupt the process
	 * rewrite default signals handler
	 *
	 * SIG_IGN = Ignore signal.
	 */
	signal(SIGINT, SIG_IGN);

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
		cmd_t cmd = parse_cmd(line);

		if (strcmp(cmd.command, "exit") == 0)
		{
			free(cmd.command);
			for (int i = 0; i < count; i++)
			{
				free(cmd.args[i]);
			}
			free(cmd.args);
			free(line);
			exit(0);
		}

		// Func that free all mallocs
		free(cmd.command);
		for (int i = 0; i < count; i++)
		{
			free(cmd.args[i]);
		}
		free(cmd.args);

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
