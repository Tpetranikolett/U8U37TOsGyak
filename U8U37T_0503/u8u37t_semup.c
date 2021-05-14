#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#define KEY 123456L

	int semid, nsems, rtn;
	unsigned nsops;
	int semflg;
	struct sembuf sembuf, *sop;

int main()
{
	nsems = 1;
 	semflg = 00666 | IPC_CREAT;
	semid = semget(KEY, nsems, semflg);
	if(semid < 0) 
	{
		perror("semget error\n");
		exit(0);
	}
	else printf("semid: %d\n", semid);
	nsops;
	sembuf.sem_num = 0;
	sembuf.sem_op = 1;
	sembuf.sem_flg = 0666;
	sop = &sembuf;
	rtn = semop(semid, sop, semflg);
	printf("rtn up: %d\n", rtn);
	return 0;
}