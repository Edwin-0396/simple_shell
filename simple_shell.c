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

char *concatenate(const char *a, const char *b, const char *c)
{
	int total_len;
	a = a ? a : EMPTY_STR;
	b = b ? b : EMPTY_STR;
	c = c ? c : EMPTY_STR;

	total_len = strlen(a) + strlen(b) + strlen(c);

	if (total_len == 0)
		return NULL;

	char *dest = malloc(total_len + 1);
	strcpy(dest, a);

	dest = strcat(dest, b);
	dest = strcat(dest, c);
	return dest;
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
	count = count >= 1 ? (count - 1) : 0;
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

void new_signal_handler(int pid __attribute__((unused)))
{
	// prompconte signo
	if (write(STDOUT_FILENO, "\n$ ", 3) == EOF)
		exit(EXIT_FAILURE);
}

char *get_non_builtin(cmd_t *cmd, char *envPath)
{
	char *path = NULL,
			 *token = NULL,
			 *tempEnvPath = NULL,
			 *tempToken = NULL;
	struct stat stats;

	tempEnvPath = strdup(envPath);

	token = strtok(tempEnvPath, ":");
	while (token != NULL)
	{
		path = concatenate(token, "/", cmd->command);

		if (stat(path, &stats) == 0)
			break;

		free(path);
		path = NULL;
		token = strtok(NULL, ":");
	}

	if (!path)
	{
		free(tempEnvPath);
		return (NULL);
	}

	free(tempEnvPath);
	return (path);
}

/**
 * main - Shell program (entry point)
 * Return: Always 0 (Success)
 */
int main(int argc, char *argv[], char **envs)
{
	/* Variables */
	size_t len = 0;
	ssize_t nread = 0;
	char *line = NULL;
	int count = 0;
	struct stat statistics;
	char *commandPath = NULL, *envPath;

	envPath = getenv("PATH");

	/**
	 * SIGINT = Interrupt the process
	 * rewrite default signals handler
	 *
	 * SIG_IGN = Ignore signal.
	 */
	signal(SIGINT, new_signal_handler);

	while (true)
	{
		// if (NULL) == false
		// if ("") == true
		line = NULL;
		commandPath = NULL;
		count++;

		// TODO: What the f*** doing this!!!
		if (isatty(STDIN_FILENO) == 1)
		{
			/**
			 * Print the prompt - "$ "
			 * when failed return (-1)
			 */
			if (write(STDOUT_FILENO, "$ ", 2) == EOF)
				exit(EXIT_FAILURE);
		}
		// TODO: What the f*** doing this!!!

		/* line the input provided by the user*/
		// (len) what function doing this??
		if ((nread = getline(&line, &len, stdin)) == EOF)
		{
			// TODO: What the f*** doing this!!! - Edwin
			if (isatty(STDIN_FILENO) != 0)
				write(STDOUT_FILENO, "\n", 1);
			// TODO: What the f*** doing this!!! - Edwin
			exit(EXIT_FAILURE);
		}

		/**
		 * Parse - Proccess a string and
		 * return in the format that I want
		 *
		 * In this case I want is a
		 * struct of type "cmd_t"
		 *
		 * Manipulate line(read buffer)
		 */
		cmd_t *cmd = parse_cmd(line);
		free(line);

		// ----------------------------------- build-in-functions----------------------
		if (strcmp(cmd->command, "exit") == 0)
		{
			free_all(cmd);
			exit(0);
		}

		if (strcmp(cmd->command, "cd") == 0)
		{
			printf("I'm cd command\n");
			free_all(cmd);
			continue;
		}

		// ----------------------------------- build-in-functions----------------------

		// ----------------------------------- no-build-in-functions----------------------

		/**
		 * Extract the command path
		 *
		 */
		commandPath = get_non_builtin(cmd, envPath);
		if (!commandPath)
		{
			printf("%s: command not found\n", cmd->command);
			free(commandPath);
			free_all(cmd);
			continue;
		}

		pid_t childPid = fork();
		int statusLock;

		if (childPid == 0)
		{
			// cmd->n_args;
			// ([ arg1, arg2, arg3 ]) = 3;
			int totalCommand = cmd->n_args + 1;

			char **arg_list = malloc(sizeof(char *) * totalCommand);

			int i = 0;
			while (i < totalCommand)
			{
				if (i == 0)
					arg_list[i] = commandPath;
				else
					arg_list[i] = cmd->args[i - 1];
				i++;
			}

			// [command, arg1, arg2, arg3] = 4

			// arg_list = [command] || cmd->args = [arg1, arg2, arg3]
			// [1] + [2] = [1, 2];
			// [command, arg1, arg2, arg3]
			// execv(..., arg_list)
			execv(commandPath, arg_list);
		}

		wait(&statusLock);

		// implement execv

		// ----------------------------------- no-build-in-functions----------------------

		// Func that free all mallocs
		free(commandPath);
		free_all(cmd);
	}

	return (EXIT_SUCCESS);
}
