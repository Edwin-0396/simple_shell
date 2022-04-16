#ifndef SIMPLE_SHELL
#define SIMPLE_SHELL

#include <stdlib.h>
#include <stdio.h>
#include <wait.h>
#include <unistd.h>
#include <signal.h>
#include <stdbool.h>
#include <string.h>
#include <sys/stat.h>
#include <stdarg.h>

#define EMPTY_STR ""

typedef struct CMD
{
	char *command;
	char **args;
	int n_args;
} cmd_t;

char *_strconcat(char *s1, char *s2, char *s3);
char *_strdup(char *str);
int _strlen(const char *str);
int _countby(char *str, char *delimeter);

#endif
