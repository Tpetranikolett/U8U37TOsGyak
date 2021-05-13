#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>


void do_nothing();


main ()
{


	signal(SIGALRM, do_nothing);
	printf("  %d varok de meddig?\n");
	pause();
    	printf("  Vegre, itt az alarm \n");
	return 0;
}	
void do_nothing(){ ;}