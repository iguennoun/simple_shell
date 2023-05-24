#include <stdio.h>

/**
 * main - prints environ global variable
 *
 * Return: Always 0.
 */
int main(void)
{
	extern char **environ;
	int i = 0;

	while (environ[i])
	{
		printf("%s\n", environ[i]);
		i++;
	}
	return (0);
}
