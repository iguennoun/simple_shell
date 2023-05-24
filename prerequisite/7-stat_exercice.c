#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

/* check_file - Check if a file exist
 * @file : The path of the file to check existance
 *
 * Return: Void
 */

void check_file(char *file)
{
	if (access(file, F_OK) == 0)
		printf("%s : FOUND\n", file);
	else
		printf("%s : NOT FOUND\n", file);
}

/**
 * main - stat exercice
 * @ac : Nbr of params
 * @av : Arrays of params
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	char *line = NULL;	
	size_t linecap = 0;
	ssize_t linelen;
	char *path;

	(void) linelen;

	while (1)
	{
		write(1, "$ ", 2);
		linelen = getline(&line, &linecap, stdin);
		path = strtok(line, " \n\t");

		if (strcmp(path, "which") == 0)
		{
			path = strtok(NULL, " \n\t");
			while (path)
			{
				check_file(path);
				path = strtok(NULL, " \n\t");
			}
		}
		else
			printf("The file doesn't exist !!!\n");
	}

	return (0);
}
