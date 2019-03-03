#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<dirent.h>
#include<sys/types.h>
#include<sys/stat.h>
int main(int argc, char *argv[])
{
    int i = 0, e = 0;
    char o = 'y';
    int fd;
    if(argc > 3) {
        if(!strcmp(argv[1],"-i")) i = 1;
        else {
            perror("Invalid option!");
            exit(1);
        }
    }
    else if(argc < 3) {
        perror("Too few  arguments!");
        exit(1);
    }
    int src = open(argv[1+i], O_RDONLY);
    if(src == -1) exit(1);
    DIR *p;
    struct dirent *d;
    p = opendir(".");
    if(p != NULL) {
        while((d = readdir(p)))
        {
            if(!strcmp(d->d_name,argv[2+i])) {
                e = 1;
                break;
            }
        }
        if(i == 1 && e == 1) {
            printf("Overwrite file? y/n: ");
            scanf("%c", &o);
        }
        if(o == 'y')
        {
            if(e == 1) fd = open(argv[2+i], O_WRONLY | O_TRUNC);
            else fd = creat(argv[2+i], O_CREAT|0666);
            char r;
            while(read(src, &r, 1))
            {
                write(fd, &r, 1);
            }
            printf("Copied!\n");
            close(src);
            close(fd);
            closedir(p);
        }
        else exit(0);
    }
    else {
        exit(1);
    }
    return 0;
}
