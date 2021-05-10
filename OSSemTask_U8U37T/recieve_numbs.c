#include <stdio.h>
#include <stdlib.h> // exit
#include <sys/file.h> // open
#include <sys/types.h> // mkfifo, open
#include <sys/stat.h> // mkfifo, open
#include <fcntl.h> // open
#include <string.h> //strcpy
#include <unistd.h> // fork, read, write
#include <time.h>
//#include <random.h>
#include <errno.h>

#define N 3

int main(int argc, char* argv[])
{
    int array[N+1];

    int fd = open("numbers", O_RDONLY); //megnyitom a numbers csovezeteket

    if(fd == -1) //ellenorzom, hogy sikerult-e es ezt jelzem a felhasznalonak, hogy mi tortenik
    {
        printf("\nProblem with opening the file: numbers");
        exit(-1);
    }
    else printf("\nJust opened the file: numbers");

    for(int i = 0; i < N; i++) //itt kiolvasom a numbers csovezetekbol a beleirt szamokat
    {
        if(read(fd, &array[i], sizeof(int)) == -1) //ellenorzom, sikeres-e a kiolvasas es jelzem a felhasznalonak
        {
            printf("\nCouldn't read number %d", i+1);
            exit(-1);
        }

        printf("\nRecieved number %d, it is: %d", i+1, array[i]);
    }

    close(fd); //bezarom a numbers csovezeteket

    unlink("numbers");//torlom a numbers csovezeteket

    int q;

    //a kovetkezo sorokban ellenorzom, hogy a csovezetekben kapott harom szam lehet-e egy haromszog harom oldala

    if((array[0] + array[1]) < array[2] && (array[0] + array[2]) < array[1] && (array[1] + array[2]) < array[0])
    {
        q = 1;
    }
    else q = 0; //itt pedig megadom a negyedik fileba irando szam erteket, amely jelzi, hogy a lehetseges-e a feladatban feltett kerdes

    array[N] = q;

    printf("\n q is: %d", q); //az eredmenyt ki is iratom

    int fd2 = mkfifo("result", 0666); //letrehozom a result csovezeteket

    if(fd2 == -1) //ellenorzom, hogy ez sikerult-e
    {
        if(fd2 != EEXIST) //megnezem, hogy veletlen nem-e azert nem sikerult, mert mar eleve letezett
        {
            printf("\nProblem with creating the file: result");
            exit(-1);
        }
        else printf("\nThe file already existed");
    }
    else printf("\nJust created the file: result");

    fd2 = open("result", O_WRONLY);

    if( fd2 == -1)
    {
        printf("\nProblem with opening the file: result");
        exit(-1);
    }
    else printf("\nJust opened the file: result");

    for(int i = 0; i < N+1; i++) //beleirom a harom szamot es az ellenorzes eredmenyet a result-ba
    {
        if(write(fd2, &array[i], sizeof(int)) == -1)
        {
            printf("\nProblem with writing number %d", i+1);
            exit(-1);
        }
        printf("\nWrote number %d, it is: %d", i+1, array[i]);
    }

    close(fd2); // bezarom a result csovezeteket

    return 0;
}
