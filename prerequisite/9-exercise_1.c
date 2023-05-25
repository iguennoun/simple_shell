#include <stdio.h>

/**
 * main - prints the environment
 * @ac : Nbr arguments
 * @av : An array of arguments
 * @env : An array of environment variables (var=value)
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	extern char **environ;

	printf("env     @ : %p\n", (void *) env);
	printf("environ @ : %p\n", (void *) environ);
	return (0);
}
