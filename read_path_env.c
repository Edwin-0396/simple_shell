#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>

/**
 * Simple example of read env variables
 * and how to find "PATH=" env variable
 *
 * gcc read_path_env.c -o read_path_env && ./read_path_env
 */

int main(int argc __attribute__((unused)), char **argv __attribute__((unused)), char **env)
{
	while (strncmp(*env, "PATH=", strlen("PATH=")) != 0)
		env++;

	printf("\n%s\n\n", *env);
	return 0;
}
