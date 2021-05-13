#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

main(int argc, char **argv)
{
	int pid;

	if (argc < 1)
	{
		perror("De kinek?");
		exit(1);
	}

	pid = atoi(argv[1]);

	kill(pid, SIGALRM);
}	