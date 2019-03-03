#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/types.h>
char directory[1000];
char* dirs[100];
int dl = 0;
int l = 0, a = 0, r = 0;
void mylsfn(char direc[1000])
{
    struct dirent *d;
    DIR *p;
    p = opendir(direc);
    if(p == NULL)
    {
        exit(1);
    }
    while(d = readdir(p)) {
        if(l == 1) {
            if(a == 0 && (d->d_name)[0] == '.') continue;
            struct stat fileStat;
            stat(d->d_name,&fileStat);
            printf((S_ISDIR(fileStat.st_mode)) ? "d" : "-");
            printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
            printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
            printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
            printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
            printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
            printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
            printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
            printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
            printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
            printf("  %-5lu %-5d %-5d %-5lu %-20s\n",fileStat.st_nlink,fileStat.st_uid,fileStat.st_gid,fileStat.st_size,d->d_name);
        }
        else if(l == 0)  {
            if(a == 0 && (d->d_name)[0] == '.') continue;
            printf("%-20s",d->d_name);
        }
        if(r == 1) {
            struct stat fileStat;
            stat(d->d_name,&fileStat);
            if(S_ISDIR(fileStat.st_mode) && strcmp(d->d_name,".") && strcmp(d->d_name,"..")) {
                getcwd(directory,sizeof(directory));
                printf("\n");
                mylsfn(strcat(strcat(directory,"/"),d->d_name));
            }
            printf("\n");
        }
    }
    closedir(p);
    printf("\n");
}
int main(int argc, char *argv[])
{
	for(int i = 1; i < argc; i++) {
		if(strcmp(argv[i],"-l") == 0) l = 1;
		else if(strcmp(argv[i],"-a") == 0) a = 1;
		else if(strcmp(argv[i],"-R") == 0) r = 1;
	}
	getcwd(directory, sizeof(directory));
    mylsfn(directory);
	exit(0);
}
