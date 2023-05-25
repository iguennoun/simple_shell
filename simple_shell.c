#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <string.h>

/**
 * tokensInLine - Returns an array of strings (parameters of prog)
 * @str: The string to split
 *
 * Return: An Array of strings which are the params of the program
 */
char **tokensInLine(char *str)
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
                        exit(EXIT_FAILURE);
                }
                params[i - 1] = param;
                param = strtok(NULL, delimiters);
        }
        params[i] = NULL;
        return (params);
}

/**
 * getEnvVarVal - Gets an environment variable
 * @name : The name of the variable to get
 * @env : Environment variables
 *
 * Return: The value is any of the @name or NULL
 */
char *getEnvVarVal(const char *name, char **env)
{
        char **environ = env;
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
 * checkCommand - Check if a program is in the Path
 * @command : The command to execute
 * @env : Environment variables
 *
 * Return: The full path of a command or NULL
 */
char *checkCommand(char *command, char **env)
{
        char *path_dirs = getEnvVarVal("PATH", env);
        char *path_dir;
        char *cmd_full_path;
        struct stat st;

        path_dir = strtok(path_dirs, ":");
        while (path_dir)
        {
                cmd_full_path = malloc(strlen(path_dir) + strlen(command) + 2);
                strcpy(cmd_full_path, path_dir);
                strcat(cmd_full_path, "/");
                strcat(cmd_full_path, command);
               
	       	if (stat(cmd_full_path, &st) == 0)
                        return (cmd_full_path);
               
	       	free(cmd_full_path);
                path_dir = strtok(NULL, ":");
        }
        return (NULL);
}
