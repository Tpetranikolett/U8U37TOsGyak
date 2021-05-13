#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>

#define SECOND 1

void do_nothing();
void do_int();

main ()
{
	int i;
	unsigned sec=1;

	signal(SIGINT, do_int);

for (i=1;i<8;i++) {
	alarm(sec);
	signal(SIGALRM, do_nothing);
	printf("  %d varok de meddig?\n", i);
	pause();
    }
return 0;

}	
void do_nothing(){ ;}

void do_int() {
	printf("jott egy int");
	signal(SIGINT,SIG_IGN);
}