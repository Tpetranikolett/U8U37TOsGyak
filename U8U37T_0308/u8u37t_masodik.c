#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	char input[20];
	printf("\ntype a command: ");
	scanf("%s", input);
	int status = system(input);
	if(WIFEXITED(status))
		printf("the output is: %d\n", WEXITSTATUS(status));
	else
		printf("error\n");
	return 0;
}