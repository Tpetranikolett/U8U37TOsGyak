#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define KEY 123456L

	int semid, nsems, semnum, rtn;
	int semflg;
	struct sembuf sembuf, *sop;
	union semun
	{
		int val;
		struct semid_ds *buf;
		unsigned short *array;
	}arg;
	int cmd;
int main()
{
	nsems = 1;
	semflg = 00666 | IPC_CREAT;
	semid = semget(KEY, nsems, semflg);
	if(semid < 0)
	{
		perror("semget error\n");
		exit(-1);
	}
	else
		printf("semid: %d\n", semid);
	printf("adja meg a semval erteket: \n");
	semnum = 0;
	cmd = SETVAL;
	scanf("%d", &arg.val);
	rtn = semctl(semid, semnum, cmd, arg);
	printf("set rtn: %d, semval: %d\n", rtn, arg.val);
	return 0;
}