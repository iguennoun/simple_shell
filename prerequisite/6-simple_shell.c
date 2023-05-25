#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

/**
 * main - Exercice : Super simple shell
 *
 * Return: Always 0.
 */
int main(void)
{
	char *line = NULL;
	size_t linecap = 0;
	ssize_t linelen;
	char **params = NULL, *param, delimiters[] = " \n\t";
	int i = 0, status;
	pid_t pid;
	
	(void) linelen;

	while (1)
	{
		write(1, "$ ", 2);
		linelen = getline(&line, &linecap, stdin);
		param = strtok(line, delimiters);
		params = malloc(sizeof(char *) * 1024);
		while (param)
		{
			params[i] = param;
			param = strtok(NULL, delimiters);
			i++;
		}
		params[i] = NULL;
		pid = fork();
		if (pid == 0)
		{
			if (execve(params[0], params, NULL) == -1)
			{
				perror("Error executing command (execve)");
				exit(EXIT_FAILURE);
			}

		}
		else
		{
			wait(&status);
		}
		i = 0;
		free(params);
	}

	exit(EXIT_SUCCESS);
}
