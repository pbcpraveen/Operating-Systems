#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
int main(int argc, char *argv[])
{
    int c = 0, n = 0, v = 0;
    int count = 0, lines = 0;
    if(argc >= 4)
    {
        for(int i = 1; i < argc; i++)
        {
            if(!strcmp(argv[i],"-v")) v = 1;
            if(!strcmp(argv[i],"-c")) c = 1;
            if(!strcmp(argv[i],"-n")) n = 1;
        }
    }
    char pattern[100]; strcpy(pattern,argv[argc - 2]);
    char filename[100]; strcpy(filename,argv[argc - 1]);
    int fd = open(filename, O_RDONLY);
    char outs[1000]="";
    char buf[2]="",line[100]="",integ[10]=""; int r = 1;
    while(r)
    {
        strcpy(line,"");
        while((r = read(fd,buf,1)))
        {
            strcat(line,buf);
            if(!strcmp(buf,"\n")) {
                lines++;
                break;
            }
        }
        if(r == 0) break;
        strcat(line,"\0");
        char *ret = strstr(line,pattern);
        if(v == 0 && ret != NULL) {
            count++;
            if(n == 0) {
                strcat(outs,line);
            }
            else if(n == 1) {
                sprintf(integ,"%d",lines);
                strcat(outs,integ);
                strcat(outs,": ");
                strcat(outs,line);
            }
        }
        else if(v == 1 && ret == NULL) {
            count++;
            if(n == 0) {
                strcat(outs,line);
            }
            else if(n == 1) {
                sprintf(integ,"%d",lines);
                strcat(outs,integ);
                strcat(outs,": ");
                strcat(outs,line);
            }
        }
    }
    if(c == 1 && n == 1) {
        printf("%d\n%s", count, outs);
    }
    else if(c == 1 && n == 0) {
        printf("%d\n", count);
    }
    else if(c == 0)
    {
        printf("%s", outs);
    }
    close(fd);
    return 0;
}
