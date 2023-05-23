#include <stdio.h>
#include <unistd.h>

/**
 * main - PID
 *
 * Return: Always 0.
 */
int main(void)
{
	pid_t my_pid;

	my_pid = getpid();
	printf("PID        : %u\n", my_pid);
	printf("Parent PID : %u\n", getppid());

	/*
	 * $$ means the process ID that the script file is running under.
	 * For any given script, when it is run, it will have only one "main"
	 * process ID.Regardless of how many subshells you invoke, $$ will always
	 * return the first process ID associated with the script. BASHPID will show
	 * you the process ID of the current instance of bash, so in a subshell
	 * it will be different than the "top level" bash which may have invoked it.
	 */
	return (0);
}
