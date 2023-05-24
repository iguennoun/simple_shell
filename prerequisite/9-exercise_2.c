#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * _getenv - Gets an environment variable
 * @name : The name of the variable to get
 *
 * Return: The value is any of the @name
 */
char *_getenv(const char *name)
{
	extern char **environ;
	int i = 0;
	char *envvkey;

	while (environ[i])
	{
		envvkey = strtok(environ[i], "=");
		if (strcmp(envvkey, name) == 0)
			return (strtok(NULL, "="));
		i++;
	}
	return (NULL);
}

/**
 * main - prints the environment
 * @ac : Nbr arguments
 * @av : An array of arguments
 * @env : An array of environment variables (var=value)
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
	printf("The value of PATH is : %s\n", _getenv("PATH"));
	return (0);
}
