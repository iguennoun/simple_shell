#include <stdio.h>
#include <unistd.h>
#include <string.h>

/**
 * print_dir_path - Show the directories contained in the env var "PATH"
 * @path_value : the value of the environment variable "PATH"
 *
 * Return: void
 */
void print_dir_path(char *path_value)
{
	char *path_dir;

	path_dir = strtok(path_value, ":");
	while (path_dir)
	{
		printf("%s\n", path_dir);
		path_dir = strtok(NULL, ":");
	}
}

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
	char *path_value;
	
	path_value = _getenv("PATH");
	printf("The value of PATH is : %s\n***\n", path_value);
	print_dir_path(path_value);
	
	return (0);
}
