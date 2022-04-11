#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

/**
 * Simple example of
 * prompt implementation
 *
 * gcc prompt.c -o prompt && ./prompt
 */

int main(int argc, char *argv[])
{
	char *line = NULL;
	size_t len = 0;
	ssize_t nread;

	char *shell_alias = "$ ";

	char *error = NULL;

	write(STDOUT_FILENO, shell_alias, strlen(shell_alias));

	/**
	 * Each iteration of the while loop
	 * get the line provided by the user
	 *
	 * Where
	 * - line: Content provided by the user
	 * - len: Lenght of the content
	 * - stdin: I don't know yet
	 *
	 * In the case of the reading (getline)
	 * failed return -1, otherwise
	 * return different of that
	 */
	
	/* non-interactive*/
	if(argc > 0)
	{
		get_func(*argv);



	}

	/*interactive*/
	while ((nread = getline(&line, &len, stdin)) != -1 && argc != 0)
	{
		if (strcmp(line, "exit\n") == 0)
		{
			free(line);
			exit(0);
		}
		
		/*
			all the structure for built-ins
		*/

		/* if built-in not found print error: */	
		error = "shs: line_number: current_command_not_found: not found\n";
		write(STDOUT_FILENO, error, strlen(error));

		write(STDOUT_FILENO, shell_alias, strlen(shell_alias));
	}

	free(line);
	exit(EXIT_SUCCESS);
}
