#include<stdio.h>
#include<stdlib.h>
#include<dirent.h>
struct dirent *d;
int main(int argc, char *argv[])
{
    char buff[100] = "../Ex2";
    DIR *dirp;
    if((dirp=opendir(buff))==NULL)
    {
        printf("The given directory does not exist");
        exit(1);
    }
    while((d=readdir(dirp)))
    {
        printf("%s\n",d->d_name);
    }
    closedir(dirp);
}

