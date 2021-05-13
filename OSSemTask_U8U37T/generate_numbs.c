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

    int r, fd, array[N];

    srand(time(0)); //a random generator mindig uj random szamokat general

    for(int i = 0; i < N; i++) //ezzel a for ciklussal generalom milyen szamok kerulnek beirasra a fajlba ellenorzesre
    {
        array[i] = rand()%100 + 1;
        printf("\nGenerated the %d. number which is: %d", i+1, array[i]);
    }

    fd = mkfifo("numbers", 0666); //letrehozom a nevesitett csovezeteket numbers nevvel

    if(fd == -1) //ellenozom, hogy sikerult-e
    {
        if(fd != EEXIST) //itt csak akkor lepek ki, ha a problema nem az, hogy mar eleve is letezett es jelzem a felhasznalonak, hogy mi tortenik
        {
            printf("\nProblem with creating the file: numbers");
            exit(-1);
        }
        else printf("\nThe file already existed");
    }
    else printf("\nJust created the file: numbers");

    fd = open("numbers", O_WRONLY); //megnyitom a csovezeteket

    if(fd == -1) //ellenorzom, hogy sikeres-e a megnyitas es jelzem a felhasznalonak
    {
        printf("\nProblem with opening the file: numbers");
        exit(-1);
    }
    else printf("\nJust opened the file: numbers");

    for(int i = 0; i < N; i++) //ezzel a for ciklussal beirom a random generalt szamaimat a csovezetekbe
    {
        if(write(fd, &array[i], sizeof(int)) == -1) //ellenorzom, hogy sikeres-e a beiras es jelzem a felhasznalonak
        {
            printf("\nProblem with writing into the file number %d", i + 1);
            exit(-1);
        }
        printf("\nNumber %d is written", i+1);
    }

    close(fd); //bezarom a numbers csovezeteket

    fd = open("result", O_RDONLY); //megnyitom a csovezeteket, amely az eredmenyt tartalmazza (olvasasra), hogy a masik bele tudjon irni

    if (fd == -1)
    {
        printf("\nProblem with opening the file: result");
    }
    else printf("\nJust opened the file: result for reading");

    for(int i = 0; i < N + 1; i++)
    {
        if(read(fd, &array[i], sizeof(int)) == -1)
        {
            printf("\nCouldn't read number %d", i+1);
            exit(-1);
        }

        printf("\nRecieved number %d, it is: %d", i+1, array[i]);
    } 

    close(fd); //bezarom a result csovezeteket

    unlink("result"); //torlom a result csovezeteket



    return 0;
}
