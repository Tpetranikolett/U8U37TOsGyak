#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(int argc, char *argv[])
{
	int pipefd[2];
	pid_t cpid;
	char buffer;

	if(argc != 2)
	{
		fprintf(stderr, "hpw to use: %s <string>\n", argv[0]);
		exit (EXIT_FAILURE);
	}
	if(pipe(pipefd) == -1)
	{
		perror("pipe");
		exit(EXIT_FAILURE);
	}

	printf("pid: %d, fd1: %d, fd2: %d\n", getpid(), pipefd[0], pipefd[1]);

	cpid = fork();

	if(cpid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	
	if(cpid == 0)
	{
		close(pipefd[1]);
		while(read(pipefd[0], &buffer, 1) > 0)
		{
			write(STDOUT_FILENO, &buffer, 1);
		}
	write(STDOUT_FILENO, "\n", 1);
	close(pipefd[0]);
	_exit(EXIT_SUCCESS);
	}
	
	else
	{
		close(pipefd[0]);
		write(pipefd[1], argv[1], strlen(argv[1]));
		close(pipefd[1]);
		wait(NULL);
		exit(EXIT_SUCCESS);
	}
 
}