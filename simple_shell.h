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

/**
 * struct CMD - struct that homes all the elements to manage the input commands
 * @command: pointer to store the command
 * @args: double pointer to store the arguments
 * @n_args: number of arguments
 */
typedef struct CMD
{
	char *command;
	char **args;
	int n_args;
} cmd_t;

void free_all(cmd_t *cmd);
void new_signal_handler(int pid __attribute__((unused)));

char *get_path_from_command(cmd_t *cmd, char *envPath);
cmd_t *new_cmd(int n_args);
int count_args_by_space(char *input);
cmd_t *parse_cmd(char *input);

bool execute_builtin(cmd_t *cmd, char **envs);
int execute_non_builtin(cmd_t *cmd, char *commandPath);

void _getline(char **line);
bool find_char(cmd_t *cmd);
void remove_spaces(cmd_t *cmd);

/* String functions */
int _strlen(const char *s);
char *_strcpy(char *dest, const char *src);
char *_strcat(char *dest, char *src);
int _strcmp(char *s1, char *s2);
char *_strdup(char *str);
char *_strconcat(char *s1, char *s2, char *s3);

void Error_handler(cmd_t *cmd, char **argv);

#endif
