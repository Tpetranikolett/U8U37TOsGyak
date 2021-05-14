#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 123456L

struct sembuf sembuf, *sop;


int main(){
	int semid, nsems, rtn;
	int semflg;
	int cmd;
	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget(KEY, nsems, semflg);
	if(semid < 0) 
	{
		printf("semget error\n");
		exit(-1);
	}
	else
		printf("semid: %d\n", semid);
	cmd = GETVAL;
	rtn = semctl(semid,0,cmd, NULL);
	printf("semval: %d\n",rtn);
	return 0;
}