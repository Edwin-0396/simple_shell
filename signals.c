#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <time.h>
#include <signal.h>

/**
 * #define SIGHUP  1   // Hangup the process
 * #define SIGINT 2 	 // Interrupt the process
 * #define SIGQUIT 3 	 // Quit the process
 * #define SIGILL 4		 // Illegal instruction.
 * #define SIGTRAP 5 	 // Trace trap.
 * #define SIGABRT 6 	 // Abort.
 */

/**
 * sample handler that replace a SIGINT default call
 */
void new_handler(int num __attribute__((unused)))
{
	printf("Nice try haha!\n");
}

/**
 * Simple example to modify signal handler
 *
 * gcc signals.c -o signals && ./signals
 */
int main(int argc, char const *argv[])
{
	pid_t current_pid = getpid();

	/**
	 * Replacing the default signal handler
	 * of "SIGINT" (Interrupt process event)
	 * with "new_handler". That will execute
	 * when a recieve the signal "SIGINT"
	 *
	 * In the case the assignation fail
	 * should return (-1) otherwise
	 * return different of that
	 */
	if (signal(SIGINT, new_handler) == SIG_ERR)
	{
		printf("error asigning to signal a new handler\n");
		exit(1);
	}

	/**
	 * Sends itself a SIGINT signal
	 */
	kill(current_pid, SIGINT);
	printf("I am still alive!!\n");
	kill(current_pid, SIGINT);
	printf("I am still alive!!\n");
	kill(current_pid, SIGINT);
	printf("I am still alive!!\n");

	return 0;
}
