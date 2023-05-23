#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

/**
 * main - Exercice : fork + wait + execve
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t pid;
	int nbr_child_p = 0, status;
	char *args[] = {"/bin/ls", "-l", "/tmp", NULL};

	for (nbr_child_p = 0; nbr_child_p < 5; nbr_child_p++)
	{
		pid = fork();
		if (pid == -1)
		{
			perror("Error: fork() didn't work!!");
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			if (execve(args[0], args, NULL) == -1)
			{
				perror("Error executing subroutine");
				exit(EXIT_FAILURE);
			}
		}
		else
		{
			wait(&status);
		}
	}
	exit(EXIT_SUCCESS);
}
