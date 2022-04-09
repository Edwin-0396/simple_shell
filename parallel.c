#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
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
	pid_t app = getpid();

	printf("PID of my app %i\n", app);
	printf("PID of my child %i\n", child);

	if (child == 0)
	{
		/**
		 * I'm child
		 */

		printf("Child is doing something\n");

		char *arg_list[] = {"/usr/bin/sleep", "4", NULL};
		execvp("/usr/bin/sleep", arg_list);
	}

	/**
	 * Im parent
	 *
	 */
	wait(&statusLock);

	printf("%d\n", statusLock);
	printf("%d\n", WEXITSTATUS(statusLock));

	printf("I'm parent!\n");

	return 0;
}
