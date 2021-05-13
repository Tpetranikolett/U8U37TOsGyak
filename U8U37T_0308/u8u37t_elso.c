#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(){
	int status = system("date");
	if(WIFEXITED(status))
		printf("befejezodes: normal, visszateresi ertek %d\n", WEXITSTATUS(status));
	else
		printf("Hamis\n");
	int status2 = system("semmi");
	if(WIFEXITED(status) == 0)
		printf("befejezodes: normal, visszateresi ertek %d\n", WEXITSTATUS(status));
	else
		printf("Hamis\n");
	return 0;
}