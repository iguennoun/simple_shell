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

/**
 * main - The main function of our simple shell program
 * @ac : Nbr of arguments
 * @av : Arrays of strings (arguments)
 * @env : The environment variables
 *
 * Return: Always 0.
 */
int main(int ac, char **av, char **env)
{
        char *shell_name = "($) ", *shell_line = NULL, *cmd = NULL;
        size_t linecap = 0;
        ssize_t linelen;
        char **tokens = NULL;
        pid_t pid;
        int status;

        (void) ac, (void) av;
        while (1)
        {
                printf("%s", shell_name);
                linelen = getline(&shell_line, &linecap, stdin);
                if (linelen == EOF)
                {
                        exit(EXIT_FAILURE);
                }
                shell_line[linelen - 1] = '\0';

                /* tokens = malloc(sizeof(char *) * 1024); */
                tokens = tokensInLine(shell_line);
                /* printf("%s\n", shell_line); */
                if (strcmp(tokens[0], "exit") == 0)
                        exit(EXIT_SUCCESS);

                pid = fork();
                if (pid == 0)
                {
                        cmd = checkCommand(tokens[0], env);
                        if (cmd)
                                execve(cmd, tokens, env);
                        else
                                printf("%s: No such file or directory\n", av[0]);
			exit(EXIT_SUCCESS);
                }
                else
                        wait(&status);
                /* free(shell_line);*/
                free(tokens);
        }
        exit(EXIT_SUCCESS);
}
