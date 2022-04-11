#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h> // wait a child proccess
#include <time.h>

int main(void)
{
	int statusLock;
	/**
	 * -1: Error not child proccess assigned
	 * 	0: child proccess assigned
	 * > 0: parent proccess id
	 */
	pid_t child = fork();
	pid_t child1 = fork();
	pid_t child2 = fork();
	pid_t app = getpid();

	printf("PID of my app %i\n", app);
	printf("PID of my child %i\n", child);

	if (child == 0)
	{
		/**
		 * I'm child
		 */

		printf("Child is doing something\n");

		char *arg_list[] = {"/usr/bin/sleep", "10", NULL};
		execvp("/usr/bin/sleep", arg_list);
	}

	if (child1 == 0)
	{
		/**
		 * I'm child
		 */

		printf("Child 1 is doing something\n");

		char *arg_list[] = {"/usr/bin/sleep", "10", NULL};
		execvp("/usr/bin/sleep", arg_list);
	}

	if (child2 == 0)
	{
		/**
		 * I'm child
		 */

		printf("Child 2 is doing something\n");

		char *arg_list[] = {"/usr/bin/sleep", "10", NULL};
		execvp("/usr/bin/sleep", arg_list);
	}

	/**
	 * Im parent
	 *
	 */
	printf("Parents is wating the sons\n");
	wait(&statusLock);

	printf("%d\n", statusLock);
	printf("%d\n", WEXITSTATUS(statusLock));

	printf("I'm parent!\n");

	return 0;
}
