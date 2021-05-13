#include <stdio.h>
#include <stdlib.h>
#include <sys/file.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int main(){
        pid_t cpid;
        int ret;
        int fd;
        char buffer[32];
        char file[] = "U8U37T";
        ret = mkfifo(file, 0666);
        if(ret == -1)
        {
                perror("mkfifo()");
                exit(-1);
        }
        cpid = fork();
        if(cpid == -1)
        {
                perror("fork()");
                exit(-2);
        }
        if(cpid == 0)
        {
                printf("gyerek: %d\n", getpid());
                fd = open(file, O_WRONLY);
                if(fd == -1)
                {
                        perror("open()");
                        exit(-3);
                }
                strcpy(buffer, "T. Toth Petra u8u37t");
                write(fd, buffer, strlen(buffer));
                printf("iras utan a gyerek: %d\n", getpid());
                close(fd);
        }
        else
        {
                printf("szulo: %d\n", getpid());
                fd = open(file, O_RDONLY);
 	if(fd == -1)
                {
                        perror("open()");
                        exit(-4);
                }
                printf("olvasas elott a szulo: %d\n", getpid());
                ret = read(fd, &buffer, sizeof(buffer));
                printf("a read() %d byteot olvasott, string: %s\n", ret, buffer);
                close(fd);
                unlink(file);
        }
        return 0;
}

