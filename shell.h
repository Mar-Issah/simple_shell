#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <sys/types.h>
#include <errno.h>
#include <fcntl.h>

#define SUCCESS_CODE (1)
#define FAIL_CODE (-1)
#define NEUTRAL_CODE (0)

#define BUFSIZE 256
#define TOKENSIZE 64
#define SETOWD(V) (V = _strdup(_getenv("OLDPWD")))
#define PRINT(c) (write(STDOUT_FILENO, c, _strlen(c)))
#define PROMPT "$ "


/* Global variable */
extern char **environ;

typedef struct shell_data
{
	char *line;
	char **args;
	char *command;
	char *error_msg;
	char *oldpwd;
	unsigned long int index;
	char *env;
} shell_info;


int read_command(shell_info *);
int split_command(shell_info *);
int process_command(shell_info *);
int parse_command(shell_info *);


char *_strdup(char *str);
char *_strcat(char *first, char *second);
char *_strcpy(char *dest, char *source);
int _strlen(char *str);
char *_strchr(char *str, char c);
int _strcmp(char *s1, char *s2);

typedef struct builtin
{
	char *command;
	int (*f)(shell_info *data);
} built_in;


void *_realloc(void *ptr, unsigned int old_size, unsigned int updated_size);
char *_memset(char *s, char byt, unsigned int n);
char *_memcpy(char *dest, char *src, unsigned int n);
int free_data(shell_info *);


void *fill_an_array(void *a, int el, unsigned int len);
void signal_handler(int signo);
char *_getenv(char *path_name);
void index_command(shell_info *data);
void array_rev(char *arr, int len);
char *_itoa(unsigned int n);
int intlen(int num);
int _atoi(char *c);
int print_error(shell_info *data);
int write_history(shell_info *data);
int _isalphabet(int c);

int is_path_string(shell_info *data);
void is_abbreviated(shell_info *data);
int is_builtin(shell_info *data);

int abort_program(shell_info *data);
int change_directory(shell_info *data);
int handle_builtin(shell_info *data);


#endif /* SHELL_H */
