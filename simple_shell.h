#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>

typedef struct CMD
{
	char *command;
	char **args;
	int n_args;
} cmd_t;

#endif
