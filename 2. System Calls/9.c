#include<stdio.h>
#include<fcntl.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
main(int argc, char* argv[])
{
    int fd;
    char buf[100];
    int i = 1;
    if((fd = open("file1.txt", O_WRONLY | O_CREAT, 00666))==-1)
    {
        printf("Cannot create\n");
        exit(1);
    }
    write(fd,"Hello world",11);
    int fd1 = open("file1.txt", O_RDONLY, 0);
    read(fd1,buf,11);
    printf("%s\n",buf);
    close(fd);
    close(fd1);
}
