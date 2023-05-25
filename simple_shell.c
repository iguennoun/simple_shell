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
