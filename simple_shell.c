#include "simple_shell.h"

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

	signal(SIGINT, new_signal_handler);

	while (true)
	{
		line = NULL;
		commandPath = NULL;
		count++;

		if (isatty(STDIN_FILENO) == 1)
		{
			if (write(STDOUT_FILENO, "$ ", 2) == EOF)
				exit(EXIT_FAILURE);
		}
		if ((nread = getline(&line, &len, stdin)) == EOF)
		{
			if (isatty(STDIN_FILENO) != 0)
				write(STDOUT_FILENO, "\n", 1);
			exit(EXIT_FAILURE);
		}

		cmd_t *cmd = parse_cmd(line);
		free(line);

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
			continue;
		}

		if (strcmp(cmd->command, "cd") == 0)
		{
			printf("I'm cd command\n");
			free_all(cmd);
			continue;
		}

		commandPath = get_path_from_command(cmd, envPath);
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
			int totalCommand = cmd->n_args + 1;

			char **arg_list = malloc(sizeof(char *) * totalCommand + 1);

			int i = 0;
			while (i < totalCommand)
			{
				if (i == 0)
					arg_list[i] = commandPath;
				else
					arg_list[i] = cmd->args[i - 1];
				i++;
			}
			execv(commandPath, arg_list);
		}
		wait(&statusLock);
		free(commandPath);
		free_all(cmd);
	}
	return (EXIT_SUCCESS);
}
