#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

/*
 * get_params - Returns an array of strings (parameters of prog)
 * @str: The string to split
 *
 * Return: An Array of strings which are the params of the program
 */
char **get_params(char *str)
{
	char **params = NULL, *param, delimiters[] = " \n\t";
	unsigned int i = 0;

	param = strtok(str, delimiters);
	while (param)
	{
		i++;
		params = realloc(params, i * sizeof(char *));
		if (!params)
		{
			perror("Error when realloc() to increase params space used");
			exit(EXIT_FAILURE);
		}
		params[i - 1] = param;
		param = strtok(NULL, delimiters);
	}
	return (params);
}

/**
 * main - Arguments
 * @ac : Nbr of arguments
 * @av : arrays of strings (arguments)
 *
 * Return: Always 0.
 */
int main(int ac, char **av)
{
	(void)ac;
	/* 0 : av */
	int i = 0;
	/* 1 : Read line */
	char *line = NULL;
	/* linecap <=> buffer_size; line <=> buffer */
	size_t linecap = 0;
	ssize_t linelen;
	/* 2 : command line to av*/
	char **params = NULL;

	printf(" ***** 0-\n");
	while (av[i])
	{
		printf("%s\n", av[i]);
		i++;
	}

	printf(" ***** 1-\n");
	write(1, "$ ", 2);
	/* 1 = stdout = write to the standart output */
	linelen = getline(&line, &linecap, stdin);
	if (linelen == EOF)
	{
		perror("Error when getline()");
		exit(EXIT_FAILURE);
	}
	line[linelen - 1] = '\0';
	printf("%s\n", line);

	/* 2 : command line to av */
	printf(" ***** 2-\n");
	params = get_params(line);
	i = 0;
	while (params[i])
	{
		printf("%s\n", params[i]), i++;
	}

	return (0);
}
